#pragma once
#include"rendercommand.h"
#include"texture.h"
#include"render.h"
namespace myrender
{
	class RenderTriangle :public RenderCommand
	{
	public:
		RenderTriangle();
		~RenderTriangle();
		void Init(Texture* texture, Triangle_Data* triangle);
		void SetTriangleData(Triangle_Data *data);
		void Init(Texture* texture, Triangle_Data_WithOut_Indics* triangle);
		void SetTexture(Texture* texture);
		void SetTriangleData(Triangle_Data_WithOut_Indics *data);
		void SetShader(int shader);
		void SetTransform(glm::mat4 t);
		virtual void LoadTexture();
		virtual void Draw();
		virtual void Release();
		virtual void LoadVertexArry();
	private:
		Triangle_Data * _triangle;
		Triangle_Data_WithOut_Indics *_triangle_i;
		TEXTUREVECTOR _texture_vector;
		GLuint _buffers_VAO;
		GLuint _buffers_VBO[2]; //0: vertex  1: indices
		int    _shader;
		glm::mat4 _transform;
	};
}