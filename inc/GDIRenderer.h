#pragma once

namespace Gdiplus
{
	class Bitmap;
	class Rect;
}

namespace GDIRenderer
{
	void Initialize();

	void Release();

	void BeginDraw();

	void Render(Gdiplus::Bitmap* image, Gdiplus::Rect& dst_rect, Gdiplus::Rect& src_rect);

	void EndDraw();
}