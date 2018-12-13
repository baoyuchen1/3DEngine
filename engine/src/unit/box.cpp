#include"../../include/unit/box.h"
#define STB_IMAGE_IMPLEMENTATION
using namespace myrender;
Box::Box()
{
	_triangle_data = new Triangle_Data();
	_triangle_data_i = new Triangle_Data_WithOut_Indics();
	_command = new RenderTriangle();
	_command->SetCommandType(Triangle_command_type::BOX);
	_command->SetDepthType(GL_LEQUAL);
	_model_mat = glm::make_mat4x4(InitMat4);
	_texture_vector = new std::map<int, bool>;
	//_initVAO();
}

myrender::Box::~Box()
{
	delete _quads;
	delete[] _indics;
}

void myrender::Box::InitTexture(char * imagepath)
{
	auto render = myrender::Root::getInstance()->getTextureManager();
	int textureid = render->SetTexture(imagepath);
	(*_texture_vector)[textureid] = true;
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
	_command->SetTransform(_model_mat);
	_command->SetMaterial(_material);
	
	render->AddRenderCommand(_command);
}

void myrender::Box::Release()
{
}


void myrender::Box::InitMaterial(Texture * diffuse, Texture * specular, float shininess)
{
	_material.diffuse = diffuse->GetTextureIndex();
	_material.specular = diffuse->GetTextureIndex();
	_material.shininess = shininess;
}

void myrender::Box::InitMaterial(int diffuse, int specular, float shininess)
{
	_material.diffuse = diffuse;
	_material.specular = specular;
	_material.shininess = shininess;
	_command->SetTexture(_material.diffuse);
	_command->SetTexture(_material.specular);
}
