#pragma once
#include"../unit/object.h"
namespace myrender
{
	class Eventhandle :public Object
   {
		virtual void Release() = 0;
   };
}
