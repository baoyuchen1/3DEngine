#pragma once
namespace myrender {
	class RenderCommand
	{   
	public:
		RenderCommand();
		~RenderCommand();
		virtual void Draw() = 0;
		virtual void BlindTexture() = 0;
		virtual void LoadTexture() = 0;
		virtual void Release() = 0;
		virtual void LoadVertexArry() = 0;
	};
}