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
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // �⺻ Ŀ�� ���
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // �⺻ ������ ���
	RegisterClass(&wc);

	// â ũ�� �� �°� ����
	RECT rcClient = { 0, 0, (LONG)g_width, (LONG)g_height };
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	// ������ ����
	g_hWnd = CreateWindow(
		szClassName,					// ������ Ŭ���� �̸�
		TEXT("GDI_AnimationTest"),		// â ����
		WS_OVERLAPPEDWINDOW,			// ������ ��Ÿ��
		800,							// ������ ��ġ x
		500,							// ������ ��ġ y
		rcClient.right - rcClient.left,	// ������ ũ�� x
		rcClient.bottom - rcClient.top, // ������ ũ�� y
		NULL,							// �θ� ������
		NULL,							// �޴�
		hInstance,
		NULL);
}

// WIN32 API ���� ���� ���� ���� �޼����� ����ϴ� �Լ�
static void PrintLastErrorMessage()
{
	DWORD errorCode = GetLastError();
	LPVOID lpMsgBuf;

	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // �⺻ ���
		(LPSTR)&lpMsgBuf,
		0,
		NULL);

	if (lpMsgBuf)
	{
		DebugLog("���� �ڵ�: %lu\n���� �޽���: %s\n", errorCode, (char*)lpMsgBuf);
		LocalFree(lpMsgBuf); // �Ҵ�� ���� ����
	}
	else
	{
		DebugLog("���� �ڵ�: %lu (�޽����� ã�� �� ����)\n", errorCode);
	}
}