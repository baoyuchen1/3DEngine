#pragma once
#include"object.h"
#include"../constant/includefile.h"
namespace myrender
{
	class ModelBase:public Object
	{
	public:
		ModelBase();
		virtual ~ModelBase();
		void SetWorldPos(const glm::vec3 &p);
		void SetShader(int s);
		void MadeModelMat(glm::vec3 Pos, GLfloat angle, glm::vec3 aixs);
		virtual void InitTexture(char * imagepath) = 0;
		virtual int LoadTexture() = 0;
		virtual void Draw() = 0;
		virtual void Release();
	protected:
		glm::vec3 _world_pos;
		glm::mat4 _model_mat;
		int _shader;
	};

}