#include <glad/glad.h>

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

  Shader dirt_cube_shader("src/shaders/cube_vert.glsl", "",
                          "src/shaders/cube_frag.glsl");

  std::vector<glm::vec3> tri_vert = {
    {-0.5f, 0.0f, 0.0f},
    {0.5f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f}
  };

  VertexArr tri_vao;
  tri_vao.setLayout({3});
  tri_vao.vb.bindVertices(tri_vert);

  while (!glfwWindowShouldClose(g.window)) {
    g.clearRender();

    dirt_cube_shader.use();
    tri_vao.bind();
    glDrawArrays( GL_TRIANGLES, 0,
                          tri_vert.size() );

    g.swapPoll();
  }
  return 0;
}