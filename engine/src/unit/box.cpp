#include"../../include/unit/box.h"
#define STB_IMAGE_IMPLEMENTATION
using namespace myrender;
Box::Box()
{

}

myrender::Box::~Box()
{
	delete _quads;
	delete[] _indics;
}

void myrender::Box::InitTexture(char * imagepath)
{
	Texture_Data temp;
	temp.texturepath = imagepath;
	temp.enable = true;
	_texturevector.push_back(temp);
}

int myrender::Box::LoadTexture()
{
	auto root = Root::getInstance();
	auto image = root->getImage();
	image->SetFlipVerticallOnLoad(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	int i = 0;
	for (auto &it : _texturevector)
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

void myrender::Box::InitVertices(float * vertices, float * indics, int indicssize)
{
	_quads = new Box_Quad_Type();
	for (size_t i = 0; i < 32; i++)
	{
		_quads->M[i] = vertices[i];
	}
	_indicssize = indicssize;
	_indics = new unsigned int[indicssize];
	for (size_t i = 0; i < indicssize/sizeof(float); i++)
	{
		_indics[i] = indics[i];
	}
}

void myrender::Box::draw()
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Box_Quad_Type), _quads, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicssize, _indics, GL_STATIC_DRAW);
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
