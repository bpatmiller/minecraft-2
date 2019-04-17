#include "VAO.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

struct Skybox {
  VertexArr VAO;
  glm::mat4 model_matrix = glm::mat4(1.0f);
  float scale = 200.0f;

  std::vector<glm::vec3> vertices = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f},
                                     {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f},
                                     {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f},
                                     {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};

  std::vector<glm::uvec3> indices = {
      {0, 1, 2}, {1, 3, 2}, {4, 6, 5}, {5, 6, 7}, {0, 5, 1}, {0, 4, 5},
      {2, 3, 7}, {2, 7, 6}, {3, 1, 5}, {3, 5, 7}, {0, 2, 6}, {0, 6, 4}};

  Skybox() {
    VAO.vb.bindVertices(vertices);
    VAO.setLayout({3}, false);
    model_matrix = glm::scale(glm::vec3(scale, scale, scale)) *
                   glm::translate(glm::vec3(-0.5f, -0.5f, -0.5f));
  }

  void draw() {
    VAO.bind();
    glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT,
                   indices.data());
  }

  void updateLocation(glm::vec3 &eye) {
    model_matrix = glm::translate(eye) *
                   glm::scale(glm::vec3(scale, scale, scale)) *
                   glm::translate(glm::vec3(-0.5f, -0.5f, -0.5f));
  }
};