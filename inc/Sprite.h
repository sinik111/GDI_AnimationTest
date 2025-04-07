#pragma once

namespace Gdiplus
{
	class Bitmap;
	class Rect;
}

struct Sprite
{
	Gdiplus::Bitmap* image;
	int frames;
	float duration;
	float current_time;
	unsigned int width;
	unsigned int height;
	unsigned int frame_width;
	bool is_loop;
	bool is_end;
	bool is_stoppable;

	Sprite();
	Sprite(const wchar_t* filename, int frames, bool is_loop, bool is_stoppable);
	~Sprite();

	void Play();

	void GetFrameInfo(Gdiplus::Rect* dstRect, Gdiplus::Rect* srcRect) const;

	void Update();

	void Reset();
};