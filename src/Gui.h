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
  std::string window_title;
  int window_width, window_height;
  GLFWwindow *window;

  // camera uniforms
  glm::mat4 view_matrix;
  glm::mat4 projection_matrix;
  glm::mat4 model_matrix;

  Gui(int w, int h, std::string title) {
    // window settings
    window_width = w;
    window_height = h;
    window_title = title;

    // init camera uniforms
    model_matrix = glm::mat4(1.0f);
    // view_matrix = glm::lookAt(eye, center, up);
    // projection_matrix = glm::perspective(
    //     kFov, (float)window_width / window_height, kNear, kFar);
    projection_matrix = glm::perspective(
        glm::radians(100.f), ((float)window_width) / window_height, 0.1f, 100.f);
    view_matrix = glm::lookAt(glm::vec3(0, 3, -3), glm::vec3(0, 0, 0),
                              glm::vec3(0, 1, 0));

    // std::cout << "mvp: " << glm::to_string(projection_matrix * view_matrix *
    // model_matrix) << std::endl << std::endl;

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

  void swapPoll() {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  void clearRender() {
    glfwGetFramebufferSize(window, &window_width, &window_height);
    glViewport(0, 0, window_width, window_height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_MULTISAMPLE);
    // glEnable(GL_BLEND);
    // // glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glDepthFunc(GL_LESS);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glCullFace(GL_BACK);
    // updateMatrices();
  }

  void updateMatrices() {
    projection_matrix = glm::perspective(
        glm::radians(100.f),
        ((float)window_width)/window_height,
        0.1f,
        100.f
    );
    view_matrix = glm::lookAt(glm::vec3(0,3,-3), glm::vec3(0,0,0), glm::vec3(0,1,0));
  }
};

#endif