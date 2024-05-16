#pragma once

#include <string>

#include <glm.hpp>


namespace Hamster {
	class Shader
	{
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

		void use();

		void setUniformi(const char* name, int value);
		void setUniformMat4(const char* name, const glm::mat4& value);
		void setUniformVec3(const char* name, const glm::vec3& value);

	private:
		unsigned int m_shaderID;
	};
}