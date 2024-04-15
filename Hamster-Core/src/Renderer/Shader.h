#pragma once

namespace Hamster {
	class Shader
	{
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

		void use();

	private:
		unsigned int m_shaderID;
	};
}