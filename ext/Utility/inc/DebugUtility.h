#pragma once

#ifdef _DEBUG

// 콘솔 초기화
#define InitializeConsole() __InitializeConsole()
// 함수를 직접 쓰면 안됨
void __InitializeConsole();

// 콘솔 해제
#define ReleaseConsole() __ReleaseConsole()
// 함수를 직접 쓰면 안됨
void __ReleaseConsole();


// 메모리 누수 체크
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define ENABLE_LEAK_CHECK() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#define DUMP_LEAKS() _CrtDumpMemoryLeaks()


// FPS 체크
#define CHECK_FPS() __CheckFPS()
// 함수를 직접 쓰면 안됨
void __CheckFPS();


// 로그 출력
// 비주얼 스튜디오->보기->출력->디버그에 로그 출력 함.
// printf랑 똑같이 사용하면 됨.
#define DebugLog(...) __PrintDebugLog(__VA_ARGS__)
// 함수를 직접 쓰면 안됨
void __PrintDebugLog(const char* fmt, ...);

#define DebugLogW(...) __PrintDebugLogW(__VA_ARGS__)
// 함수를 직접 쓰면 안됨
void __PrintDebugLogW(const wchar_t* fmt, ...);

#else // !_DEBUG
// 디버그 모드가 아닐때는 함수 없앰

#define InitializeConsole()		((void)0)
#define ReleaseConsole()		((void)0)
#define ENABLE_LEAK_CHECK()		((void)0)
#define DUMP_LEAKS()			((void)0)
#define CHECK_FPS()				((void)0)
#define DebugLog(...)			((void)0)

#endif // _DEBUG