#pragma once
#include"../constant/engine_constant.h"
namespace myrender {
	class RenderCommand
	{   
	public:
		RenderCommand();
		~RenderCommand();
		virtual void Draw() ;
		virtual void LoadTexture();
		virtual void Release();
		virtual void LoadVertexArry();
		virtual void Init();
	};
}