#pragma once
#include"texture.h"
#include"rendercommand.h"
#include"../root.h"
#include"lighting.h"
// GLEW

namespace myrender {
	class Camera;
	class Lighting;
	class RenderSkybox;
	class Render
	{
	public:
		static Render* getInstance();
		void Init_Render();
		int LoardVertexArry(float vertices[], unsigned int indices[],int verticessize,int indicessize);
		int LoardVertexArry(float vertices[], int verticessize);
		int IncludeShader(const GLchar*);
		void setShaderproperty(int shaderID, const STRING &name, float value);
		void setShaderproperty(int shaderID, const STRING &name, int value);
		void setShaderproperty(int shaderID, const STRING &name, bool value);
		void setShaderproperty(int shaderID, const STRING &name, MAT4 value);
		void setShaderproperty(int shaderID, const STRING &name, VEC3 value);
		void UseShder();
		void UseShader(const STRING &name);
		void Release();
		void AddRenderCommand(RenderCommand *command);
		int  GetShaderByName(char* name);
		int Draw();
		void SetVAO(float * vertices, int vertocessize);
		Camera* GetCamera();
		GLint GetVBO();
		void SetSkybox(RenderSkybox* s);
		int GetShaderByName(STRING shadername);
		void CreatNewLighting(const VEC3 &pos, const VEC3 &color, Lighting_type);
		Lighting* GetLightByIndex(const int& index);
		void SetLightModel(const MAT4 &m);
		void ReadyForDraw();
		void RenderBackGround();
		MAT4 GetViewMat();
		MAT4 GetProjectionMat();
	private:
		Render();
		//把复制构造函数和=操作符也设为私有,防止被复制
		Render(const Render&);
		void _drawLighting();
		void _drawBox();
		void _drawSkybox();
		void _generateViewMat4();
		static Render* instance;		
		Camera*     _camera;
		unsigned int _VBO, _VAO, _EBO;
		MAP<STRING,Shader*>  OurShader;
		RENDERQUADVECTOR  _commandList;
		LIGHTINGVECTOR    _lightingList;
		RenderSkybox* _skybox;
		MAT4    _projection;
		MAT4    _view;
	};
}