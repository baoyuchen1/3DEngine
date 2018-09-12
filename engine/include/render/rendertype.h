#pragma once
#include"../unit/object.h"
namespace myrender
{
	class RenderType:public Object
	{
	public:
		void init();
		virtual void draw() = 0;
		RenderType();
		~RenderType();
	private:

	};

}