#pragma once
#include"object.h"
#include"../constant/includefile.h"
namespace myrender
{
	class ModelBase:public Object
	{
	public:
		ModelBase() {};
		~ModelBase() {};
		virtual void render() = 0;
	private:

	};

}