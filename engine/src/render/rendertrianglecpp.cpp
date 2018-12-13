#include"../../include/render/rendertriangle.h"
using namespace myrender;
RenderTriangle::RenderTriangle()
{

}
RenderTriangle::~RenderTriangle()
{

}
void myrender::RenderTriangle::Init(Texture * texture, Triangle_Data * triangle)
{
	_texture_vector.push_back(texture);
	_triangle = triangle;
}
void myrender::RenderTriangle::SetTriangleData(Triangle_Data * data)
{
	_triangle = data;
}
void myrender::RenderTriangle::Init(Texture * texture, Triangle_Data_WithOut_Indics * triangle)
{
	_texture_vector.push_back(texture);
	_triangle_i = triangle;
}
void myrender::RenderTriangle::SetTexture(Texture * texture)
{
	_texture_vector.push_back(texture);
}
void myrender::RenderTriangle::SetTexture(const int & textureid)
{
	auto texturemanager = Root::getInstance()->getTextureManager();
	auto texture = texturemanager->GetTextureByID(textureid);
	if (texture != nullptr)
	{
		_texture_vector.push_back(texture);
	}
}
void myrender::RenderTriangle::SetMaterial(const Material &m)
{
	_material = m;
}
void myrender::RenderTriangle::SetTriangleData(Triangle_Data_WithOut_Indics * data)
{
	_triangle_i = data;
}

void myrender::RenderTriangle::SetTransform(glm::mat4 t)
{
	_transform = t;
}

void myrender::RenderTriangle::SetMaterialShader()
{
	auto render = myrender::Render::getInstance();
	int shader;
	if (_commandtype == Triangle_command_type::BOX)
	{
		shader = render->GetShaderByName("pointlighting");
		render->setShaderproperty(shader, "material.diffuse", _material.diffuse - 1);
		render->setShaderproperty(shader, "material.specular", _material.specular - 1);
		render->setShaderproperty(shader, "material.shininess", _material.shininess);
		shader = render->GetShaderByName("directionlighting");
		render->setShaderproperty(shader, "material.diffuse", _material.diffuse - 1);
		render->setShaderproperty(shader, "material.specular", _material.specular - 1);
		render->setShaderproperty(shader, "material.shininess", _material.shininess);
	}
	else if (_commandtype == Triangle_command_type::SKYBOX)
	{
		shader = render->GetShaderByName("skybox");

	}

}

void myrender::RenderTriangle::SetCommandType(Triangle_command_type t)
{
	_commandtype = t;
}




void myrender::RenderTriangle::LoadTexture()
{
	for (auto &it : _texture_vector)
	{
		it->LoadTexture();
	}
}
void myrender::RenderTriangle::Draw()
{
	auto render = myrender::Render::getInstance();
	for (auto &it : _texture_vector)
	{
		it->BlindTexture();
	}
	render->SetLightModel(_transform);
	SetMaterialShader();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
}
void myrender::RenderTriangle::Release()
{
	for (auto &it : _texture_vector)
	{
		it->Release();
	}
}

void myrender::RenderTriangle::LoadVertexArry()
{
	glGenVertexArrays(1, &_buffers_VAO);
	glGenBuffers(1, &_buffers_VBO[0]);

	glBindVertexArray(_buffers_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _buffers_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, _triangle_i->quad_size, _triangle_i->quad, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
