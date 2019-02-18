#include"../../include/render/render.h"
#include"../../include/camera/camera.h"
#include"../../include/render/renderskybox.h"
#include"../../include/unit/model.h"
#include"../../include/root.h"
#include"../../include/render/lighting.h"
#include"../../include/render/rendercommand.h"
namespace myrender {
	Render* Render::instance = nullptr;
	Render::Render()
	{
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
		glBindVertexArray(0);
	}
	void Render::_drawBox()
	{
		TextureManager* texturemanager = Root::getInstance()->getTextureManager();
		glBindVertexArray(_VAO);
		_drawLighting();
		_commandList.clear();

	}
	void Render::_drawModel()
	{
		Shader shader;
		glm::vec3 lightPositions[] = {
			glm::vec3(0.0f, 0.0f, 10.0f),
		};
		glm::vec3 lightColors[] = {
			glm::vec3(150.0f, 150.0f, 150.0f),
		};
		int nrRows = 7;
		int nrColumns = 7;
		float spacing = 2.5;
		for (auto &it : _modelmap)
		{
			shader = it->GetShader();
			shader.use();
			for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
			{
				glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
				newPos = lightPositions[i];
				shader.setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
				shader.setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
			}
			shader.setMat4("projection", _projection);
			shader.setMat4("view", _view);
			
			MAT4 model = glm::make_mat4x4(InitMat4);
			model = glm::translate(model, it->GetPosition());
			model = glm::scale(model, it->GetScale());
			shader.setMat4("model", model);
			it->Draw();
		}


	}
	void Render::_drawSkybox()
	{
		if(_skybox)
		_skybox->Draw();
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
		IncludeShader("skybox");
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
			if (it.second&&it.second->GetID() == shaderID)
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
		if (OurShader[path] == nullptr)
		{
			STRING vertexPath = SHADER_PATH + path + VSSUFFIX;
			STRING fragmentPath = SHADER_PATH + path + FSSUFFIX;
			auto shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
			OurShader[path] = shader;
			return shader->GetID();
		}
		return OurShader[path]->GetID();
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
			if (it.second&&it.second->GetID() == shaderID)
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


	void Render::AddRenderCommand(RenderCommand * command)
	{
		_commandList.push_back(command);
	}


	int Render::Draw()
	{
		auto viewport = Root::getInstance()->getViewPort();
		viewport->UpdateDeltaTime();
		_generateViewMat4();
		RenderBackGround();
		
		//_gpassrender = false;
		if (_gpassrender)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			Shader* gshader = GetShaderByName(_gpassShader);
			gshader->use();
			gshader->setMat4("projection", _projection);
			gshader->setMat4("view", _view);
			
			for (auto &it: _modelmap)
			{
				it->SetShader(_gpassShader);
			}
			_drawModel();
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			Shader* lshader = GetShaderByName(_lpassShader);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			lshader->use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _gPosition);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, _gNormal);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, _gAlbedoSpec);
			for (auto &it : _defereedlightlist)
			{
				it->Draw();
			}
			DeferredLighting::DrawLight();
			glBindFramebuffer(GL_READ_FRAMEBUFFER, _gBuffer);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glBlitFramebuffer(
				0, 0, viewport->GetScreenWidth(), viewport->GetScreenHeight(), 0, 0, viewport->GetScreenWidth(), viewport->GetScreenHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST
			);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else
		{
			_drawModel();
		}
		
		//_drawBox();
		_drawSkybox();
		glfwPollEvents();
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

	void Render::SetSkybox(RenderSkybox * s)
	{
		_skybox = s;
	}
	int Render::GetShaderIDByName(const STRING &shadername)
	{
		IncludeShader(shadername.c_str());
		Shader* shader = OurShader[shadername.c_str()];
		if (shader == nullptr)
			return 0;
		return shader->GetID();
	}

	Shader * Render::GetShaderByName(const STRING & shadername)
	{
		IncludeShader(shadername.c_str());
		return OurShader[shadername.c_str()];
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
			//it->SetModel(m);
		}
	}

	void Render::ReadyForDraw()
	{
		int shader = GetShaderIDByName("directionlighting");
		//OurShader["directionlighting"]->use();
	}

	void Render::SetupGBuffer(STRING GPASS, STRING LPASS)
	{
		IncludeShader(GPASS.c_str());
		IncludeShader(LPASS.c_str());
		_gpassShader = GPASS;
		_lpassShader = LPASS;
		_gpassrender = true;
		_setupGBuffer();
	}

	void Render::_setupGBuffer()
	{
		auto viewport = Root::getInstance()->getViewPort();
		int width = viewport->GetScreenWidth();
		int height = viewport->GetScreenHeight();
		Shader* shader = GetShaderByName(_lpassShader);
		if (shader != nullptr)
		{
			shader->use();
			glUniform1i(glGetUniformLocation(shader->GetID(), "gPosition"), 0);
			glUniform1i(glGetUniformLocation(shader->GetID(), "gNormal"), 1);
			glUniform1i(glGetUniformLocation(shader->GetID(), "gAlbedoSpec"), 2);
		}
		glGenFramebuffers(1, &_gBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);
		// - Position color buffer
		glGenTextures(1, &_gPosition);
		glBindTexture(GL_TEXTURE_2D, _gPosition);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _gPosition, 0);
		// - Normal color buffer
		glGenTextures(1, &_gNormal);
		glBindTexture(GL_TEXTURE_2D, _gNormal);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _gNormal, 0);
		// - Color + Specular color buffer
		glGenTextures(1, &_gAlbedoSpec);
		glBindTexture(GL_TEXTURE_2D, _gAlbedoSpec);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _gAlbedoSpec, 0);
		// - Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
		GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		glDrawBuffers(3, attachments);
		// - Create and attach depth buffer (renderbuffer)
		glGenRenderbuffers(1, &_rboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, _rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rboDepth);
		// - Finally check if framebuffer is complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		DeferredLighting::SetShader(_lpassShader);
	}

	void Render::RenderBackGround()
	{
		
		glClearColor(0.5f, 0.5f, 1.0f, 0.5f);
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

	int Render::AddModel(Model * model)
	{
		int index = 0;
		if (index >= _modelmap.max_size())
		{
			_modelmap.resize(index * 2);
		}
		if (!_lastmodel.empty())
		{
			index = _lastmodel.top();
			_lastmodel.pop();
			_modelmap[index] = model;
		}
		else
		{
			_modelmap.push_back(model);
		}
		
		return index;
	}

	void Render::RemoveModel(const int & modelid)
	{
		_modelmap[modelid] = nullptr;
		_lastmodel.push(modelid);
	}

	Shader * Render::GetGpassShader()
	{
		return nullptr;
	}

	Shader * Render::GetLpassShader()
	{
		return nullptr;
	}

	int Render::AddDefereedlight(DeferredLighting *d)
	{
		_defereedlightlist.push_back(d);
		return _defereedlightlist.size() - 1;
	}

	void Render::SetMeshMap(const STRING &p, Model *m)
	{
		_meshmap[p] = m;
	}

	VECTOR<Mesh> Render::GetMesh(const STRING &p)
	{
		if (_meshmap[p])
		{
			return _meshmap[p]->GetMesh();
		}
		return VECTOR<Mesh>();
	}


}

