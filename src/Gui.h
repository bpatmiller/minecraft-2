#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>

#include "VAO.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

class Gui {
public:
  std::string window_title;
  int window_width, window_height;
  GLFWwindow *window;

  float kFov = 45.0f;
  float kNear = 0.1;
  float kFar = 1000.0f;
  float aspect;

  float camera_distance = 5.0f;
  glm::vec3 eye = glm::vec3(0.0f, 0.1f, camera_distance);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 look = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 tangent = glm::cross(look, up);
  glm::vec3 center = eye - camera_distance * look;
  glm::mat3 orientation = glm::mat3(tangent, up, look);
  glm::vec4 light_position;

  glm::mat4 view_matrix = glm::lookAt(eye, center, up);
  glm::mat4 projection_matrix =
      glm::perspective((float)(kFov * (M_PI / 180.0f)), aspect, kNear, kFar);

  glm::mat4 model_matrix = glm::mat4(1.0f);

  Gui(int w, int h, std::string title) {
    aspect = static_cast<float>(w) / h;
    window_width = w;
    window_height = h;
    window_title = title;

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

  void swapPoll() {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  void clearRender() {
    glfwGetFramebufferSize(window, &window_width, &window_height);
    glViewport(0, 0, window_width, window_height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    // glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glCullFace(GL_BACK);
  }
};

#endif