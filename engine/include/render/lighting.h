#pragma once
#include"../unit/object.h"
#include"../constant/engine_constant.h"
#include"../root.h"
namespace myrender
{
	class Lighting :public Object
	{
	public:
		Lighting();
		~Lighting();
		Lighting(const VEC3 &color,const VEC3 &pos);
		void SetPos(const VEC3 &pos);
		VEC3 GetPos();
		VEC3 GetViewPos();
		void SetColor(const VEC3 &color);
		void SetViewPos(const VEC3 &pos);
		static void SetVAO();
		static void SetVBO(GLuint VBO);
		void SetIndex(GLuint index);
		static int GetVAO();
		virtual void SetModel(const MAT4 &m);
		virtual void Release();
		virtual void Draw();
	private:
		static GLuint _lightVAO;
		static GLuint _lightVBO;
		VEC3   _lightViewPos;
		VEC3   _lightPos;
		VEC3   _lightColor;
		GLuint _index;
	};
	class DirectionLighting : public Lighting
	{
	public:
		DirectionLighting(const VEC3 &color, const VEC3 &pos);
		void SetAmbient(const VEC3&);
		VEC3 GetAmbient();
		void SetDiffuse(const VEC3&);
		VEC3 GetDiffuse();
		void SetSpecular(const VEC3&);
		VEC3 GetSpecular();
		void SetDirection(const VEC3&);
		VEC3 GetDirection();
		virtual void Draw();
		virtual void SetModel(const MAT4 &m);
	private:
		VEC3 _ambient;
		VEC3 _diffuse;
		VEC3 _specular;
		VEC3 _direction;
	};
	class PointLighting :public Lighting
	{
	public:
		PointLighting();
		~PointLighting();
		PointLighting(const VEC3 &color, const VEC3 &pos);
		void SetAmbient(const VEC3&);
		VEC3 GetAmbient();
		void SetDiffuse(const VEC3&);
		VEC3 GetDiffuse();
		void SetSpecular(const VEC3&);
		VEC3 GetSpecular();
		void SetConstant(const FLOAT&);
		FLOAT GetConstant();
		void SetLinear(const FLOAT&);
		FLOAT GetLinear();
		void SetQuadratic(const FLOAT&);
		FLOAT GetQuadratic();
		virtual void Draw();
		virtual void SetModel(const MAT4 &m);
	private:
		VEC3 _ambient;
		VEC3 _diffuse;
		VEC3 _specular;
		FLOAT _constant;
		FLOAT _linear;
		FLOAT _quadratic;
	};
}