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
bool myrender::TextureManager::CheckTextureExist(STRING name)
{
	for (auto &it : _textureMap)
	{
		if (it.second->GetPath() == name)
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

GLuint myrender::TextureManager::SetTexture(STRING path, STRING type )
{

	if (CheckTextureExist(path))
	{
		auto texture = new Texture(path, type);
		texture->LoadTexture();
		_textureMap[texture->GetTextureIndex()] = texture;
		return texture->GetTextureIndex();
	}
	return -1;
}

GLuint myrender::TextureManager::SetCubeTexture(STRING path, STRING type )
{

	if (CheckTextureExist(path))
	{
		auto texture = new Texture(path, type);
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

vector<int> TextureManager::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName,string directpath)
{
	vector<int> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		str = directpath + "/"+ str.C_Str() ;
		if (CheckTextureExist(str.C_Str()))
		{   // if texture hasn't been loaded already, load it
			auto texture = new Texture(str.C_Str(), typeName);
			if (texture->LoadTexture())
			{
				texture->SetTextureType(typeName);
				_textureMap[texture->GetTextureIndex()] = texture;
				textures.push_back(texture->GetTextureIndex());
			}
		}
	}
	return textures;
}
