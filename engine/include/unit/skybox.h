#pragma once
#include"modelbase.h"
#include"../render/render.h"
#include"../root.h"
#include"../render/texture.h"
#include"../render/rendertriangle.h"
namespace myrender {
	class RenderSkybox;
	class SkyBox :public ModelBase
	{
	public:
		SkyBox();
		virtual ~SkyBox();
		virtual void InitTexture(char * imagepath);
		virtual int LoadTexture();
		void InitVertices(float* vertices, unsigned int* indics, int indicssize, int vertocessize);
		void InitVertices(float* vertices, int vertocessize);
		void SetSkyBoxTexture(const int& textureid);
		virtual void Draw();
		virtual void Release();
	private:
		Box_Quad_Type* _quads;
		Triangle_Data* _triangle_data;
		Triangle_Data_WithOut_Indics* _triangle_data_i;
		unsigned int* _indics;
		RenderSkybox* _command;
		int _indicssize;
		glm::vec3 _world_pos;
		glm::mat4 _model_mat;
		GLuint _VAO;
		GLuint _VBO;
		GLuint _EBO;
		int _shader;
		int _textureid;
		Material _material;
		TEXTUREVECTOR _texture_vector;
	};

}