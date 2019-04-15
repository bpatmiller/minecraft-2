#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <string>

class Game {
public:
  Game() {
    std::cout << "lol222";
  }

  static void err();

  void loop();
  void init();





  std::string window_title;
  int window_width, window_height;


private:

};

#endif