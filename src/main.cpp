#include <glad/glad.h>

#include "Gui.h"
#include "RenderObject.h"
#include "Shader.h"
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

  Shader dirt_cube_shader("src/shaders/cube_vert.glsl", "",
                          "src/shaders/cube_frag.glsl");

  while (!glfwWindowShouldClose(g.window)) {

    g.SwapPoll();
  }
  return 0;
}