#include "Gui.h"

#include "glm/gtx/rotate_vector.hpp"
#include <glm/glm.hpp>

void Gui::gravity() {
  if (!on_ground) {
    eye = eye + glm::vec3(0.0f, -0.05f, 0.0f);
  }
}

void Gui::checkGround(std::vector<glm::vec3> &offsets) {
  for (auto block : offsets) {
    // offset of a unit (0 - 1) cube
    bool x = (block[0] <= eye[0] && eye[0] <= block[0] + 1.0f);
    bool y = (block[1] + 2.0f >= eye[1]);
    bool z = (block[2] <= eye[2] && eye[2] <= block[2] + 1.0f);

    if (x && y && z) {
      on_ground = true;
      return;
    }
  }
  on_ground = false;
}

void Gui::clearRender() {
  glfwGetFramebufferSize(window, &window_width, &window_height);
  glViewport(0, 0, window_width, window_height);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glDepthFunc(GL_LESS);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCullFace(GL_BACK);
  updateMatrices();
}

void Gui::updateMatrices() {
  glm::mat4 translate = glm::mat4(1.0f);
  translate = glm::translate(translate, -eye);
  view_matrix = glm::mat4_cast(orientation) * translate;
  projection_matrix = glm::perspective(
      glm::radians(100.f), ((float)window_width) / window_height, 0.1f, 100.f);
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
  bool first = (current_x == -1 || current_y == -1);
  float dx = mouse_x - current_x;
  float dy = mouse_y - current_y;
  current_x = mouse_x;
  current_y = mouse_y;
  if (first)
    return;

  dx *= 0.25;
  dy *= 0.25;

  glm::quat qyaw = glm::angleAxis(glm::radians(dy), glm::vec3(1, 0, 0));
  glm::quat qpitch = glm::angleAxis(glm::radians(dx), glm::vec3(0, 1, 0));
  orientation = qyaw * orientation * qpitch;

  glm::mat4 inv = glm::inverse(glm::mat4_cast(orientation));

  fdir = glm::vec3(inv * glm::vec4(0, 0, -1, 1));
  sdir = glm::vec3(inv * glm::vec4(1, 0, 0, 1));
}

void Gui::keyCallback(int key, int scancode, int action, int mods) {
  float move_speed = 0.25f;
  if (key == GLFW_KEY_Q) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  } else if (key == GLFW_KEY_W) {
    eye += fdir * move_speed;
  } else if (key == GLFW_KEY_S) {
    eye -= fdir * move_speed;
  } else if (key == GLFW_KEY_A) {
    eye -= sdir * move_speed;
  } else if (key == GLFW_KEY_D) {
    eye += sdir * move_speed;
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