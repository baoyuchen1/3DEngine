#pragma once
#include"modelbase.h"
#include"../render/render.h"
#include"../root.h"
#include"../render/texture.h"
#include"../render/rendertriangle.h"
namespace myrender {
	class Box:public ModelBase
	{
	public:
		Box();
		~Box();
		void InitTexture(char * imagepath);
		int LoadTexture();
		void InitVertices(float* vertices, unsigned int* indics,int indicssize,int vertocessize);
		void InitVertices(float* vertices,int vertocessize);
		void Draw();
		void Release();
		void SetWorldPos(const glm::vec3 &p);
		void SetShader(int s);
		void MadeModelMat(glm::vec3 Pos, GLfloat angle, glm::vec3 aixs);
	private:
		Box_Quad_Type* _quads;
		Triangle_Data* _triangle_data;
		Triangle_Data_WithOut_Indics* _triangle_data_i;
		unsigned int* _indics;
		RenderTriangle* _command;
		int _indicssize;
		glm::vec3 _world_pos;
		glm::mat4 _model_mat;
		GLuint _VAO;
		GLuint _VBO;
		GLuint _EBO;
		int _shader;
		TEXTUREVECTOR _texture_vector;
	};

}