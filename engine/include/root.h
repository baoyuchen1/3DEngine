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
		//�Ѹ��ƹ��캯����=������Ҳ��Ϊ˽��,��ֹ������
		 static Root* instance;
	};
}