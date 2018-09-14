#include "..\..\include\render\texture.h"
unsigned int myrender::Texture::_index = 0;
myrender::Texture::Texture()
{
}

myrender::Texture::~Texture()
{
}

myrender::Texture::Texture(const char * texture_path)
{
	Init(texture_path);
}

const STRING myrender::Texture::GetPath()
{
	return _textureData.texturepath;
}

int myrender::Texture::GetWidth()
{
	return _textureData.width;
}

int myrender::Texture::GetHeight()
{
	return _textureData.height;
}

void myrender::Texture::SetUseMipmp(bool enable)
{
	_textureData.useMipmap = enable;
}

void myrender::Texture::SetTextureEnable(bool enable)
{
	_textureData.enable = enable;
}

bool myrender::Texture::GetEnable()
{
	return _textureData.enable;
}

int myrender::Texture::GetTextureTarget()
{
	return _textureData.textureType;
}

void myrender::Texture::BlindTexture()
{
	glActiveTexture(_textureData.textureTarget);
	glBindTexture(_textureData.textureType, _textureData.texture);
}

void myrender::Texture::Init(STRING texture_path)
{
	_textureData.enable = true;
	_textureData.texturepath = texture_path;  
}

void myrender::Texture::LoadTexture()
{
	auto image = Image::getInstance();
	glGenTextures(1, &_textureData.texture);
	glBindTexture(GL_TEXTURE_2D, _textureData.texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char *data = image->LoadImageData(_textureData.texturepath.c_str(), &_textureData.width, &_textureData.height, &_textureData.nrChannels, 0);
	if (data)
	{
		_textureData.textureType = GL_TEXTURE_2D;
		_textureData.textureTarget = GL_TEXTURE0 + _index;
		_textureData.enable = true;
		_index++;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _textureData.width, _textureData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		_textureData.enable = false;
		std::cout << "Failed to load texture" << std::endl;
	}
	image->FreeImage(data);
}

void myrender::Texture::Release()
{
}

