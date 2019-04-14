#include <GL/glew.h>
#include <glm/gtx/io.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "hello" << std::endl;
  glm::vec3 v(1.0);
  std::cout << glm::to_string(v) << std::endl;
}