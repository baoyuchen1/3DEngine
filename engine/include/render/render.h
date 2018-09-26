#pragma once
#include"texture.h"
#include"rendercommand.h"
#include"../root.h"
// GLEW

namespace myrender {
	class Camera;
	class Render
	{
	public:
		static Render* getInstance();
		void Init_Render();
		int LoardVertexArry(float vertices[], unsigned int indices[],int verticessize,int indicessize);
		int LoardVertexArry(float vertices[], int verticessize);
		int IncludeShader(const GLchar*);
		void setShaderproperty(int shaderID, const std::string &name, float value);
		void setShaderproperty(int shaderID, const std::string &name, int value);
		void setShaderproperty(int shaderID, const std::string &name, bool value);
		void setShaderproperty(int shaderID, const std::string &name, glm::mat4 value);
		void UseShder();
		void Release();
		void InitTexture(char* imagepath);
		void AddRenderCommand(RenderCommand *command);
		void BlindTexture();
		bool CheckTextureExist(char* name);
		GLuint SetTexture(char* t);
		int  GetShaderByName(char* name);
		int Draw();
		void SetVAO(float * vertices, int vertocessize);
		Camera* GetCamera();
	private:
		Render();
		//把复制构造函数和=操作符也设为私有,防止被复制
		Render(const Render&);
		static Render* instance;		
		Camera*     _camera;
		unsigned int _VBO, _VAO, _EBO;
		MAP<STRING,Shader*>  OurShader;
		RENDERQUADVECTOR  _command_list;
		TEXTUREMAP        _texture_map;
		glm::mat4    _projection;
		glm::mat4    _view;
	};
}