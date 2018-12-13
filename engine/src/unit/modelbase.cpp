#include"../../include/unit/modelbase.h"
using namespace myrender;

myrender::ModelBase::ModelBase()
{
}

myrender::ModelBase::~ModelBase()
{
}

void myrender::ModelBase::SetWorldPos(const glm::vec3 & p)
{
	_world_pos = p;
}

void myrender::ModelBase::SetShader(int s)
{
	_shader = s;
}

void myrender::ModelBase::MadeModelMat(glm::vec3 Pos, GLfloat angle, glm::vec3 aixs)
{
	_model_mat = glm::translate(_model_mat, Pos);//����ƽ�ƾ���
	_model_mat = glm::rotate(_model_mat, angle, aixs);//������ת����
}

void myrender::ModelBase::Release()
{
}
