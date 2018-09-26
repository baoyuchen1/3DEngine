#include"../../include/render/render.h"
#include"../../include/camera/camera.h"
namespace myrender {
	Render* Render::instance = nullptr;
	Render::Render()
	{
		_texture_map.clear();
	}
	Render * Render::getInstance()
	{
		if (instance == nullptr)
			instance = new Render();
		return instance;
	}

	void Render::Init_Render()
	{
		auto viewport = Root::getInstance()->getViewPort();
		viewport->InitViewPort();
		_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
		Camera::RegisterKeyboardCallback();
		Camera::RegisterMousemoveCallback();
		Camera::RegisterMousescrollCallback();

	}

	int Render::LoardVertexArry(float vertices[], unsigned int indices[], int verticessize, int indicessize)
	{
		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);
		glGenBuffers(1, &_EBO);

		glBindVertexArray(_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, VBO_SIZE*sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
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
		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);

		glBindVertexArray(_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, verticessize, vertices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0); // Unbind VAO
		return _VAO;
	}

	void Render::setShaderproperty(int shaderID, const std::string & name, bool value)
	{ 
		for (auto &it : OurShader)
		{
			if (it.second->ID == shaderID)
			{
				it.second->setShaderproperty(name, value);
				break;
			}
		}
	}

	void Render::setShaderproperty(int shaderID, const std::string & name, glm::mat4 value)
	{
		for (auto &it : OurShader)
		{
			if (it.second->ID == shaderID)
			{
				it.second->setShaderproperty(name, value);
				break;
			}
		}
	}


	int Render::IncludeShader(const GLchar * Path)
	{
		STRING path = STRING(Path);
		STRING vertexPath = SHADER_PATH + path + VSSUFFIX;
		STRING fragmentPath = SHADER_PATH + path + FSSUFFIX;
		auto shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
		OurShader[path] = shader;
		return shader->ID;
	}

	void Render::setShaderproperty(int shaderID, const std::string & name, float value)
	{
		for (auto &it : OurShader)
		{
			if (it.second->ID == shaderID)
			{
				it.second->setShaderproperty(name, value);
				break;
			}
		}
	}

	void Render::setShaderproperty(int shaderID, const std::string & name, int value)
	{
		for (auto &it : OurShader)
		{
			if (it.second->ID == shaderID)
			{
				it.second->setShaderproperty(name, value);
				break;
			}
		}
	}

	void Render::UseShder()
	{
		for (auto &it : OurShader)
		{
			it.second->use();
		}
	}

	void Render::Release()
	{
		glDeleteVertexArrays(1, &_VAO);
		glDeleteBuffers(1, &_VBO);
		glDeleteBuffers(1, &_EBO);
		glfwTerminate();
	}

	void Render::InitTexture(char * imagepath)
	{
	}

	void Render::AddRenderCommand(RenderCommand * command)
	{
		_command_list.push_back(command);
	}

	void Render::BlindTexture()
	{
		int shader = OurShader["transform"]->ID;
		int i = 1;
		for (auto &it : _texture_map)
		{
			it.second->BlindTexture();
			std::string res = "ourTexture" + std::to_string(i);
			setShaderproperty(shader, res, i - 1);
			i++;
		}
	}

	bool Render::CheckTextureExist(char * name)
	{
		return (_texture_map[name]==nullptr);
	}

	GLuint Render::SetTexture(char * t)
	{
		if (t == nullptr)
			return -1;

		if (CheckTextureExist(t))
		{
			auto texture = new Texture();
			texture->Init(t);
			texture->LoadTexture();
			_texture_map[t] = texture;
			return texture->GetTextureIndex();
		}
		return -1;
	}


	int Render::GetShaderByName(char * name)
	{
		if (OurShader[name])
			return OurShader[name]->ID;
		return -1;
	}

	int Render::Draw()
	{
		auto viewport = Root::getInstance()->getViewPort();
		viewport->UpdateDeltaTime();
		_view = _camera->GetViewMatrix();
		_projection = glm::make_mat4x4(InitMat4);
		int width = viewport->GetScreenWidth();
		int height = viewport->GetScreenHeight();
		_projection = glm::perspective(_camera->Zoom, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
		int shader = OurShader["transform"]->ID;
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		setShaderproperty(shader, "view", _view);
		setShaderproperty(shader, "projection", _projection);
		UseShder();
		glBindVertexArray(_VAO);
		for (auto &it : _command_list)
		{
			it->Draw();
		}
		_command_list.clear();
		glBindVertexArray(0);

		// Swap the screen buffers
		viewport->SwapBuffers();
		return 0;
	}

	void Render::SetVAO(float * vertices, int vertocessize)
	{
		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);

		glBindVertexArray(_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, vertocessize, vertices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0); // Unbind VAO
	}

	Camera * Render::GetCamera()
	{
		return _camera;
	}


}

