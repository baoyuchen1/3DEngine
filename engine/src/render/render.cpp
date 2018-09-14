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
		glBufferData(GL_ARRAY_BUFFER, VBO_SIZE*sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicessize, indices, GL_STATIC_DRAW);
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_V3F_V2F), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_V3F_V2F), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_V3F_V2F), (void*)(6 * sizeof(float)));
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
		for (auto &it : _texturevector)
		{
			if (it.GetEnable())
			{

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

	void Render::LoadTexture()
	{ 
		auto image = Image::getInstance();
		image->SetFlipVerticallOnLoad(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		for (auto &it : _texturevector)
		{
			it.LoadTexture();
		} 
	}

	void Render::InitTexture(char * imagepath)
	{
	}

	void Render::AddRenderCommand(RenderCommand * command)
	{
		_commandlist.push_back(command);
	}




	int Render::Draw()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto &it : _commandlist)
		{
			it->Draw();
		}
		UseShder();
		_commandlist.clear();
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
		return 0;
	}

}

