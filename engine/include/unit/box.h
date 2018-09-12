#pragma once
#include"modelbase.h"
#include"../render/render.h"
#include"../root.h"
namespace myrender {
	class Box:public ModelBase
	{
	public:
		Box();
		~Box();
		void InitTexture(char * imagepath);
		int LoadTexture();
		void InitVertices(float* vertices, float* indics,int indicssize);
		void draw();
	private:
		void _initVAO();
		Box_Quad_Type* _quads;
		unsigned int* _indics;
		int _indicssize;
		GLuint _VAO;
		GLuint _VBO;
		GLuint _EBO;
		TEXTUREVECTOR _texturevector;
	};

}