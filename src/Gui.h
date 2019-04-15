#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>

#include "RenderObject.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
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

  Gui(int w, int h, std::string title) {
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

  void SwapPoll() {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
};

#endif