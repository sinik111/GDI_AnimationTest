#include "MyTime.h"

#include <windows.h>

static LARGE_INTEGER frequency;
static LARGE_INTEGER previous_counter;

static float delta_time = 0.f;

void MyTime::Initialize()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&previous_counter);

	srand((unsigned int)previous_counter.QuadPart);
}

void MyTime::Update()
{
	LARGE_INTEGER current_counter;

	QueryPerformanceCounter(&current_counter);

	delta_time = (float)(current_counter.QuadPart - previous_counter.QuadPart) / frequency.QuadPart;

	previous_counter = current_counter;
}

float MyTime::DeltaTime()
{
	return delta_time;
}