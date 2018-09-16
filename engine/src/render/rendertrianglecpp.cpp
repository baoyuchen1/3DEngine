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
	_texture = texture;
	_triangle = triangle;
}
void myrender::RenderTriangle::SetTriangleData(Triangle_Data * data)
{
	_triangle = data;
}
void myrender::RenderTriangle::BlindTexture()
{
	_texture->BlindTexture();
}
void myrender::RenderTriangle::LoadTexture()
{
	_texture->LoadTexture();
}
void myrender::RenderTriangle::Draw()
{
	BlindTexture();
	auto render = myrender::Render::getInstance();
	render->UseShder();
	glBindVertexArray(_buffersVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void myrender::RenderTriangle::Release()
{
	_texture->Release();
}

void myrender::RenderTriangle::LoadVertexArry()
{
	glGenVertexArrays(1, &_buffersVAO);
	glGenBuffers(1, &_buffersVBO[0]);
	glGenBuffers(1, &_buffersVBO[1]);

	glBindVertexArray(_buffersVAO);

	glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, _triangle->quad_size, _triangle->quad, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
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
}
