#include "Gui.h"

void Gui::mouseButtonCallback(int button, int action, int mods) {
  std::cout << "click!" << std::endl;
}

void Gui::mousePosCallback(int mouse_x, int mouse_y) {
    std::cout << mouse_x << std::endl;
}

void Gui::MouseButtonCallback(GLFWwindow *window, int button, int action,
                              int mods) {
  Gui *gui = (Gui *)glfwGetWindowUserPointer(window);
  gui->mouseButtonCallback(button, action, mods);
}

void Gui::MousePosCallback(GLFWwindow *window, double mouse_x, double mouse_y) {
  Gui *gui = (Gui *)glfwGetWindowUserPointer(window);
  gui->mousePosCallback(mouse_x, mouse_y);
}