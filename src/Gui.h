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
#include <map>
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
  glm::vec3 screenRes;

  std::map<int, bool> keyHeld;

  int current_x = -1;
  int current_y = -1;
  bool mouse_pressed = false;
  bool on_ground = false;
  bool flying = false;
  bool colw = false;
  bool cols = false;
  bool cola = false;
  bool cold = false;
  int loopy = 0;
  glm::vec3 momentum = glm::vec3(0);
  glm::vec3 light_position = glm::vec3(-3.0f, 10.0f, 5.0f);

  // camera properties
  glm::vec3 eye = glm::vec3(0, 5, 5);
  glm::quat orientation = glm::quat(glm::mat4(1.0f));
  glm::vec3 fdir = glm::vec3(0, 0, -1);
  glm::vec3 sdir = glm::vec3(1, 0, 0);
  glm::vec3 gfdir = fdir;
  glm::vec3 gsdir = sdir;
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(window_width, window_height, window_title.c_str(),
                              NULL, NULL);
    if (!window) {
      glfwTerminate();
      std::cout << "error" << std::endl;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);
    // set input callbacks
    glfwSetCursorPosCallback(window, MousePosCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    updateMatrices();
  }

  ~Gui() {
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  bool groundBlock(glm::vec4 &block);
  bool collideBlock(glm::vec4 &block, glm::vec3 &offset, float move_speed);

  void swapPoll();
  void clearRender();
  void updateMatrices();
  void checkGround(std::vector<glm::vec4> &offsets);
  void gravity();
  void applyKeyboardInput();

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