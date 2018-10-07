#include"../../include/render/render.h"
#include"../../include/camera/camera.h"
namespace myrender {
	Render* Render::instance = nullptr;
	Render::Render()
	{
		_textureMap.clear();
	}
	Render::Render(const Render &)
	{
	}
	void Render::_drawLighting()
	{	

		for (auto &it : _lightingList)
		{
			it->SetViewPos(_camera->Position);
			it->Draw();
			for (auto &it : _commandList)
			{
				it->Draw();
			}
			
		}
	}
	void Render::_drawBox()
	{
		BlindTexture();
		glBindVertexArray(_VAO);
		_drawLighting();
		_commandList.clear();
		glBindVertexArray(0);
		int shader = GetShaderByName("transform");
		UseShader("transform");
		setShaderproperty(shader, "view", _view);
		setShaderproperty(shader, "projection", _projection);
		glBindVertexArray(Lighting::GetVAO());
		for (auto &it : _lightingList)
		{
			MAT4 model = INITMAT;
			model = glm::translate(model, it->GetPos());
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			setShaderproperty(shader, "model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		glBindVertexArray(0);
	}
	void Render::_generateViewMat4()
	{
		auto viewport = Root::getInstance()->getViewPort();
		_view = _camera->GetViewMatrix();
		_projection = glm::make_mat4x4(InitMat4);
		int width = viewport->GetScreenWidth();
		int height = viewport->GetScreenHeight();
		_projection = PERSPECTIVE(_camera->Zoom, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
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
		
		IncludeShader("pointlighting");
		IncludeShader("directionlighting");
		IncludeShader("transform");	
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

		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, verticessize, vertices, GL_STATIC_DRAW);

		glBindVertexArray(_VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
		return _VAO;
	}

	void Render::setShaderproperty(int shaderID, const STRING & name, bool value)
	{ 
		for (auto &it : OurShader)
		{
			if (it.second->GetID() == shaderID)
			{
				it.second->setShaderproperty(name, value);
				break;
			}
		}
	}

	void Render::setShaderproperty(int shaderID, const STRING & name, MAT4 value)
	{
		for (auto &it : OurShader)
		{
			if (it.second->GetID() == shaderID)
			{
				it.second->setShaderproperty(name, value);
				break;
			}
		}
	}

	void Render::setShaderproperty(int shaderID, const STRING & name, VEC3 value)
	{
		for (auto &it : OurShader)
		{
			if (it.second->GetID() == shaderID)
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
		return shader->GetID();
	}

	void Render::setShaderproperty(int shaderID, const STRING & name, float value)
	{
		for (auto &it : OurShader)
		{
			if (it.second->GetID() == shaderID)
			{
				it.second->setShaderproperty(name, value);
				break;
			}
		}
	}

	void Render::setShaderproperty(int shaderID, const STRING & name, int value)
	{
		for (auto &it : OurShader)
		{
			if (it.second->GetID() == shaderID)
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

	void Render::UseShader(const STRING & name)
	{
		Shader* shader = OurShader[name];
		if (shader != nullptr)
		{
			shader->use();
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
		_commandList.push_back(command);
	}

	void Render::BlindTexture()
	{
		int shader = OurShader["transform"]->GetID();
		int i = 1;
		for (auto &it : _textureMap)
		{
			it.second->BlindTexture();
			/*std::string res = "ourTexture" + std::to_string(i);
			setShaderproperty(shader, res, i - 1);*/
			i++;
		}
	/*	 shader = OurShader["lighting"]->GetID();
		i = 1;
		for (auto &it : _textureMap)
		{
			std::string res = "ourTexture" + std::to_string(i);
			setShaderproperty(shader, res, i - 1);
			i++;
		}*/
	}

	bool Render::CheckTextureExist(char * name)
	{
		return (_textureMap[name]==nullptr);
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
			_textureMap[t] = texture;
			return texture->GetTextureIndex();
		}
		return -1;
	}


	int Render::GetShaderByName(char * name)
	{
		if (OurShader[name])
			return OurShader[name]->GetID();
		return -1;
	}

	int Render::Draw()
	{
		auto viewport = Root::getInstance()->getViewPort();
		viewport->UpdateDeltaTime();
		_generateViewMat4();
		RenderBackGround();
		_drawBox();
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

	GLint Render::GetVBO()
	{
		return _VBO;
	}

	int Render::GetShaderByName(STRING shadername)
	{
		Shader* shader = OurShader[shadername.c_str()];
		if (shader == nullptr)
			return 0;
		return shader->GetID();
	}

	void Render::CreatNewLighting(const VEC3 & pos, const VEC3 & color, Lighting_type l_type = Lighting_type::BASELIGHTING)
	{
		Lighting* light = nullptr;
		if (Lighting_type::BASELIGHTING == l_type)
		{
			light = new Lighting(color, pos);
		}
		else if (Lighting_type::POINTLIGHTING == l_type)
		{
			light = new PointLighting(color,pos);
		}
		else if (Lighting_type::DIRECTIONLIGHTING == l_type)
		{
			light = new DirectionLighting(color, pos);
		}
		else
		{
			return;
		}
		_lightingList.push_back(light);
		light->SetIndex(_lightingList.size() - 1);
		Lighting::SetVBO(_VBO);
	}

	Lighting * Render::GetLightByIndex(const int & index)
	{
		return _lightingList[index];
	}

	void Render::SetLightModel(const MAT4 & m)
	{
		for (auto &it: _lightingList)
		{
			it->SetModel(m);
		}
	}

	void Render::ReadyForDraw()
	{
		int shader = GetShaderByName("pointlighting");
		OurShader["pointlighting"]->use();
	}

	void Render::RenderBackGround()
	{
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	MAT4 Render::GetViewMat()
	{
		return _view;
	}

	MAT4 Render::GetProjectionMat()
	{
		return _projection;
	}


}

