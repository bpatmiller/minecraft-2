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
  glfwSetWindowUserPointer(g.window, &g);

  // set input callbacks
  glfwSetCursorPosCallback(g.window, Gui::MousePosCallback);
  glfwSetMouseButtonCallback(g.window, Gui::MouseButtonCallback);
  glfwSetKeyCallback(g.window, Gui::KeyCallback);

  // dirt cube shader/vao
  Shader dirt_cube_shader("src/shaders/cube_vert.glsl",
                          "src/shaders/cube_geom.glsl",
                          "src/shaders/cube_frag.glsl");
  Cube dirt_cube;

  // draw loop
  while (!glfwWindowShouldClose(g.window)) {
    g.clearRender();
    // g.checkGround(dirt_cube.offsets);
    // g.gravity();

    // dirt draw pass
    dirt_cube_shader.use();
    // pass uniforms
    dirt_cube_shader.setMat("projection", g.projection_matrix);
    dirt_cube_shader.setMat("view", g.view_matrix);
    dirt_cube_shader.setMat("model", g.model_matrix);
    dirt_cube_shader.setVec3("light_position", g.light_position);
    // render
    dirt_cube.draw();

    g.swapPoll();
  }
  return 0;
}