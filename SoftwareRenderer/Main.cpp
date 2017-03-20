#include <Windows.h>
#include <tchar.h>
#include "Raster.h"

LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch(message){
	case WM_SIZE:
		break;

	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){

	//注册
	WNDCLASSEX wndClass = {0};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	wndClass.lpfnWndProc = windowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = NULL;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = _T("Test");

	RegisterClassEx(&wndClass);

	//创建
	HWND hwnd = CreateWindowEx(
		NULL,
		_T("Test"), _T("Test"),
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		480, 320,
		NULL, NULL,
		hInstance, NULL
		);

	//显示
	UpdateWindow(hwnd);
	ShowWindow(hwnd, SW_SHOW);

	//初始化DC
	RECT rect = {0};
	GetClientRect(hwnd, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	void* buffer = 0;

	HDC hDC = GetDC(hwnd);
	HDC hMem = CreateCompatibleDC(hDC);

	BITMAPINFO bmpInfor;
	bmpInfor.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfor.bmiHeader.biWidth = width;
	bmpInfor.bmiHeader.biHeight = -height;
	bmpInfor.bmiHeader.biPlanes = 1;
	bmpInfor.bmiHeader.biBitCount = 32;
	bmpInfor.bmiHeader.biCompression = BI_RGB;
	bmpInfor.bmiHeader.biSizeImage = 0;
	bmpInfor.bmiHeader.biXPelsPerMeter = 0;
	bmpInfor.bmiHeader.biYPelsPerMeter = 0;
	bmpInfor.bmiHeader.biClrUsed = 0;
	bmpInfor.bmiHeader.biClrImportant = 0;

	HBITMAP hBmp = CreateDIBSection(hDC, &bmpInfor, DIB_RGB_COLORS, (void**)&buffer, 0, 0);
	SelectObject(hMem, hBmp);

	memset(buffer, 0, width * height * 4);

	//光栅
	Raster raster(width, height, buffer);

	//消息循环
	MSG msg = {0};

	while(true){
		if(msg.message == WM_DESTROY || msg.message == WM_CLOSE || msg.message == WM_QUIT){
			break;
		}

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		raster.clear();

		//绘制
		int2 points[] = {
			int2(10, 10),
			int2(110, 10),
			int2(110, 110),
			int2(10, 110)
		};

		Pixel pixel[] = {
			Pixel(255, 0, 0),
			Pixel(0, 255, 0),
			Pixel(0, 0, 255),
			Pixel(255, 255, 255)
		};

		raster.drawRectangle(points, pixel);

		//拷贝数据
		memcpy(buffer, raster.getBuffer(), raster.getBufferSize());
		BitBlt(hDC, 0, 0, width, height, hMem, 0, 0, SRCCOPY);
	}

	return 0;
}
