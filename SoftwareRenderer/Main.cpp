#include <Windows.h>
#include <stdio.h> 
#include <tchar.h>
#include "Raster.h"
#include "Loader.h"

void recover(void* p){
	if(p != nullptr){
		delete p;
		p = nullptr;
	}
}

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

	// Register window
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

	// Create window
	HWND hwnd = CreateWindowEx(
		NULL,
		_T("Test"), _T("Test"),
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL, NULL,
		hInstance, NULL
		);

	// Show window
	UpdateWindow(hwnd);
	ShowWindow(hwnd, SW_SHOW);

	// Initialize DC
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

	// Initialize raster
	Raster raster(width, height, buffer);
	Image* image = Loader::loadImage("Images\\bg.png");
	Image* imageUV = Loader::loadImage("Images\\scale.jpg");

	// Message loop
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

		// Draw
		raster.drawImage(0, 0, image);

		Vertex vertex[] = {
			Vertex(float3(-10, -10, 1), Pixel(), float2(0.0f, 0.0f)),
			Vertex(float3(210, 210, 1), Pixel(), float2(2.0f, 2.0f)),
			Vertex(float3(210, -10, 1), Pixel(), float2(2.0f, 0.0f)),

			Vertex(float3(-10, -10, 1), Pixel(), float2(0.0f, 0.0f)),
			Vertex(float3(210, 210, 1), Pixel(), float2(2.0f, 2.0f)),
			Vertex(float3(-10, 210, 1), Pixel(), float2(0.0f, 2.0f))
		};

		static float angles = 0.0f;
		matrix3 matrix;
		matrix.translate(-110, -110);

		matrix3 rotate;
		rotate.rotate(angles);

		matrix3 scale;
		scale.scale(0.5f, 0.5f);

		matrix3 translate;
		translate.translate(110, 110);

		matrix3 all = matrix * (rotate * scale * translate);
		angles += 1.0f;

		raster.setMatrix(all);

		raster.drawTriangle(vertex[0], vertex[1], vertex[2], imageUV);
		raster.drawTriangle(vertex[3], vertex[4], vertex[5], imageUV);

		// Copy data
		BitBlt(hDC, 0, 0, width, height, hMem, 0, 0, SRCCOPY);
	}

	// recover
	recover(imageUV);
	recover(image);

	return 0;
}
