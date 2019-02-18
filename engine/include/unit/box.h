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
		virtual ~Box();
		virtual void InitTexture(char * imagepath);
		virtual int LoadTexture();
		void InitVertices(float* vertices, unsigned int* indics,int indicssize,int vertocessize);
		void InitVertices(float* vertices,int vertocessize);
		virtual void Draw();
		virtual void Release();
		void InitMaterial(Texture* diffuse, Texture* specular, float shininess);
		void InitMaterial(int diffuse, int specular, float shininess);
	private:
		Box_Quad_Type* _quads;
		Triangle_Data* _triangle_data;
		Triangle_Data_WithOut_Indics* _triangle_data_i;
		unsigned int* _indics;
		RenderTriangle* _command;
		int _indicssize;
		GLuint _VAO;
		GLuint _VBO;
		GLuint _EBO;
		Material _material;
		std::map<int, bool > *_texture_vector;
	};

}