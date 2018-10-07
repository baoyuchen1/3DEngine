#include"../../include/render/lighting.h"
namespace myrender
{
	GLuint Lighting::_lightVAO = 0;
	GLuint Lighting::_lightVBO = 0;
	Lighting::Lighting()
	{

	}
	Lighting::~Lighting()
	{
	}
	Lighting::Lighting(const VEC3 & color, const VEC3 & pos):_lightPos(pos), _lightColor(color)
	{
	}
	void Lighting::SetPos(const VEC3 & pos)
	{
		_lightPos = pos;
	}
	VEC3 Lighting::GetPos()
	{
		return _lightPos;
	}
	VEC3 Lighting::GetViewPos()
	{
		return _lightViewPos;
	}
	void Lighting::SetColor(const VEC3 & color)
	{
		_lightColor = color;
	}
	void Lighting::SetViewPos(const VEC3 & pos)
	{
		_lightViewPos = pos;
	}
	void Lighting::SetVAO()
	{
		glGenVertexArrays(1, &_lightVAO);
		glBindVertexArray(_lightVAO);
		// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
		glBindBuffer(GL_ARRAY_BUFFER, _lightVBO);
		// Set the vertex attributes (only position data for the lamp))
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the normal vectors
		glEnableVertexAttribArray(0);
	}
	void Lighting::SetVBO(GLuint VBO)
	{
		_lightVBO = VBO;
	}
	void Lighting::SetIndex(GLuint index)
	{
		_index = index;
	}
	int Lighting::GetVAO()
	{
		return _lightVAO;
	}
	void Lighting::SetModel(const MAT4 & m)
	{
		auto render = Root::getInstance()->getRender();
		int shader = render->GetShaderByName("lighting");
		render->setShaderproperty(shader, "model", m);
	}
	void Lighting::Release()
	{
	}
	void Lighting::Draw()
	{
		auto render = Root::getInstance()->getRender();
		int shader = render->GetShaderByName("lighting");
		render->UseShader("lighting");
		render->setShaderproperty(shader, "lightColor", _lightColor);
		render->setShaderproperty(shader, "lightPos", _lightPos);
		render->setShaderproperty(shader, "viewPos", _lightViewPos);
	}
	PointLighting::PointLighting()
	{
	}
	PointLighting::~PointLighting()
	{
	}
	PointLighting::PointLighting(const VEC3 & color, const VEC3 & pos)
	{
		SetPos(pos);
		SetColor(color);
	}
	void PointLighting::SetAmbient(const VEC3 &a)
	{
		_ambient = a;
	}
	VEC3 PointLighting::GetAmbient()
	{
		return _ambient;
	}
	void PointLighting::SetDiffuse(const VEC3 &d)
	{
		_diffuse = d;
	}
	VEC3 PointLighting::GetDiffuse()
	{
		return _diffuse;
	}
	void PointLighting::SetSpecular(const VEC3 &s)
	{
		_specular = s;
	}
	VEC3 PointLighting::GetSpecular()
	{
		return _specular;
	}
	void PointLighting::SetConstant(const FLOAT &c)
	{
		_constant = c;
	}
	FLOAT PointLighting::GetConstant()
	{
		return _constant;
	}
	void PointLighting::SetLinear(const FLOAT &l)
	{
		_linear = l;
	}
	FLOAT PointLighting::GetLinear()
	{
		return _linear;
	}
	void PointLighting::SetQuadratic(const FLOAT &q)
	{
		_quadratic = q;
	}
	FLOAT PointLighting::GetQuadratic()
	{
		return _quadratic;
	}
	void PointLighting::Draw()
	{
		auto render = Root::getInstance()->getRender();
		int shader = render->GetShaderByName("pointlighting");
		render->UseShader("pointlighting");
		render->setShaderproperty(shader, "light.ambient", _ambient);
		render->setShaderproperty(shader, "light.diffuse", _diffuse);
		render->setShaderproperty(shader, "light.specular", _specular);
		render->setShaderproperty(shader, "light.constant", _constant);
		render->setShaderproperty(shader, "light.linear", _linear);
		render->setShaderproperty(shader, "light.quadratic", _quadratic);
		render->setShaderproperty(shader, "light.position", GetPos());
		render->setShaderproperty(shader, "viewPos", GetViewPos());
		render->setShaderproperty(shader, "view", render->GetViewMat());
		render->setShaderproperty(shader, "projection", render->GetProjectionMat());
	}
	void PointLighting::SetModel(const MAT4 & m)
	{
		auto render = Root::getInstance()->getRender();
		int shader = render->GetShaderByName("pointlighting");
		render->setShaderproperty(shader, "model", m);
	}
	DirectionLighting::DirectionLighting(const VEC3 & color, const VEC3 & pos)
	{
		SetPos(pos);
		SetColor(color);
	}
	void DirectionLighting::SetAmbient(const VEC3 &a)
	{
		_ambient = a;
	}
	VEC3 DirectionLighting::GetAmbient()
	{
		return _ambient;
	}
	void DirectionLighting::SetDiffuse(const VEC3 &d)
	{
		_diffuse = d;
	}
	VEC3 DirectionLighting::GetDiffuse()
	{
		return _diffuse;
	}
	void DirectionLighting::SetSpecular(const VEC3 &s)
	{
		_specular = s;
	}
	VEC3 DirectionLighting::GetSpecular()
	{
		return _specular;
	}
	void DirectionLighting::SetDirection(const VEC3 &d)
	{
		_direction = d;
	}
	VEC3 DirectionLighting::GetDirection()
	{
		return _direction;
	}
	void DirectionLighting::Draw()
	{
		auto render = Root::getInstance()->getRender();
		int shader = render->GetShaderByName("directionlighting");
		render->UseShader("directionlighting");
		render->setShaderproperty(shader, "light.ambient", _ambient);
		render->setShaderproperty(shader, "light.diffuse", _diffuse);
		render->setShaderproperty(shader, "light.specular", _specular);
		render->setShaderproperty(shader, "light.direction", _direction);
		render->setShaderproperty(shader, "light.position", GetPos());
		render->setShaderproperty(shader, "viewPos", GetViewPos());
		render->setShaderproperty(shader, "view", render->GetViewMat());
		render->setShaderproperty(shader, "projection", render->GetProjectionMat());
	}
	void DirectionLighting::SetModel(const MAT4 & m)
	{
		auto render = Root::getInstance()->getRender();
		int shader = render->GetShaderByName("directionlighting");
		render->setShaderproperty(shader, "model", m);
	}
}