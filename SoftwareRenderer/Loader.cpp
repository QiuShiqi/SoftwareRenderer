#include "Loader.h"
#include "Library/FreeImage.h"

Image* Loader::loadImage(const char* fileName){

	//1 获取图片格式
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName, 0);
	if (fifmt == FIF_UNKNOWN) {
		return 0;
	}

	//2 加载图片
	FIBITMAP *dib = FreeImage_Load(fifmt, fileName,0);
	FREE_IMAGE_COLOR_TYPE type = FreeImage_GetColorType(dib);

	//! 获取数据指针
	FIBITMAP* temp = dib;
	dib = FreeImage_ConvertTo32Bits(dib);
	FreeImage_Unload(temp);

	BYTE* pixels = (BYTE*)FreeImage_GetBits(dib);
	int width = FreeImage_GetWidth(dib);
	int height = FreeImage_GetHeight(dib);

	Image* image = new Image(width, height, pixels);
	FreeImage_Unload(dib);

	return image;
}