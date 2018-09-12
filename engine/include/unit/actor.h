#pragma once
#include"modelbase.h"
namespace myrender {
	class Actor:public ModelBase
	{
	public:
		Actor();
		~Actor();
		void draw();
	private:
		int actorsize;
		int* vertices;
	};
}