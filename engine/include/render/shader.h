#pragma once
#ifndef SHADER_H
#define SHADER_H
#include"../constant/engine_constant.h"
namespace myrender {
	class Shader
	{
	public:
		// 程序ID
		
		unsigned int GetID()
		{
			return ID;
		}
		// 构造器读取并构建着色器
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
		{
			// 1. retrieve the vertex/fragment source code from filePath
			propertyvector.clear();
			std::string vertexCode;
			std::string fragmentCode;
			std::ifstream vShaderFile;
			std::ifstream fShaderFile;
			// ensure ifstream objects can throw exceptions:
			vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				// open files
				vShaderFile.open(vertexPath);
				fShaderFile.open(fragmentPath);
				std::stringstream vShaderStream, fShaderStream;
				// read file's buffer contents into streams
				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();
				// close file handlers
				vShaderFile.close();
				fShaderFile.close();
				// convert stream into string
				vertexCode = vShaderStream.str();
				fragmentCode = fShaderStream.str();
			}
			catch (std::ifstream::failure e)
			{
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			}
			const char* vShaderCode = vertexCode.c_str();
			const char * fShaderCode = fragmentCode.c_str();
			// 2. compile shaders
			unsigned int vertex, fragment;
			// vertex shader
			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vShaderCode, NULL);
			glCompileShader(vertex);
			checkCompileErrors(vertex, "VERTEX");
			// fragment Shader
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			glCompileShader(fragment);
			checkCompileErrors(fragment, "FRAGMENT");
			// shader Program
			ID = glCreateProgram();
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			glLinkProgram(ID);
			checkCompileErrors(ID, "PROGRAM");
			// delete the shaders as they're linked into our program now and no longer necessary
			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}
		// 使用/激活程序
		void use()
		{
			glUseProgram(ID);
		}
		// uniform工具函数
		void setBool(const STRING &name, bool value) const
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
		}
		// ------------------------------------------------------------------------
		void setInt(const STRING &name, int value) const
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
		}
		// ------------------------------------------------------------------------
		void setFloat(const STRING &name, float value) const
		{
			glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
		}
		void setMat4(const STRING &name, MAT4 &trans) const
		{
			glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()) , 1, GL_FALSE, glm::value_ptr(trans));
		}

		void setVec3(const STRING &name,VEC3 &vec)
		{
			glUniform3f(glGetUniformLocation(ID, name.c_str()),vec.x,vec.y,vec.z);
		}
		void setShaderproperty(const STRING name, float value)
		{
			ShaderProperty temp;
			temp.propertyname = name;
			temp.fvalue = value;
			temp.propertytype = PROPERTYVALUETYPE::FLOAT;
			propertyvector.push_back(temp);
			setFloat(name, value);
		}
		void setShaderproperty(const STRING name, bool value)
		{
			ShaderProperty temp;
			temp.propertyname = name;
			temp.bvalue = value;
			temp.propertytype = PROPERTYVALUETYPE::BOOL;
			propertyvector.push_back(temp);
			setBool(name, value);
		}
		void setShaderproperty(const STRING name, int value)
		{
			ShaderProperty temp;
			temp.propertyname = name;
			temp.ivalue = value;
			temp.propertytype = PROPERTYVALUETYPE::INT;
			propertyvector.push_back(temp);
     		setInt(name, value);
		}
		void setShaderproperty(const STRING &name, MAT4 &trans)
		{
			setMat4(name, trans);
		}
		void setShaderproperty(const STRING &name, VEC3 &vec)
		{
			setVec3(name, vec);
		}
	private:
		unsigned int ID;
		enum PROPERTYVALUETYPE
		{
			BOOL,
			INT,
			FLOAT,
		};
		struct ShaderProperty
		{
			std::string propertyname;
			union 
			{
				float fvalue;
				int   ivalue;
				bool  bvalue;
			};
			PROPERTYVALUETYPE propertytype;

		};
		SHADERPROVECTOR  propertyvector;
		void checkCompileErrors(unsigned int shader, std::string type)
		{
			int success;
			char infoLog[1024];
			if (type != "PROGRAM")
			{
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(shader, 1024, NULL, infoLog);
					std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
				}
			}
			else
			{
				glGetProgramiv(shader, GL_LINK_STATUS, &success);
				if (!success)
				{
					glGetProgramInfoLog(shader, 1024, NULL, infoLog);
					std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
				}
			}
		}
	};
}
#endif