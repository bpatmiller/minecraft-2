#include "VAO.h"

struct Cube {
  VertexArr VAO;
  std::vector<glm::vec3> vertices = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f},
                                     {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f},
                                     {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f},
                                     {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};

  std::vector<glm::uvec3> indices = {
      {0, 1, 2}, {1, 2, 3}, {0, 1, 5}, {0, 4, 1}, {1, 2, 6}, {1, 2, 5},
      {0, 2, 4}, {2, 6, 4}, {3, 0, 4}, {3, 4, 7}, {4, 5, 6}, {5, 7, 6}};

  std::vector<glm::vec3> offsets = {{0.0f, 0.0f, 0.0f}, {-1.25f, 0.5f, 0.0f}};

  Cube() {
    VAO.vb.bindVertices(vertices);
    VAO.ib.bindVertices(offsets);
    VAO.setLayout({3}, false);
    VAO.setLayout({3}, true);
  }

  void draw() {
    VAO.bind();
    glDrawElementsInstanced(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT,
                            indices.data(), offsets.size());
  }
};