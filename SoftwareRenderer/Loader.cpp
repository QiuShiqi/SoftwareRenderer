#include "Loader.h"
#include "Library/FreeImage.h"

Image* Loader::loadImage(const char* fileName){

	// Get the image format
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName, 0);
	if (fifmt == FIF_UNKNOWN) {
		return 0;
	}

	// Load image
	FIBITMAP *dib = FreeImage_Load(fifmt, fileName,0);
	FREE_IMAGE_COLOR_TYPE type = FreeImage_GetColorType(dib);

	// Get the data pointer
	FIBITMAP* temp = dib;
	dib = FreeImage_ConvertTo32Bits(dib);
	FreeImage_Unload(temp);

	BYTE* pixels = (BYTE*)FreeImage_GetBits(dib);
	int width = FreeImage_GetWidth(dib);
	int height = FreeImage_GetHeight(dib);

	// Flip the image so that it is the same as the Windows coordinate system
	int size = width * 4;
	BYTE* row = new BYTE[width * 4];

	for(int i = 0; i < height / 2; i++){
		memcpy(row, pixels + i * size, size);
		memcpy(pixels + i * size, pixels + (height - i - 1) * size, size);
		memcpy(pixels + (height - i - 1) * size, row, size);
	}

	delete []row;
	row = nullptr;

	// Pack data
	Image* image = new Image(width, height, pixels);
	FreeImage_Unload(dib);

	return image;
}