#include <glad/glad.h>

#include "Cube.h"
#include "Gui.h"
#include "Shader.h"
#include "VAO.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <string>

int window_width = 640;
int window_height = 480;
std::string window_title = "minecraft";

int main(int argc, char *argv[]) {
  // create window/init glfw
  Gui g(window_width, window_height, window_title);

  // dirt cube shader/vao
  Shader dirt_cube_shader("src/shaders/cube_vert.glsl", "",
                          "src/shaders/cube_frag.glsl");
  Cube dirt_cube;

  // draw loop
  while (!glfwWindowShouldClose(g.window)) {
    g.clearRender();

    // dirt draw pass
    dirt_cube_shader.use();
    dirt_cube.draw();

    g.swapPoll();
  }
  return 0;
}