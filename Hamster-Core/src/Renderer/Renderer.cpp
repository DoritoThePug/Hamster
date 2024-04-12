#include "Renderer.h"

#include <iostream>


#include <glad/glad.h>
#include <glfw3.h>


namespace Hamster {
	void Renderer::Init(uint16_t windowWidth, uint16_t windowHeight) {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialise glad" << std::endl;
		}
	}

	void Renderer::Terminate() {

	}

	void Renderer::SetViewport(uint16_t width, uint16_t height) {
		glViewport(0, 0, width, height);
	}

	void Renderer::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	void Renderer::SetClearColour(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}
}