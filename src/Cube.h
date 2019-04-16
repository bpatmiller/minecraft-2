#include "VAO.h"

struct Cube {
  VertexArr VAO;
  std::vector<glm::vec3> cube_vertices = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 0.0f},
    {1.0f, 1.0f, 1.0f}
  };

  std::vector<glm::uvec3> cube_indices = {
      {},
      {},
      {},
      {},
      {},
      {}
  };

  std::vector<glm::vec3> vertices = {
      {-0.3f, 0.0f, 0.0f}, {0.3f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}};

  std::vector<glm::vec3> offsets = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.5f, 0.0f}};

  Cube() {
    VAO.vb.bindVertices(vertices);
    VAO.ib.bindVertices(offsets);
    VAO.setLayout({3}, false);
    VAO.setLayout({3}, true);
  }

  void draw() {
    VAO.bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, vertices.size(), offsets.size());
  }
};