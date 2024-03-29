#include "Config.h"
#include "VAO.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/common.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

std::vector<int> permutation = {
    151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233, 7,
    225, 140, 36,  103, 30,  69,  142, 8,   99,  37,  240, 21,  10,  23,  190,
    6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203, 117,
    35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125, 136,
    171, 168, 68,  175, 74,  165, 71,  134, 139, 48,  27,  166, 77,  146, 158,
    231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,  41,  55,  46,
    245, 40,  244, 102, 143, 54,  65,  25,  63,  161, 1,   216, 80,  73,  209,
    76,  132, 187, 208, 89,  18,  169, 200, 196, 135, 130, 116, 188, 159, 86,
    164, 100, 109, 198, 173, 186, 3,   64,  52,  217, 226, 250, 124, 123, 5,
    202, 38,  147, 118, 126, 255, 82,  85,  212, 207, 206, 59,  227, 47,  16,
    58,  17,  182, 189, 28,  42,  223, 183, 170, 213, 119, 248, 152, 2,   44,
    154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,   129, 22,  39,  253,
    19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246, 97,
    228, 251, 34,  242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,  51,
    145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157, 184,
    84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205, 93,
    222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,  156,
    180};

struct Cube {
  VertexArr VAO;

  std::vector<glm::vec3> vertices = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f},
                                     {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f},
                                     {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f},
                                     {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};

  std::vector<glm::uvec3> indices = {
      {0, 2, 1}, {1, 2, 3}, {4, 5, 6}, {5, 7, 6}, {0, 1, 5}, {0, 5, 4},
      {2, 7, 3}, {2, 6, 7}, {3, 5, 1}, {3, 7, 5}, {0, 6, 2}, {0, 4, 6}};

  std::vector<glm::vec4> offsets = {{0.0f, 0.0f, 0.0f, 0.0f}};

  std::vector<glm::ivec2> chunks = {{0, 0}};

  Cube() {
    offsets.clear();
    for (auto c : chunks) {
      generateTerrain(c);
    }
    VAO.vb.bindVertices(vertices);
    VAO.ib.bindVertices(offsets);
    VAO.setLayout({3}, false);
    VAO.setLayout({4}, true);
  }

  bool checkChunks(glm::vec3 &eye) {

    float xsign = 1;
    float zsign = 1;
    if (eye.x < 0)
      xsign = -1;
    if (eye.z < 0)
      zsign = -1;

    int x = (int)(eye.x / (2 * BlockSize) + (xsign * 0.5));
    int y = (int)(eye.z / (2 * BlockSize) + (zsign * 0.5));

    std::vector<glm::ivec2> closest_chunks;
    std::vector<glm::ivec2> addChunks;

    for (int i = -2; i <= 2; i++) {
      for (int j = -2; j <= 2; j++) {
        closest_chunks.emplace_back(glm::ivec2(x + i, y + j));
      }
    }

    // for each candidate chunk
    for (auto cc : closest_chunks) {
      bool found = false;
      // check existing chunks
      for (auto c : chunks) {
        if (c.x == cc.x && c.y == cc.y) {
          found = true;
        }
      }
      if (!found)
        addChunks.emplace_back(cc);
    }
    updateChunk(addChunks);
    return (addChunks.size() != 0);
  }

  void updateChunk(std::vector<glm::ivec2> new_chunks) {
    for (auto c : new_chunks) {
      // std::cout << "chunk added" << std::endl;
      chunks.emplace_back(c);
      generateTerrain(c);
    }

    if (chunks.size() > 60) {
      // std::cout << "erasing chunks" << std::endl;
      offsets.clear();
      for (int i = 0; i < 8; i++) {
        chunks.erase(chunks.begin());
      }
      for (auto c : chunks) {
        generateTerrain(c);
      }
    }

    VAO.ib.bindVertices(offsets);
  }

  void draw() {
    VAO.bind();
    glDrawElementsInstanced(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT,
                            indices.data(), offsets.size());
  }

  void generateTerrain(glm::ivec2 chunk) {

    int minx = -BlockSize + BlockSize * 2 * chunk.x;
    int maxx = BlockSize + BlockSize * 2 * chunk.x;
    int minz = -BlockSize + BlockSize * 2 * chunk.y;
    int maxz = BlockSize + BlockSize * 2 * chunk.y;

    // generate dirt
    for (int x = minx; x < maxx; x++) {
      for (int z = minz; z < maxz; z++) {
        float pn = perlin2d(x, z);
        if (pn < RockLevel) {
          // rock
          offsets.emplace_back(glm::vec4(x, (int)pn, z, 3.0f));
        } else {
          bool tree = ((rand() % 100) == 1);
          // add cactus
          if (tree && pn >= WaterLevel) {
            offsets.emplace_back(glm::vec4(x, (int)pn, z, 0.0f));
            int h = (rand() % 6) + 4;
            for (int b = 0; b < h; b++) {
              offsets.emplace_back(glm::vec4(x, (int)pn + b, z, 2.0f));
            }
          } else {
            // dirt
            offsets.emplace_back(glm::vec4(x, (int)pn, z, 0.0f));
          }
        }
      }
    }
  }

  float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }
  float lerp(float t, float a, float b) { return a + t * (b - a); }
  float grad(int hash, float x, float y, float z) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
  }

  int perm(int i) {
    if (i >= (int)permutation.size()) {
      i = i % permutation.size();
    }
    return permutation[i];
  }

  float perlin3d(float x, float y, float z) {
    int X = (int)glm::floor(x) & 255;
    int Y = (int)glm::floor(y) & 255;
    int Z = (int)glm::floor(z) & 255;

    x -= glm::floor(x);
    y -= glm::floor(y);
    z -= glm::floor(z);

    float u = fade(x);
    float v = fade(y);
    float w = fade(z);

    int A = perm(X) + Y;
    int AA = perm(A) + Z;
    int AB = perm(A + 1) + Z;
    int B = perm(X + 1) + Y;
    int BA = perm(B) + Z;
    int BB = perm(B + 1) + Z;

    return lerp(
        w,
        lerp(v, lerp(u, grad(perm(AA), x, y, z), grad(perm(BA), x - 1, y, z)),
             lerp(u, grad(perm(AB), x, y - 1, z),
                  grad(perm(BB), x - 1, y - 1, z))),
        lerp(v,
             lerp(u, grad(perm(AA + 1), x, y, z - 1),
                  grad(perm(BA + 1), x - 1, y, z - 1)),
             lerp(u, grad(perm(AB + 1), x, y - 1, x - 1),
                  grad(perm(BB + 1), x - 1, y - 1, z - 1))));
  }

  float perlin2d(float x, float z) {
    x /= 25.0f;
    z /= 25.0f;
    float r = perlin3d(x, 1.0f, z);
    r *= 20.0f;
    return r;
  }
};