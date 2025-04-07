#include "Input.h"

#include <windows.h> // GetAsyncKeyState 사용
#include <memory>

static SHORT key_state[256] = { 0 };
static SHORT previous_key_state[256] = { 0 };

void Input::Update()
{
    // 이전 상태 저장
    memcpy_s(previous_key_state, sizeof(previous_key_state), key_state, sizeof(key_state));

    for (int i = 0; i < 256; ++i)
    {
        key_state[i] = GetAsyncKeyState(i);
    }
}

bool Input::IsKeyPressing(int vKey)
{
    return (key_state[vKey] & 0x8000) != 0;
}

bool Input::IsKeyDown(int vKey)
{
    return (!(previous_key_state[vKey] & 0x8000) && (key_state[vKey] & 0x8000));
}

bool Input::IsKeyUp(int vKey)
{
    return ((previous_key_state[vKey] & 0x8000) && !(key_state[vKey] & 0x8000));
}