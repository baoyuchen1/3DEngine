#include"../../include/unit/box.h"
#define STB_IMAGE_IMPLEMENTATION
using namespace myrender;
Box::Box()
{
	_triangle_data = new Triangle_Data();
	_triangle_data_i = new Triangle_Data_WithOut_Indics();
	_command = new RenderTriangle();
	_model_mat = glm::make_mat4x4(InitMat4);
	//_initVAO();
}

myrender::Box::~Box()
{
	delete _quads;
	delete[] _indics;
}

void myrender::Box::InitTexture(char * imagepath)
{
	auto render = myrender::Root::getInstance()->getRender();
	render->SetTexture(imagepath);
}

int myrender::Box::LoadTexture()
{
	_command->LoadTexture();
	return 0;
}

void myrender::Box::InitVertices(float* vertices, unsigned int* indics, int indicssize, int vertocessize)
{
	_triangle_data->quad_size = vertocessize;
	_triangle_data->quad = new V3F_V3F_V2F[vertocessize / sizeof(V3F_V3F_V2F)];
	_triangle_data->indics = new unsigned int[indicssize / sizeof(float)];
	memcpy(_triangle_data->quad, vertices, vertocessize);
	_triangle_data->indics_size = indicssize;
	memcpy(_triangle_data->indics, indics, indicssize);
	_command->SetTriangleData(_triangle_data);
	_command->LoadVertexArry();
}

void myrender::Box::InitVertices(float * vertices, int vertocessize)
{
	_triangle_data_i->quad_size = vertocessize;
	_triangle_data_i->quad = new V3F_V2F[vertocessize / sizeof(V3F_V2F)];
	memcpy(_triangle_data_i->quad, vertices, vertocessize);
	_command->SetTriangleData(_triangle_data_i);
}

void myrender::Box::Draw()
{
	auto render = Render::getInstance();
	_command->SetTriangleData(_triangle_data_i);
	_command->SetShader(_shader);
	_command->SetTransform(_model_mat);
	render->AddRenderCommand(_command);
}

void myrender::Box::Release()
{
}

void myrender::Box::SetWorldPos(const glm::vec3 & p)
{
	_world_pos = p;
}

void myrender::Box::SetShader(int s)
{
	_shader = s;
}

void myrender::Box::MadeModelMat(glm::vec3 Pos, GLfloat angle, glm::vec3 aixs)
{
	_model_mat = glm::translate(_model_mat, Pos);//构造平移矩阵
	_model_mat = glm::rotate(_model_mat, angle, aixs);//构造旋转矩阵
}
