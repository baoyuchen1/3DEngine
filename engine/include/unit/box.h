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
		void InitVertices(float* vertices, unsigned short* indics,int indicssize,int vertocessize);
		void draw();
		void Release();
	private:
		void _initVAO();
		Box_Quad_Type* _quads;
		Triangle_Data* _triangle_data;
		unsigned int* _indics;
		RenderTriangle* _command;
		int _indicssize;
		GLuint _VAO;
		GLuint _VBO;
		GLuint _EBO;
		TEXTUREVECTOR _texturevector;
		Texture*      _texture;
	};

}