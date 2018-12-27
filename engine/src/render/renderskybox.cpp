#include"../../include/render/renderskybox.h"

using namespace myrender;
RenderSkybox::RenderSkybox()
{

}

myrender::RenderSkybox::~RenderSkybox()
{
}

void myrender::RenderSkybox::SetTexture(Texture * texture)
{
	_texture_vector.push_back(texture);
}

void myrender::RenderSkybox::SetTexture(const int & textureid)
{
	auto texturemanager = Root::getInstance()->getTextureManager();
	auto texture = texturemanager->GetTextureByID(textureid);
	if (texture != nullptr)
	{
		_texture_vector.push_back(texture);
	}
}

void myrender::RenderSkybox::SetTriangleData(Triangle_Data_WithOut_Indics * data)
{
}

void myrender::RenderSkybox::SetTransform(glm::mat4 t)
{
	_transform = t;
}

void myrender::RenderSkybox::SetVAO(const int & vao)
{
	_buffers_VAO = vao;
}

void myrender::RenderSkybox::LoadTexture()
{
	for (auto &it : _texture_vector)
	{
		it->LoadTexture();
	}
}

void myrender::RenderSkybox::Draw()
{
	
	glDepthFunc(GL_LEQUAL);
	glBindVertexArray(_buffers_VAO);
	auto render = myrender::Render::getInstance();
	for (auto &it : _texture_vector)
	{
		it->BlindTexture();
	}
	int shader = render->GetShaderIDByName("skybox");
	render->UseShader("skybox");
	render->setShaderproperty(shader, "view", glm::mat4(glm::mat3(render->GetViewMat())));
	render->setShaderproperty(shader, "projection", render->GetProjectionMat());

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}

void myrender::RenderSkybox::Release()
{
}

void myrender::RenderSkybox::LoadVertexArry()
{
}
