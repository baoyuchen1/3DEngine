#pragma once
#include"../constant/includefile.h"
namespace myrender {
	class RenderCommand
	{   
	public:
		RenderCommand();
		~RenderCommand();
		virtual void Draw() ;
		virtual void BlindTexture();
		virtual void LoadTexture();
		virtual void Release();
		virtual void LoadVertexArry();
		virtual void Init();
	};
}