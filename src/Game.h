#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <string>

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

class Game {
public:
  Game() {
    window_width = 640;
    window_height = 480;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
      exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

   window = glfwCreateWindow(window_width, window_height,
                               window_title.c_str(), NULL, NULL);
    if (!window) {
      glfwTerminate();
      err();
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

  }

  ~Game() {
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  static void err();

  void loop();
  void init();

  std::string window_title = "minecraft";
  int window_width, window_height;
  GLFWwindow *window;

};

#endif