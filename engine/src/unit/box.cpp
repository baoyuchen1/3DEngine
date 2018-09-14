#include"../../include/unit/box.h"
#define STB_IMAGE_IMPLEMENTATION
using namespace myrender;
Box::Box()
{
	_triangle_data = new Triangle_Data();
	_texture = new Texture();
	_command = new RenderTriangle();
	//_initVAO();
}

myrender::Box::~Box()
{
	delete _quads;
	delete[] _indics;
}

void myrender::Box::InitTexture(char * imagepath)
{
	_texture->Init(imagepath);
	_command->Init(_texture, _triangle_data);
	_command->LoadTexture();
}

int myrender::Box::LoadTexture()
{
	_command->LoadTexture();
	return 0;
}

void myrender::Box::InitVertices(float* vertices, unsigned short* indics, int indicssize, int vertocessize)
{
	_triangle_data->quad_size = vertocessize;
	_triangle_data->quad = new V3F_V3F_V2F[vertocessize / sizeof(V3F_V3F_V2F)];
	_triangle_data->indics = new unsigned short[indicssize / sizeof(float)];
	memcpy(_triangle_data->quad, vertices, vertocessize);
	_triangle_data->indics_size = indicssize;
	memcpy(_triangle_data->indics, indics, indicssize);
	_command->SetTriangleData(_triangle_data);
	_command->LoadVertexArry();
}

void myrender::Box::draw()
{
	auto render = Render::getInstance();
	_command->Init(_texture, _triangle_data);
	render->AddRenderCommand(_command);
}

void myrender::Box::Release()
{
}



void myrender::Box::_initVAO()
{
	glDeleteBuffers(2, &_VBO);
	glDeleteVertexArrays(1, &_VAO);
	glBindVertexArray(0);
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Box_Quad_Type)*VBO_SIZE, _quads, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicssize*VBO_SIZE, _indics, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
