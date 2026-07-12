#pragma once

#include <glm.hpp>
#include <string>

class Shader {
	public:
		unsigned int ID = 0;

		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void use() const;
		void setInt(const std::string& name, int value) const;
		void setMat4(const std::string& name, const glm::mat4& mat) const;
		void setBool(const std::string& name, bool value) const;
		void setVec3(const std::string& name, const glm::vec3& value) const;

	private:
		std::string readFile(const char* path);
		unsigned int compileShader(unsigned int type, const char* source);
};
