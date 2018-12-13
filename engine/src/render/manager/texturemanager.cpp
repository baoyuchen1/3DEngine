#include"../../../include/render/manager/texturemanager.h"
#include"../../../include/render/texture.h"
using namespace myrender;
TextureManager* TextureManager::_instance = nullptr;
TextureManager::TextureManager()
{
	tgaCubeTexturePath =
	{
		/*"_rt.tga",
		"_lf.tga",
		"_up.tga",
		"_dn.tga",
		"_ft.tga",
		"_bk.tga",*/
		
		
		"right.jpg",
		"left.jpg",
		
		
		"bottom.jpg",
		"top.jpg",
		"front.jpg",
		"back.jpg",
	};
}
TextureManager::~TextureManager()
{

}
TextureManager * myrender::TextureManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new TextureManager();
	return _instance;
}
bool myrender::TextureManager::CheckTextureExist(char * name)
{
	for (auto &it : _textureMap)
	{
		if (it.second->GetPath().c_str() == name)
			return false;
	}
	return true;
}

void myrender::TextureManager::BlindTexture()
{
	for (auto &it : _textureMap)
	{
		it.second->BlindTexture();

	}
}

GLuint myrender::TextureManager::SetTexture(char * t)
{
	if (t == nullptr)
		return -1;

	if (CheckTextureExist(t))
	{
		auto texture = new Texture();
		texture->Init(t);
		texture->LoadTexture();
		_textureMap[texture->GetTextureIndex()] = texture;
		return texture->GetTextureIndex();
	}
	return -1;
}

GLuint myrender::TextureManager::SetCubeTexture(char * t)
{

	if (t == nullptr)
		return -1;

	if (CheckTextureExist(t))
	{
		auto texture = new Texture();
		texture->Init(t);
		texture->LoadCubeTexture();
		_textureMap[texture->GetTextureIndex()] = texture;
		return texture->GetTextureIndex();
	}
	return -1;
}

Texture * myrender::TextureManager::GetTextureByID(const int & textureid)
{
	return _textureMap[textureid];
}

const VECTOR<STRING>& myrender::TextureManager::GettgaCubeTexturePath()
{
	return tgaCubeTexturePath;
}
