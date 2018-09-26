#pragma once
#include"render/render.h"
#include"render/image.h"
#include"render\viewport.h"
namespace myrender {
	class Render;
	class Image;
	class Root
	{
	public:
		static Root* getInstance();
		Render* getRender();
		Image*  getImage();		
		ViewPort* getViewPort();
	private:
		Root();
		//把复制构造函数和=操作符也设为私有,防止被复制
		 static Root* instance;
	};
}