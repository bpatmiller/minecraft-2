#include <glad/glad.h>

#include "Cube.h"
#include "Gui.h"
#include "RenderTexture.h"
#include "Shader.h"
#include "Skybox.h"
#include "TexturedQuad.h"
#include "VAO.h"
#include "Water.h"
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

  // dirt cube shader/vao
  Shader dirt_cube_shader("src/shaders/cube_vert.glsl",
                          "src/shaders/cube_geom.glsl",
                          "src/shaders/cube_frag.glsl");
  Cube dirt_cube;

  // skubox shader/vao
  Shader skybox_shader("src/shaders/skybox_vert.glsl", "",
                       "src/shaders/skybox_frag.glsl");
  Skybox skybox;

  // water vao
  Shader water_shader("src/shaders/water_vert.glsl", "",
                      "src/shaders/water_frag.glsl");
  Water water(dirt_cube.offsets);
  // water texture
  RenderTexture waterTex;
  waterTex.create(g.window_width, g.window_height);

  // textured quad for first render pass
  Shader texquad_shader("src/shaders/texq_vert.glsl", "",
                        "src/shaders/texq_frag.glsl");
  TexturedQuad texQuad;

  // draw loop
  while (!glfwWindowShouldClose(g.window)) {
    g.checkGround(dirt_cube.offsets);
    g.gravity();
    g.applyKeyboardInput();
    bool updateWorld = dirt_cube.checkChunks(g.eye);
    if (updateWorld)
      water.generateWater(dirt_cube.offsets);
    g.updateMatrices();
    g.clearRender();

    waterTex.changeSize(g.window_width, g.window_height);
    waterTex.bind();

    g.clearRender();
    // cube pass ------------------------- //
    dirt_cube_shader.use();
    // pass uniforms
    dirt_cube_shader.setMat("projection", g.projection_matrix);
    dirt_cube_shader.setMat("view", g.view_matrix);
    dirt_cube_shader.setMat("model", g.model_matrix);
    dirt_cube_shader.setVec3("light_position", g.light_position);
    // render
    dirt_cube.draw();

    // skybox pass ------------------------- //
    skybox_shader.use();
    skybox.updateLocation(g.eye);
    // pass uniforms
    skybox_shader.setMat("projection", g.projection_matrix);
    skybox_shader.setMat("view", g.view_matrix);
    skybox_shader.setMat("model", skybox.model_matrix);
    // render
    skybox.draw();
    waterTex.unbind();

    waterTex.bindTexture();

    // draw scene quad ------------------------- //
    texquad_shader.use();
    // sampler uniforms
    texquad_shader.setInt("screenTex", 0);
    texquad_shader.setInt("depTex", 1);
    texquad_shader.setInt("loopy", g.loopy);
    texQuad.draw();

    // water pass ------------------------- //
    water_shader.use();
    // uniforms
    water_shader.setMat("projection", g.projection_matrix);
    water_shader.setMat("view", g.view_matrix);
    water_shader.setMat("model", g.model_matrix);
    water_shader.setVec3("screenRes", g.screenRes);
    // sampler uniforms
    water_shader.setInt("screenTex", 0);
    water_shader.setInt("depTex", 1);
    // render
    water.draw();

    waterTex.unbindTexture();

    g.swapPoll();
  }
  return 0;
}