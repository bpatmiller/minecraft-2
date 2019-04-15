#include "Game.h"

void Game::err() {
  std::cout << "GLFW not initialized" << std::endl;
  exit(1);
}

void Game::init() {
  if (!glfwInit()) {
    err();
  }
}

void Game::loop() {}