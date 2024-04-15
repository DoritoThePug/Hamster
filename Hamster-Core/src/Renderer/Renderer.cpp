#include "Renderer.h"

#include <iostream>


#include <glad/glad.h>
#include <glfw3.h>

#include "Shader.h"


namespace Hamster {
	void Renderer::Init(uint16_t windowWidth, uint16_t windowHeight) {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialise glad" << std::endl;
		}

		Renderer::SetViewport(windowWidth, windowHeight);

		glEnable(GL_DEPTH_TEST);

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

	// shapes

	void Renderer::DrawTriangle() {


		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

	void Renderer::InitTriangle() {
		Shader shader("C:/Users/Jaden/OneDrive - Tonbridge School/Documents/Hamster/Hamster-Core/src/Renderer/DefaultShaders/flatColour.vs", "C:/Users/Jaden/OneDrive - Tonbridge School/Documents/Hamster/Hamster-Core/src/Renderer/DefaultShaders/flatColour.fs");

		shader.use();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		unsigned int VAO, VBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
}