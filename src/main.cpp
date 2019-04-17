#include <glad/glad.h>

#include "Cube.h"
#include "Gui.h"
#include "Shader.h"
#include "Skybox.h"
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
  // glfwSetInputMode(g.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // dirt cube shader/vao
  Shader dirt_cube_shader("src/shaders/cube_vert.glsl",
                          "src/shaders/cube_geom.glsl",
                          "src/shaders/cube_frag.glsl");
  Cube dirt_cube;

  // skubox shader/vao
  Shader skybox_shader("src/shaders/skybox_vert.glsl", "",
                       "src/shaders/skybox_frag.glsl");
  Skybox skybox;

  // draw loop
  while (!glfwWindowShouldClose(g.window)) {
    g.clearRender();
    g.checkGround(dirt_cube.offsets);
    g.gravity();
    g.applyKeyboardInput();

    // cube pass
    dirt_cube_shader.use();
    // pass uniforms
    dirt_cube_shader.setMat("projection", g.projection_matrix);
    dirt_cube_shader.setMat("view", g.view_matrix);
    dirt_cube_shader.setMat("model", g.model_matrix);
    dirt_cube_shader.setVec3("light_position", g.light_position);
    // render
    dirt_cube.draw();

    // skybox pass
    skybox_shader.use();
    // pass uniforms
    skybox_shader.setMat("projection", g.projection_matrix);
    skybox_shader.setMat("view", g.view_matrix);
    skybox_shader.setMat("model", skybox.model_matrix);
    // render
    skybox.draw();

    g.swapPoll();
  }
  return 0;
}