#include "GDIRenderer.h"

#include <windows.h>
#include <gdiplus.h>

#include "Global.h"
#include "Sprite.h"

#pragma comment(lib, "gdiplus.lib")

static HDC front_buffer_DC;
static HDC back_buffer_DC;
static HBITMAP back_buffer_bitmap;

// GDI+
static ULONG_PTR gdiplus_token;
static Gdiplus::Graphics* back_buffer_graphics;

void GDIRenderer::Initialize()
{
	front_buffer_DC = GetDC(g_hWnd); // 윈도우 클라이언트 영역의 Device Constext 얻기
	back_buffer_DC = CreateCompatibleDC(front_buffer_DC); // 호환되는 Device Context 생성
	back_buffer_bitmap = CreateCompatibleBitmap(front_buffer_DC, g_width, g_height); // 메모리 영역 생성
	SelectObject(back_buffer_DC, back_buffer_bitmap); // MemDC의 메모리 영역 지정

	Gdiplus::GdiplusStartupInput gsi;
	Gdiplus::GdiplusStartup(&gdiplus_token, &gsi, nullptr);
	back_buffer_graphics = Gdiplus::Graphics::FromHDC(back_buffer_DC);
}

void GDIRenderer::Shutdown()
{
	delete back_buffer_graphics;
	Gdiplus::GdiplusShutdown(gdiplus_token);

	DeleteObject(back_buffer_bitmap);
	DeleteDC(back_buffer_DC);
	ReleaseDC(g_hWnd, front_buffer_DC);
}

void GDIRenderer::BeginDraw()
{
	PatBlt(back_buffer_DC, 0, 0, g_width, g_height, BLACKNESS);
}

void GDIRenderer::Render(Gdiplus::Bitmap* image, Gdiplus::Rect& dst_rect, Gdiplus::Rect& src_rect)
{
	back_buffer_graphics->DrawImage(image, dst_rect, src_rect.X, src_rect.Y, src_rect.Width, src_rect.Height, Gdiplus::UnitPixel);
}

void GDIRenderer::EndDraw()
{
	BitBlt(front_buffer_DC, 0, 0, g_width, g_height, back_buffer_DC, 0, 0, SRCCOPY);
}