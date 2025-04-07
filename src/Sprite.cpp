#include "Sprite.h"

#include <windows.h>
#include <gdiplus.h>

#include "MyTime.h"

Sprite::Sprite()
	: image(nullptr), frames(0), width(0), height(0), frame_width(0), is_loop(false)
	, duration(0.0f), current_time(0.0f), is_end(false), is_stoppable(false)
{

}

Sprite::Sprite(const wchar_t* filename, int frames, bool is_loop, bool is_stoppable)
	: frames(frames), is_loop(is_loop), current_time(0.0f), is_end(true), is_stoppable(is_stoppable)
{
	image = new Gdiplus::Bitmap(filename);
	width = image->GetWidth();
	height = image->GetHeight();

	frame_width = width / frames;

	duration = frames * 0.05f;
}

Sprite::~Sprite()
{
	if (image != nullptr)
	{
		delete image;
	}
}

void Sprite::Play()
{
	is_end = false;
}

void Sprite::GetFrameInfo(Gdiplus::Rect* dstRect, Gdiplus::Rect* srcRect) const
{
	dstRect->Width = frame_width;
	dstRect->Height = height;

	srcRect->X = frame_width * (int)(frames * (current_time / duration));
	srcRect->Y = 0;
	srcRect->Width = frame_width;
	srcRect->Height = height;
}

void Sprite::Update()
{
	current_time += MyTime::DeltaTime();
	if (current_time > duration)
	{
		if (is_loop)
		{
			current_time -= duration;
		}
		else
		{
			is_end = true;
		}
	}
}

void Sprite::Reset()
{
	current_time = 0.0f;
	is_end = true;
}