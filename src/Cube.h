#include "VAO.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

struct Cube {
  VertexArr VAO;
  float minxz = 5.0;
  float miny = 1.0;

  std::vector<glm::vec3> vertices = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f},
                                     {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f},
                                     {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f},
                                     {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};

  std::vector<glm::uvec3> indices = {
      {0, 1, 2}, {1, 2, 3}, {0, 1, 5}, {0, 4, 1}, {1, 2, 6}, {1, 2, 5},
      {0, 2, 4}, {2, 6, 4}, {3, 0, 4}, {3, 4, 7}, {4, 5, 6}, {5, 7, 6}};

  std::vector<glm::vec3> offsets = {{0.0f, 0.0f, 0.0f}};

  Cube() {
    generateTerrain();
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

  void generateTerrain() {
    offsets.clear();

    int minx = -5;
    int maxx = 5;
    int minz = -5;
    int maxz = 5;

    for (int x = minx; x < maxx; x++) {
      for (int z = minz; z < maxz; z++) {
        int y = (int)(glm::sin((float)x) * glm::sin((float)z) * 1.5);
        offsets.emplace_back(glm::vec3(x, y, z));
      }
    }

    // for (auto v : )
    // std::cout << glm::to_string(offsets) << std::endl;
  }
};