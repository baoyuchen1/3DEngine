#pragma once
#include"render/render.h"
#include"render/image.h"
#include"render\viewport.h"
#include"render\manager\texturemanager.h"
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
		TextureManager* getTextureManager();
	private:
		Root();
		//把复制构造函数和=操作符也设为私有,防止被复制
		 static Root* instance;
	};
}