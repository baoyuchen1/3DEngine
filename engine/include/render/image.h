#pragma once
#include"../constant/includefile.h"
#include"../../../3rd/OpenGL/include/FreeImage.h"
namespace myrender
{
	class Image
	{
	public:

		static Image* getInstance();
		void SetFlipVerticallOnLoad(bool);
		unsigned char * LoadImageData(char const *filename, int *x, int *y, int *comp, int req_comp);
		void FreeImage(void *retval_from_stbi_load);
	private:
		Image();
		~Image();
		static Image* instance;
	};

}