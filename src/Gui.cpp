#include "Gui.h"
#include <glm/gtx/transform.hpp>

void Gui::clearRender() {
  glfwGetFramebufferSize(window, &window_width, &window_height);
  glViewport(0, 0, window_width, window_height);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
  return;
  if (current_x <= window_width)
    mouse_pressed = (action == GLFW_PRESS);
}

void Gui::mousePosCallback(double mouse_x, double mouse_y) {
  return;
  last_x = current_x;
  last_y = current_y;
  current_x = mouse_x;
  current_y = window_height - mouse_y;
  float delta_x = current_x - last_x;
  float delta_y = current_y - last_y;

  if (sqrt(delta_x * delta_x + delta_y * delta_y) < 1e-15)
    return;
  if (mouse_x > window_width)
    return;

  // glm::vec3 mouse_direction = glm::normalize(glm::vec3(delta_x, delta_y,
  // 0.0f));

  // float rotation_speed = 10.0f;

  if (mouse_pressed) {
    //   glm::vec3 axis = glm::normalize(
    //       orientation * glm::vec3(mouse_direction.y, -mouse_direction.x,
    //       0.0f));
    //   orientation =
    //       glm::mat3(glm::rotate(rotation_speed, axis) *
    //       glm::mat4(orientation));
    tangent = glm::column(orientation, 0);
    up = glm::column(orientation, 1);
    //   look = glm::column(orientation, 2);
    focus = eye + look * camera_distance;

    std::cout << "look:" << glm::to_string(look) << std::endl;
  }
}

void Gui::keyCallback(int key, int scancode, int action, int mods) { return; }

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