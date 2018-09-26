#pragma once
#include"../unit/object.h"
#include"../constant/engine_constant.h"
#include"shader.h"
#include"image.h"
#include<string>
namespace myrender
{
	class Texture :public Object
	{
	public:
		Texture();
		~Texture();
		Texture(const char* texture_path);
		const STRING GetPath();
		int GetWidth();
		int GetHeight();
		void SetUseMipmp(bool enable);
		void SetTextureEnable(bool enable);
		bool GetEnable();
		int GetTextureTarget();
		void BlindTexture();
		void Init(STRING texture_path);
		void LoadTexture();
		GLuint GetTextureIndex();
		virtual void Release();
	private:
		static unsigned int _index;
		Texture_Data _textureData;
	};
}