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
	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	_textureData.width = FreeImage_GetWidth(dib);
	_textureData.height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (_textureData.width == 0) || (_textureData.height == 0))
		return false;

	glGenTextures(1, &_textureData.texture);
	glBindTexture(GL_TEXTURE_2D, _textureData.texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _textureData.width, _textureData.height,
		0, GL_BGR, GL_UNSIGNED_BYTE, bits);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_textureData.textureType = GL_TEXTURE_2D;
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

		_textureData.textureType = GL_TEXTURE_CUBE_MAP;
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

