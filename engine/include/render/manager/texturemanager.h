#pragma once
#include"../../constant/engine_constant.h"
using namespace std;
namespace myrender
{
	class Texture;
	class TextureManager
	{
	public:
		~TextureManager();
		static TextureManager* getInstance();
		bool CheckTextureExist(STRING name);
		void BlindTexture();
		GLuint SetTexture(STRING path,STRING type = STRING());
		GLuint SetCubeTexture(STRING path, STRING type = STRING());
		Texture* GetTextureByID(const int& textureid);
		const VECTOR<STRING>& GettgaCubeTexturePath();
		vector<int> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName,string directpath);
	private:
		static TextureManager* _instance;
		TextureManager();
		TEXTUREMAP        _textureMap;
		VECTOR<STRING> tgaCubeTexturePath;
	};

}