#include "Config.h"
#include "VAO.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

struct Water {
  VertexArr VAO;

  std::vector<glm::vec3> vertices = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f},
                                     {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f},
                                     {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f},
                                     {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};

  std::vector<glm::uvec3> indices = {
      {0, 2, 1}, {1, 2, 3}, {4, 5, 6}, {5, 7, 6}, {0, 1, 5}, {0, 5, 4},
      {2, 7, 3}, {2, 6, 7}, {3, 5, 1}, {3, 7, 5}, {0, 6, 2}, {0, 4, 6}};

  std::vector<glm::vec3> offsets = {{0.0f, 0.0f, 0.0f}};

  Water(std::vector<glm::vec4> &block_offsets) { generateWater(block_offsets); }

  void draw() {
    VAO.bind();
    glDrawElementsInstanced(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT,
                            indices.data(), offsets.size());
  }

  void generateWater(std::vector<glm::vec4> &block_offsets) {
    offsets.clear();
    for (auto block : block_offsets) {
      if (block.y < WaterLevel) {
        int y = block.y + 1;
        while (y < WaterLevel) {
          offsets.emplace_back(glm::vec3(block.x, y, block.z));
          y++;
        }
      }
    }
    VAO.vb.bindVertices(vertices);
    VAO.ib.bindVertices(offsets);
    VAO.setLayout({3}, false);
    VAO.setLayout({3}, true);
  }
};