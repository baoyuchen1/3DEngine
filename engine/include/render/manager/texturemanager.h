#pragma once
#include"../../constant/engine_constant.h"
namespace myrender
{
	class Texture;
	class TextureManager
	{
	public:
		~TextureManager();
		static TextureManager* getInstance();
		bool CheckTextureExist(char* name);
		void BlindTexture();
		GLuint SetTexture(char* t);
		GLuint SetCubeTexture(char* t);
		Texture* GetTextureByID(const int& textureid);
		const VECTOR<STRING>& GettgaCubeTexturePath();
	private:
		static TextureManager* _instance;
		TextureManager();
		TEXTUREMAP        _textureMap;
		VECTOR<STRING> tgaCubeTexturePath;
	};

}