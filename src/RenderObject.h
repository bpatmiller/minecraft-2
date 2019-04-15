#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include <glm/gtx/io.hpp>
#include <vector>

class MeshObject {
public:
  std::vector<glm::vec4> vertices;
  std::vector<glm::uvec3> indices;
};

class RenderObject {
public:
  MeshObject *mesh;
};

#endif