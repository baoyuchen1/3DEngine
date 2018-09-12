#include "../../include/render/image.h"
#define STB_IMAGE_IMPLEMENTATION
#include"../../include/stb_image.h"
using namespace myrender;
Image* Image::instance = nullptr;
myrender::Image::Image()
{
}

myrender::Image::~Image()
{
}

Image * myrender::Image::getInstance()
{
	if (instance == nullptr)
		instance = new Image();
	return instance;
}

void myrender::Image::SetFlipVerticallOnLoad(bool state)
{
	stbi_set_flip_vertically_on_load(state);
}

unsigned char * myrender::Image::LoadImageData(char const * filename, int * x, int * y, int * comp, int req_comp)
{
	return stbi_load(filename, x, y, comp, req_comp);
}

void myrender::Image::FreeImage(void * retval_from_stbi_load)
{
	stbi_image_free(retval_from_stbi_load);
}


