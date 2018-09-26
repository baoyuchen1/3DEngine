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
		//�Ѹ��ƹ��캯����=������Ҳ��Ϊ˽��,��ֹ������
		 static Root* instance;
	};
}