#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>

#include "VAO.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <string>

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

class Gui {
public:
  GLFWwindow *window;

  std::string window_title;
  int window_width;
  int window_height;

  int last_x = 0;
  int last_y = 0;
  int current_x = 0;
  int current_y = 0;
  bool mouse_pressed = false;

  // camera properties
  glm::vec3 eye = glm::vec3(0.0f, 2.0f, 2.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 focus = glm::vec3(0.0f, 0.0f, 0.0f);
  // secondary camera properties
  float camera_distance = glm::distance(eye, focus);
  glm::vec3 look = glm::normalize(focus - eye);
  glm::vec3 tangent = glm::cross(look, up);
  glm::mat3 orientation = glm::mat3(tangent, up, look);
  // camera uniforms
  glm::mat4 view_matrix;
  glm::mat4 projection_matrix;
  glm::mat4 model_matrix;

  Gui(int w, int h, std::string title) {
    window_width = w;
    window_height = h;
    window_title = title;
    // init glfw
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
      exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(window_width, window_height, window_title.c_str(),
                              NULL, NULL);
    if (!window) {
      glfwTerminate();
      std::cout << "error" << std::endl;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);
  }

  ~Gui() {
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  void swapPoll();
  void clearRender();
  void updateMatrices();

  void mouseButtonCallback(int button, int action, int mods);
  void mousePosCallback(double mouse_x, double mouse_y);
  void keyCallback(int key, int scancode, int action, int mods);
  static void MouseButtonCallback(GLFWwindow *window, int button, int action,
                                  int mods);
  static void MousePosCallback(GLFWwindow *window, double mouse_x,
                               double mouse_y);
  static void KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
};

#endif