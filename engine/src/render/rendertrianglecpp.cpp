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
void myrender::RenderTriangle::SetTriangleData(Triangle_Data_WithOut_Indics * data)
{
	_triangle_i = data;
}

void myrender::RenderTriangle::SetShader(int shader)
{
	_shader = shader;
}

void myrender::RenderTriangle::SetTransform(glm::mat4 t)
{
	_transform = t;
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
	render->setShaderproperty(_shader, "model", _transform);
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
	/*glGenVertexArrays(1, &_buffers_VAO);
	glGenBuffers(1, &_buffers_VBO[0]);
	glGenBuffers(1, &_buffers_VBO[1]);

	glBindVertexArray(_buffers_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _buffers_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, _triangle->quad_size, _triangle->quad, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffers_VBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _triangle->indics_size, _triangle->indics, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_V3F_V2F), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_V3F_V2F), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_V3F_V2F), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	*/
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
