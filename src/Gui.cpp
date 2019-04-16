#include "Gui.h"

#include "glm/gtx/rotate_vector.hpp"
#include <glm/glm.hpp>

void Gui::clearRender() {
  glfwGetFramebufferSize(window, &window_width, &window_height);
  glViewport(0, 0, window_width, window_height);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  updateMatrices();
}

void Gui::updateMatrices() {
  projection_matrix = glm::perspective(
      glm::radians(100.f), ((float)window_width) / window_height, 0.1f, 100.f);
  view_matrix = glm::lookAt(eye, focus, up);
  model_matrix = glm::mat4(1.0f);
}

void Gui::swapPoll() {
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void Gui::mouseButtonCallback(int button, int action, int mods) {
  if (current_x <= window_width)
    mouse_pressed = (action == GLFW_PRESS);
}

void Gui::mousePosCallback(double mouse_x, double mouse_y) {
  float dx = mouse_x - current_x;
  float dy = mouse_y - current_y;
  current_x = mouse_x;
  current_y = mouse_y;
  if (mouse_pressed) {
    float rotation_speed = 0.01f;

    look = glm::rotate(look, dx * rotation_speed, up);
    tangent = glm::normalize(glm::cross(look, up));
    look = glm::rotate(look, dy * rotation_speed, tangent);
    up = glm::normalize(glm::cross(look, -tangent));

    look = glm::normalize(look);
    focus = look * glm::length(focus - eye) + eye;
  }
}

void Gui::keyCallback(int key, int scancode, int action, int mods) {
  float move_speed = 0.1f;
  if (key == GLFW_KEY_W) {
    eye = eye + look * move_speed;
    focus = focus + look * move_speed;
  } else if (key == GLFW_KEY_S) {
    eye = eye - look * move_speed;
    focus = focus - look * move_speed;
  } else if (key == GLFW_KEY_A) {
    eye = eye - tangent * move_speed;
    focus = focus - tangent * move_speed;
  } else if (key == GLFW_KEY_D) {
    eye = eye + tangent * move_speed;
    focus = focus + tangent * move_speed;
  }
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

void Gui::KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                      int mods) {
  Gui *gui = (Gui *)glfwGetWindowUserPointer(window);
  gui->keyCallback(key, scancode, action, mods);
}