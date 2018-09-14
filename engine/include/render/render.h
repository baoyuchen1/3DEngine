#pragma once
#include"texture.h"
#include"rendercommand.h"
namespace myrender {
	class Render
	{
	public:
		static Render* getInstance();
		GLFWwindow* Init_Render(GLFWframebuffersizefun framebuffer_size_callback);
		int LoardVertexArry(float vertices[], unsigned int indices[],int verticessize,int indicessize);
		int LoardVertexArry(float vertices[], int verticessize);
		int IncludeShader(const GLchar* vertexPath, const GLchar* fragmentPath);
		void setShaderproperty(int shaderID, const std::string &name, float value);
		void setShaderproperty(int shaderID, const std::string &name, int value);
		void setShaderproperty(int shaderID, const std::string &name, bool value);
		void BindTexture();
		void UseShder();
		void Release();
		void LoadTexture();
		void InitTexture(char* imagepath);
		void AddRenderCommand(RenderCommand *command);
		int Draw();
	private:
		Render();
		//�Ѹ��ƹ��캯����=������Ҳ��Ϊ˽��,��ֹ������
		Render(const Render&);
		static Render* instance;		
		GLFWwindow* window;
		int view_weight;
		int view_height;		
		unsigned int VBO, VAO, EBO;
		std::vector<Shader*>  OurShader;
        TEXTUREVECTOR     _texturevector;
		RENDERQUADVECTOR  _commandlist;
	};
}