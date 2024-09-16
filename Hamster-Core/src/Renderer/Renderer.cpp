#include "HamsterPCH.h"

#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Utils/AssetManager.h"

namespace Hamster {
void Renderer::Init(int viewportHeight, int viewportWidth) {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialise glad" << std::endl;
  }

  Renderer::SetViewport(1920, 1080);

  // glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Renderer::InitRendererData();
}

void Renderer::Terminate() {}

void Renderer::SetViewport(uint16_t width, uint16_t height) {
  glViewport(0, 0, width, height);

  // std::cout << width << ", " << height << std::endl;
}

void Renderer::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Renderer::SetClearColour(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
}

void Renderer::InitRendererData() {
  std::string hamsterCorePath = HAMSTER_CORE_SRC_DIR;

  m_SpriteShader = AssetManager::AddShader(
      "sprite", hamsterCorePath + "/Renderer/DefaultShaders/SpriteShader.vs",
      hamsterCorePath + "/Renderer/DefaultShaders/SpriteShader.fs");

  m_FlatShader = AssetManager::AddShader(
      "flat", hamsterCorePath + "/Renderer/DefaultShaders/FlatShader.vs",
      hamsterCorePath + "/Renderer/DefaultShaders/FlatShader.fs");

  // AssetManager::AddShader("sprite", shader);

  float vertices[] = {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

                      0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                      0.0f, 0.0f, 0.0f, 0.0f, 0.0f

  };

  unsigned int VBO;

  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(m_VAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);

  // Unbind the VAO and VBO
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::DrawSprite(Texture &texture, glm::vec2 position, glm::vec2 size,
                          float rotation, glm::vec3 colour) {
  m_SpriteShader->use();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));
  //
  // // Code from learnopengl.com, used to translate sprite so rotation is based
  // // around centre of sprite
  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model =
      glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
  model =
      glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

  model = glm::scale(model, glm::vec3(size, 1.0f));

  m_SpriteShader->setUniformMat4("model", model);
  m_SpriteShader->setUniformVec3("spriteColour", colour);

  glActiveTexture(GL_TEXTURE0);
  texture.BindTexture();

  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindVertexArray(0);

  // DrawGuizmo(position, Translate);
}

void Renderer::DrawFlat(glm::vec2 position, glm::vec2 size, float rotation,
                        glm::vec3 colour) {
  m_FlatShader->use();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));
  //
  // // Code from learnopengl.com, used to translate sprite so rotation is based
  // // around centre of sprite
  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model =
      glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
  model =
      glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

  model = glm::scale(model, glm::vec3(size, 1.0f));

  m_FlatShader->setUniformMat4("model", model);
  m_FlatShader->setUniformVec3("colour", colour);

  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindVertexArray(0);
}

void Renderer::DrawGuizmo(Transform targetTransform, TransformType type,
                          bool selectionColour) {
  m_FlatShader->use();

  glDisable(GL_DEPTH_TEST);

  glm::mat4 model = glm::mat4(1.0f);
  model =
      glm::translate(model, glm::vec3(targetTransform.position.x +
                                          0.5 * targetTransform.size.x - 5.0f,
                                      targetTransform.position.y +
                                          0.5 * targetTransform.size.y - 110.0f,
                                      0.0f));
  model = glm::scale(model, glm::vec3(10.0f, 100.0f, 1.0f));
  // model = glm::scale(model, glm::vec3(1000.0f));

  m_FlatShader->setUniformMat4("model", model);

  if (selectionColour) {
    m_FlatShader->setUniformVec3("colour", Application::IdToColour(YGuizmoID));
  } else {
    m_FlatShader->setUniformVec3(
        "colour", glm::vec3(230.0f / 255.0f, 57.0f / 255.0f, 70.0f / 255.0f));
  }

  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindVertexArray(0);

  model = glm::mat4(1.0f);
  model =
      glm::translate(model, glm::vec3(targetTransform.position.x +
                                          0.5 * targetTransform.size.x + 5.0f,
                                      targetTransform.position.y +
                                          0.5 * targetTransform.size.y - 10.0f,
                                      0.0f));
  model = glm::scale(model, glm::vec3(100.0f, 10.0f, 1.0f));

  m_FlatShader->setUniformMat4("model", model);

  if (selectionColour) {
    m_FlatShader->setUniformVec3("colour", Application::IdToColour(XGuizmoID));
  } else {
    m_FlatShader->setUniformVec3(
        "colour", glm::vec3(81.0f / 255.0f, 152.0f / 255.0f, 114.0f / 255.0f));
  }

  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindVertexArray(0);

  // glEnable(GL_DEPTH_TEST);
}
} // namespace Hamster
