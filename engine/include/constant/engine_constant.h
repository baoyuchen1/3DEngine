#pragma once
#include"includefile.h"
#define PROJECT_PATH  "C:\Users\baoyuchen\Documents\Visual Studio 2017\Projects\My3Dproject\My3Dproject"
#define TEXTUREVECTOR     std::vector<Texture>
#define TEXTUREVECTORITOR  std::vector<Texture>::iterator
#define SHADERPROVECTOR    std::vector<ShaderProperty>
#define RENDERQUADVECTOR   std::vector<RenderCommand*>
#define RENDERQUADVECTORITOR   std::vector<RenderCommand*>::iterator
#define RENDERTRIANGLEQUADVECTOR   std::vector<RenderTriangle>
#define VBO_SIZE      65535
#define INDICE_SIZE   65535
#define STRING        std::string

struct V3F_V3F_V2F
{
	union
	{
		struct
		{
			glm::vec3 pos;
			glm::vec3 color;
			glm::vec2 textcoord;
		};
		float M[8];
	};

};

struct  Box_Quad_Type
{
	union 
	{
		struct
		{
			/// top left
			V3F_V3F_V2F    tl;
			/// bottom left
			V3F_V3F_V2F    bl;
			/// top right
			V3F_V3F_V2F    tr;
			/// bottom right
			V3F_V3F_V2F    br;
		};
		float M[32];
	};

};

struct Triangle_Data
{
	V3F_V3F_V2F *quad;
	unsigned short*   indics;
	int indics_size;
	int quad_size;
};

struct Texture_Data
{
	GLenum textureTarget;  //GL_TEXTURE0
	GLenum textureType;    //GL_TEXTURE_2D
	unsigned int texture;
	STRING texturepath;
	int width, height, nrChannels;
	bool enable;
	bool  useMipmap;
};
