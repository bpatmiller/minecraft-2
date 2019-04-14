#include <GL/glew.h>

#include "Gui.h"
#include "Shader.h"
#include <glm/gtx/io.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

int window_width = 1280;
int window_height = 720;

const char *cube_vertex_shader =
#include "shaders/cube.vert"
    ;

const char *cube_fragment_shader =
#include "shaders/cube.frag"
    ;

int main(int argc, char *argv[]) {
  std::cout << "hello" << std::endl;
  glm::vec3 v(1.0);
  std::cout << glm::to_string(v) << std::endl;
}