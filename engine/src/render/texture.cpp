#include "..\..\include\render\texture.h"
unsigned int myrender::Texture::_index = 0;
myrender::Texture::Texture()
{
}

myrender::Texture::~Texture()
{
}

myrender::Texture::Texture(STRING texture_path, STRING texture_type, const int & nrComponents, GLenum GLtype)
{
	Init(texture_path, texture_type, nrComponents, GLtype);
}

myrender::Texture::Texture(const char * texture_path,const char* type)
{
	Init(texture_path, type);
}

const STRING myrender::Texture::GetPath()
{
	return _textureData.texturepath;
}

const STRING myrender::Texture::GetTextureType()
{
	return _textureData.textureType;
}

void myrender::Texture::SetTextureType(const STRING & type)
{
	_textureData.textureType = type;
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
	return _textureData.GLtextureType;
}

void myrender::Texture::BlindTexture()
{
	glActiveTexture(_textureData.textureTarget);
	glBindTexture(_textureData.GLtextureType, _textureData.texture);
}

void myrender::Texture::Init(STRING texture_path, STRING texture_type, const int& nrComponents, GLenum GLtype)
{
	_textureData.enable = true;
	_textureData.texturepath = texture_path;  
	_textureData.GLtextureType = GLtype;
	if (nrComponents == 1)
	{
		_textureData.image_format = GL_RED;
		_textureData.data_format = GL_RED;
	}
	else if (nrComponents == 3)
	{
		_textureData.image_format = GL_RGB;
		_textureData.data_format = GL_BGR;
	}
	else if (nrComponents == 4)
	{
		_textureData.image_format = GL_RGBA;
		_textureData.data_format = GL_BGRA;
	}
}

bool myrender::Texture::LoadTexture()
{
	auto image = Image::getInstance();
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	fif = FreeImage_GetFileType(_textureData.texturepath.c_str(), 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(_textureData.texturepath.c_str());
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, _textureData.texturepath.c_str());
	//if the image failed to load, return failure
	if (!dib)
		return false;
	int bpp = FreeImage_GetBPP(dib);
	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	_textureData.width = FreeImage_GetWidth(dib);
	_textureData.height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (_textureData.width == 0) || (_textureData.height == 0))
		return false;
		
	glGenTextures(1, &_textureData.texture);
	glBindTexture(_textureData.GLtextureType, _textureData.texture);

	glTexImage2D(_textureData.GLtextureType, 0, _textureData.image_format, _textureData.width, _textureData.height,
		0, _textureData.data_format, GL_UNSIGNED_BYTE, bits);
	// set the texture wrapping parameters
	glTexParameteri(_textureData.GLtextureType, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(_textureData.GLtextureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(_textureData.GLtextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(_textureData.GLtextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_textureData.textureTarget = GL_TEXTURE0 + _index; //?
	_textureData.enable = true;
	_index++;
	FreeImage_Unload(dib);
	return true;
}

bool myrender::Texture::LoadCubeTexture()
{
	int count = 0;
	auto texturemanager = myrender::Root::getInstance()->getTextureManager();
	glGenTextures(1, &_textureData.texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _textureData.texture);
	for (auto it : texturemanager->GettgaCubeTexturePath())
	{
		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP *dib(0);
		//pointer to the image data
		BYTE* bits(0);
		std::string texturepath = _textureData.texturepath + it;
		fif = FreeImage_GetFileType(texturepath.c_str(), 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(texturepath.c_str());
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return false;

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, texturepath.c_str());
		//if the image failed to load, return failure
		if (!dib)
			return false;
		//retrieve the image data
		bits = FreeImage_GetBits(dib);
		//get the image width and height
		_textureData.width = FreeImage_GetWidth(dib);
		_textureData.height = FreeImage_GetHeight(dib);
		//if this somehow one of these failed (they shouldn't), return failure
		if ((bits == 0) || (_textureData.width == 0) || (_textureData.height == 0))
			return false;

		_textureData.GLtextureType = GL_TEXTURE_CUBE_MAP;
		_textureData.textureTarget = GL_TEXTURE0;
		_textureData.enable = true;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+count, 0, GL_RGB, _textureData.width, _textureData.height,
			0, GL_BGR, GL_UNSIGNED_BYTE, bits);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		count++;
		FreeImage_Unload(dib);
	}

	return true;
}

GLuint myrender::Texture::GetTextureIndex()
{
	return _textureData.texture;
}

void myrender::Texture::Release()
{
}

