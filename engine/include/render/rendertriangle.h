#pragma once
#include"rendercommand.h"
#include"texture.h"
namespace myrender
{
	class RenderTriangle :public RenderCommand
	{
	public:
		RenderTriangle();
		~RenderTriangle();
		void Init(Texture* texture, Triangle_Data* triangle);
		virtual void BlindTexture();
		virtual void LoadTexture();
		virtual void Draw();
		virtual void Release();
		virtual void LoadVertexArry();
	private:
		Triangle_Data * _triangle;
		Texture* _texture;
		GLuint _buffersVAO;
		GLuint _buffersVBO[2]; //0: vertex  1: indices
	};
}