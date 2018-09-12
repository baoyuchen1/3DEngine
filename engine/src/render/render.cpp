#include"../../include/render/render.h"
namespace myrender {
	Render* Render::instance = nullptr;
	Render::Render()
	{
		view_weight = 960;
		view_height = 720;
	}
	Render * Render::getInstance()
	{
		if (instance == nullptr)
			instance = new Render();
		return instance;
	}

	GLFWwindow* Render::Init_Render(GLFWframebuffersizefun framebuffer_size_callback)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
		window = glfwCreateWindow(view_weight, view_height, "LearnOpenGL", NULL, NULL);
		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return nullptr;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return nullptr;
		}
		return window;
	}

	int Render::LoardVertexArry(float vertices[], unsigned int indices[], int verticessize, int indicessize)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verticessize, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicessize, indices, GL_STATIC_DRAW);
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		return 0;
	}

	int Render::LoardVertexArry(float vertices[], int verticessize)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verticessize, vertices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		return 0;
	}

	void Render::setShaderproperty(int shaderID, const std::string & name, bool value)
	{ 
		for (auto &it : OurShader)
		{
			if (it->ID == shaderID)
			{
				it->setShaderproperty(name, value);
				break;
			}
		}
	}

	void Render::BindTexture()
	{
		for (auto &it : texturevector)
		{
			if (it.enable)
			{
				glActiveTexture(it.textureTarget);
				glBindTexture(it.textureType, it.texture);
			}
		}
	}

	int Render::IncludeShader(const GLchar * vertexPath, const GLchar * fragmentPath)
	{
		auto shader = new Shader(vertexPath, fragmentPath);
		OurShader.push_back(shader);
		return shader->ID;
	}

	void Render::setShaderproperty(int shaderID, const std::string & name, float value)
	{
		for (auto &it : OurShader)
		{
			if (it->ID == shaderID)
			{
				it->setShaderproperty(name, value);
				break;
			}
		}
	}

	void Render::setShaderproperty(int shaderID, const std::string & name, int value)
	{
		for (auto &it : OurShader)
		{
			if (it->ID == shaderID)
			{
				it->setShaderproperty(name, value);
				break;
			}
		}
	}

	void Render::UseShder()
	{
		for (auto &it : OurShader)
		{
			it->use();
		}
	}

	void Render::Release()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glfwTerminate();
	}

	int Render::LoadTexture()
	{ 
		auto image = Image::getInstance();
		image->SetFlipVerticallOnLoad(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		int i = 0;
		for (auto &it : texturevector)
		{
			glGenTextures(1, &it.texture);
			glBindTexture(GL_TEXTURE_2D, it.texture);
			// set the texture wrapping parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			// set texture filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			unsigned char *data = image->LoadImageData(it.texturepath.c_str(), &it.width, &it.height, &it.nrChannels, 0);
			if (data)
			{
				it.textureType = GL_TEXTURE_2D;
				it.textureTarget = GL_TEXTURE0 + i;
				it.enable = true;
				i++;
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, it.width, it.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{   
				it.enable = false;
				std::cout << "Failed to load texture" << std::endl;
			}
			image->FreeImage(data);
		}
		return 0;
	}

	int Render::InitTexture(char * imagepath)
	{
		Texture_Data temp;
		temp.texturepath = imagepath;
		temp.enable = true;
		texturevector.push_back(temp);
		return 0;
	}


	int Render::Draw()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// bind textures on corresponding texture units
		BindTexture();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		UseShder();
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
		return 0;
	}

}
