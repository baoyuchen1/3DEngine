#pragma once
#include"../unit/object.h"
#include"../constant/engine_constant.h"
#include"shader.h"
#include"../root.h"
#include<string>

namespace myrender
{
	class Texture :public Object
	{
	public:
		Texture();
		~Texture();
		Texture(STRING texture_path, STRING texture_type, const int& nrComponents = 3, GLenum GLtype = GL_TEXTURE_2D);
		Texture(const char* texture_path, const char* type);
		const STRING GetPath();
		const STRING GetTextureType();
		void SetTextureType(const STRING &type);
		int GetWidth();
		int GetHeight();
		void SetUseMipmp(bool enable);
		void SetTextureEnable(bool enable);
		bool GetEnable();
		int GetTextureTarget();
		void BlindTexture();
		void Init(STRING texture_path, STRING texture_type, const int& nrComponents = 3, GLenum GLtype = GL_TEXTURE_2D);
		bool LoadTexture();
		bool LoadCubeTexture();
		GLuint GetTextureIndex();
		virtual void Release();
	private:
		static unsigned int _index;
		Texture_Data _textureData;
	};
}