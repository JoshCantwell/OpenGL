#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode = readFile(vertexPath);
	std::string fragmentCode = readFile(fragmentPath);

	unsigned int vertexShader =
		compileShader(GL_VERTEX_SHADER, vertexCode.c_str());

	unsigned int fragmentShader =
		compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	int success;
	char infoLog[1024];

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 1024, nullptr, infoLog);
		std::cerr << "Shader link error:\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	if (ID != 0)
		glDeleteProgram(ID);
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(
			glGetUniformLocation(ID, name.c_str()),
			value
		   );
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(
			glGetUniformLocation(ID, name.c_str()),
			1,
			GL_FALSE,
			glm::value_ptr(mat)
			);
}

std::string Shader::readFile(const char* path)
{
	std::ifstream file(path);

	if (!file.is_open())
	{
		std::cerr << "Failed to open shader file: " << path << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

unsigned int Shader::compileShader(unsigned int type, const char* source)
{
	unsigned int shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int success;
	char infoLog[1024];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
		std::cerr << "Shader compile error:\n" << infoLog << std::endl;
	}

	return shader;
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(
			glGetUniformLocation(ID, name.c_str()),
			value ? 1 : 0
		   );
}

void Shader::setVec3(
		const std::string& name,
		const glm::vec3& value) const
{
	glUniform3fv(
			glGetUniformLocation(ID, name.c_str()),
			1,
			glm::value_ptr(value)
		    );
}
