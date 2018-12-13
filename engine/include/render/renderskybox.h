#pragma once
#include"rendercommand.h"
#include"texture.h"
#include"render.h"
namespace myrender
{
	class RenderSkybox :public RenderCommand
	{
	public:
		RenderSkybox();
		~RenderSkybox();
		void SetTexture(Texture* texture);
		void SetTexture(const int& textureid);
		void SetTriangleData(Triangle_Data_WithOut_Indics *data);
		void SetTransform(glm::mat4 t);
		void SetVAO(const int& vao);
		virtual void LoadTexture();
		virtual void Draw();
		virtual void Release();
		virtual void LoadVertexArry();
	private:
		TEXTUREVECTOR _texture_vector;
		GLuint _buffers_VAO;
		GLuint _buffers_VBO[2]; //0: vertex  1: indices
		glm::mat4 _transform;
	};
}
