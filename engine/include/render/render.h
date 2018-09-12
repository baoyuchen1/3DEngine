#pragma once

#include "../constant/includefile.h"
#include "../render/shader.h"
#include "../render/image.h"
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
		int LoadTexture();
		int InitTexture(char* imagepath);
		int Draw();
	private:
		Render();
		//把复制构造函数和=操作符也设为私有,防止被复制
		Render(const Render&);
		static Render* instance;		
		GLFWwindow* window;
		int view_weight;
		int view_height;		
		unsigned int VBO, VAO, EBO;
		std::vector<Shader*>  OurShader;
        TEXTUREVECTOR     texturevector;
	};
}