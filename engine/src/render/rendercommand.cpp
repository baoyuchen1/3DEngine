#include"../../include/render/rendercommand.h"
using namespace myrender;
RenderCommand::RenderCommand()
{

}
RenderCommand::~RenderCommand()
{

}

void myrender::RenderCommand::Draw()
{
}

void myrender::RenderCommand::LoadTexture()
{
}

void myrender::RenderCommand::Release()
{
}

void myrender::RenderCommand::LoadVertexArry()
{
}

void myrender::RenderCommand::Init()
{
}

void myrender::RenderCommand::SetShader(const int & shader)
{
	_shader = shader;
}

int myrender::RenderCommand::GetShader()
{
	return _shader;
}

int myrender::RenderCommand::GetDepthType()
{
	return _depthtype;
}

void myrender::RenderCommand::SetDepthType(const int & depth)
{
	_depthtype = depth;
}

