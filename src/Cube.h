#include "VAO.h"

struct Cube {
  VertexArr VAO;
  std::vector<glm::vec3> cube_vertices = {
      {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f},
      {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f},
      {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};

  std::vector<glm::uvec3> cube_indices = {
      {0, 1, 2}, {1, 2, 3}, {0, 1, 5}, {0, 1, 4}, {1, 2, 6}, {1, 2, 5},
      {2, 3, 7}, {2, 3, 6}, {3, 0, 4}, {3, 0, 7}, {4, 5, 6}, {5, 6, 7}};

  std::vector<glm::vec3> vertices = {
      {-0.3f, 0.0f, 0.0f}, {0.3f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}};

  std::vector<glm::vec3> offsets = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.5f, 0.0f}};

  Cube() {
    VAO.vb.bindVertices(cube_vertices);
    VAO.ib.bindVertices(offsets);
    VAO.setLayout({3}, false);
    VAO.setLayout({3}, true);
  }

  void draw() {
    VAO.bind();
    // glDrawArraysInstanced(GL_TRIANGLES, 0, vertices.size(), offsets.size());
    glDrawElementsInstanced(GL_TRIANGLES, cube_indices.size() * 3, GL_UNSIGNED_INT, cube_indices.data(), offsets.size());
  }
};