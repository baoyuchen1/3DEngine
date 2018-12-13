#pragma once
#include"includefile.h"
#define PROJECT_PATH  "C:\Users\baoyuchen\Documents\Visual Studio 2017\Projects\My3Dproject\My3Dproject"
#define SHADER_PATH   STRING("./resource/shader/")
#define FSSUFFIX      STRING(".fs")
#define VSSUFFIX      STRING(".vs")
#define TEXTUREVECTOR     std::vector<Texture*>
#define LIGHTINGVECTOR    std::vector<Lighting*>
#define TEXTUREMAP     std::map<int,myrender::Texture*>
#define TEXTUREVECTORITOR  std::vector<Texture*>::iterator
#define SHADERPROVECTOR    std::vector<ShaderProperty>
#define RENDERQUADVECTOR   std::vector<RenderCommand*>
#define RENDERQUADVECTORITOR   std::vector<RenderCommand*>::iterator
#define RENDERTRIANGLEQUADVECTOR   std::vector<RenderTriangle>
#define KEYBOARDFUNC        std::function<void(int)>
#define MOUSEMOVEFUNC      std::function<void(MouseMoveEvent)>
#define MOUSESCROLLFUNC      std::function<void(MouseScrollEvent)>
#define VBO_SIZE      65535
#define INDICE_SIZE   65535
#define STRING        std::string
#define VECTOR        std::vector
#define MAP           std::map
#define VEC3          glm::vec3
#define MAT4          glm::mat4
#define PERSPECTIVE   glm::perspective
#define FLOAT         GLfloat
#define BOOL          GLboolean
#define INITMAT        glm::make_mat4x4(InitMat4)
static GLfloat InitMat4[] =
{       
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1,
};

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

struct V3F_V2F
{
	union
	{
		struct
		{
			glm::vec3 pos;
			glm::vec2 textcoord;
		};
		float M[5];
	};

};

enum Lighting_type
{
	BASELIGHTING,
	POINTLIGHTING,
	DIRECTIONLIGHTING,
};

enum Material_enum
{
	DIFFUSE,
	SPECULAR,
};

enum Triangle_command_type
{
	BOX,
	SKYBOX,
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
	unsigned int*   indics;
	int indics_size;
	int quad_size;
};

struct Triangle_Data_WithOut_Indics
{
	V3F_V2F *quad;
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

struct Material
{
	int diffuse;
	int specular;
	float     shininess;
};
enum KeyBoardCode
{
	KEY_SPACE = 32,
	KEY_APOSTROPHE = 39,  /* ' */
	KEY_COMMA = 44,  /* , */
	KEY_MINUS = 45,  /* - */
	KEY_PERIOD = 46,  /* . */
	KEY_SLASH = 47,  /* / */
	KEY_0 = 48,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57,
	KEY_SEMICOLON = 59,  /* ; */
	KEY_EQUAL = 61,  /* = */
	KEY_A = 65,
	KEY_B = 66,
	KEY_C = 67,
	KEY_D = 68,
	KEY_E = 69,
	KEY_F = 70,
	KEY_G = 71,
	KEY_H = 72,
	KEY_I = 73,
	KEY_J = 74,
	KEY_K = 75,
	KEY_L = 76,
	KEY_M = 77,
	KEY_N = 78,
	KEY_O = 79,
	KEY_P = 80,
	KEY_Q = 81,
	KEY_R = 82,
	KEY_S = 83,
	KEY_T = 84,
	KEY_U = 85,
	KEY_V = 86,
	KEY_W = 87,
	KEY_X = 88,
	KEY_Y = 89,
	KEY_Z = 90,
	KEY_LEFT_BRACKET = 91,  /* [ */
	KEY_BACKSLASH = 92, /* \ */
	KEY_RIGHT_BRACKET = 93,  /* ] */
	KEY_GRAVE_ACCENT = 96,  /* ` */
	KEY_WORLD_1 = 161, /* non-US #1 */
	KEY_WORLD_2 = 162, /* non-US #2 */

					   /* Function keys */
					   KEY_ESCAPE = 256,
					   KEY_ENTER = 257,
					   KEY_TAB = 258,
					   KEY_BACKSPACE = 259,
					   KEY_INSERT = 260,
					   KEY_DELETE = 261,
					   KEY_RIGHT = 262,
					   KEY_LEFT = 263,
					   KEY_DOWN = 264,
					   KEY_UP = 265,
					   KEY_PAGE_UP = 266,
					   KEY_PAGE_DOWN = 267,
					   KEY_HOME = 268,
					   KEY_END = 269,
					   KEY_CAPS_LOCK = 280,
					   KEY_SCROLL_LOCK = 281,
					   KEY_NUM_LOCK = 282,
					   KEY_PRINT_SCREEN = 283,
					   KEY_PAUSE = 284,
					   KEY_F1 = 290,
					   KEY_F2 = 291,
					   KEY_F3 = 292,
					   KEY_F4 = 293,
					   KEY_F5 = 294,
					   KEY_F6 = 295,
					   KEY_F7 = 296,
					   KEY_F8 = 297,
					   KEY_F9 = 298,
					   KEY_F10 = 299,
					   KEY_F11 = 300,
					   KEY_F12 = 301,
					   KEY_F13 = 302,
					   KEY_F14 = 303,
					   KEY_F15 = 304,
					   KEY_F16 = 305,
					   KEY_F17 = 306,
					   KEY_F18 = 307,
					   KEY_F19 = 308,
					   KEY_F20 = 309,
					   KEY_F21 = 310,
					   KEY_F22 = 311,
					   KEY_F23 = 312,
					   KEY_F24 = 313,
					   KEY_F25 = 314,
					   KEY_KP_0 = 320,
					   KEY_KP_1 = 321,
					   KEY_KP_2 = 322,
					   KEY_KP_3 = 323,
					   KEY_KP_4 = 324,
					   KEY_KP_5 = 325,
					   KEY_KP_6 = 326,
					   KEY_KP_7 = 327,
					   KEY_KP_8 = 328,
					   KEY_KP_9 = 329,
					   KEY_KP_DECIMAL = 330,
					   KEY_KP_DIVIDE = 331,
					   KEY_KP_MULTIPLY = 332,
					   KEY_KP_SUBTRACT = 333,
					   KEY_KP_ADD = 334,
					   KEY_KP_ENTER = 335,
					   KEY_KP_EQUAL = 336,
					   KEY_LEFT_SHIFT = 340,
					   KEY_LEFT_CONTROL = 341,
					   KEY_LEFT_ALT = 342,
					   KEY_LEFT_SUPER = 343,
					   KEY_RIGHT_SHIFT = 344,
					   KEY_RIGHT_CONTROL = 345,
					   KEY_RIGHT_ALT = 346,
					   KEY_RIGHT_SUPER = 347,
					   KEY_MENU = 348,
};