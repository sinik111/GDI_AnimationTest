#include <windows.h>

#include <stdio.h>

#include "DebugUtility.h"
#include "Global.h"
#include "MyTime.h"
#include "Game.h"

#pragma comment(lib, "Utility.lib")

HWND g_hWnd;

const int g_width = 800;
const int g_height = 600;

static LPCTSTR szClassName = TEXT("GDI");

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

static void InitializeWindow(HINSTANCE hInstance);
static void PrintLastErrorMessage();

// main
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ENABLE_LEAK_CHECK();

	InitializeConsole();

	char szPath[MAX_PATH] = {};
	GetCurrentDirectoryA(MAX_PATH, szPath);
	DebugLog("Current Directory: %s\n", szPath);

	InitializeWindow(hInstance);

	ShowWindow(g_hWnd, nCmdShow);

	UpdateWindow(g_hWnd);

	DebugLog("1 Walk, 2 Attack\n");

	Game::Initialize();
	MyTime::Initialize();
	
	MSG msg = {};

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Game::Update();
		Game::Render();

		CHECK_FPS();
		
		MyTime::Update();
	}

	Game::Shutdown();

	ReleaseConsole();

	DUMP_LEAKS();

	return (int)msg.wParam;
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

static void InitializeWindow(HINSTANCE hInstance)
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = szClassName;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // 기본 커서 모양
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 기본 아이콘 모양
	RegisterClass(&wc);

	// 창 크기 딱 맞게 조정
	RECT rcClient = { 0, 0, (LONG)g_width, (LONG)g_height };
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	// 윈도우 생성
	g_hWnd = CreateWindow(
		szClassName,					// 윈도우 클래스 이름
		TEXT("GDI_AnimationTest"),		// 창 제목
		WS_OVERLAPPEDWINDOW,			// 윈도우 스타일
		800,							// 윈도우 위치 x
		500,							// 윈도우 위치 y
		rcClient.right - rcClient.left,	// 윈도우 크기 x
		rcClient.bottom - rcClient.top, // 윈도우 크기 y
		NULL,							// 부모 윈도우
		NULL,							// 메뉴
		hInstance,
		NULL);
}

// WIN32 API 에러 값에 대한 실제 메세지를 출력하는 함수
static void PrintLastErrorMessage()
{
	DWORD errorCode = GetLastError();
	LPVOID lpMsgBuf;

	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 기본 언어
		(LPSTR)&lpMsgBuf,
		0,
		NULL);

	if (lpMsgBuf)
	{
		DebugLog("오류 코드: %lu\n오류 메시지: %s\n", errorCode, (char*)lpMsgBuf);
		LocalFree(lpMsgBuf); // 할당된 버퍼 해제
	}
	else
	{
		DebugLog("오류 코드: %lu (메시지를 찾을 수 없음)\n", errorCode);
	}
}