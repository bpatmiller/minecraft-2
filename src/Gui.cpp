#include "Gui.h"

#include "glm/gtx/rotate_vector.hpp"
#include <glm/glm.hpp>

void Gui::gravity() {
  if (!on_ground && !flying) {
    eye = eye + momentum;
    momentum.y -= 0.015;
    momentum.x *= 0.95;
    momentum.z *= 0.95;

  } else {
    momentum = glm::vec3(0.0);
  }
}

bool Gui::groundBlock(glm::vec4 &block) {
  bool x = (block[0] <= eye[0] && eye[0] <= block[0] + 1.0f);
  bool y = (block[1] + 2.75f >= eye[1]);
  bool z = (block[2] <= eye[2] && eye[2] <= block[2] + 1.0f);
  return (x && y && z);
}

bool Gui::collideBlock(glm::vec4 &block, glm::vec3 &offset, float move_speed) {
  glm::vec3 new_eye = eye + (offset * move_speed);

  bool x = (block[0] <= new_eye[0] && new_eye[0] <= block[0] + 1.0f);
  bool y = (block[1] >= new_eye[1] - 1.75 && block[1] <= new_eye[1] - 0.75);
  bool z = (block[2] <= new_eye[2] && new_eye[2] <= block[2] + 1.0f);
  return (x && y && z);
}

void Gui::checkGround(std::vector<glm::vec4> &offsets) {
  if (flying)
    return;

  on_ground = false;
  colw = false;
  cols = false;
  cola = false;
  cold = false;
  for (auto block : offsets) {
    if (block[3] == 1.0) {
      continue;
    }
    if (groundBlock(block))
      on_ground = true;

    colw = (colw || collideBlock(block, gfdir, 0.25f));
    cols = (cols || collideBlock(block, gfdir, -0.25f));
    cola = (cola || collideBlock(block, gsdir, -0.25f));
    cold = (cold || collideBlock(block, gsdir, 0.25f));
  }
}

void Gui::clearRender() {
  glfwGetFramebufferSize(window, &window_width, &window_height);
  glViewport(0, 0, window_width, window_height);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDepthFunc(GL_LESS);
  glCullFace(GL_BACK);
}

void Gui::updateMatrices() {
  screenRes = glm::vec3(window_width, window_height, 0.0f);

  gfdir = glm::vec3(fdir.x, 0, fdir.z);
  gsdir = glm::vec3(sdir.x, 0, sdir.z);

  glm::mat4 translate = glm::mat4(1.0f);
  translate = glm::translate(translate, -eye);
  view_matrix = glm::mat4_cast(orientation) * translate;
  projection_matrix = glm::perspective(
      glm::radians(100.f), ((float)window_width) / window_height, 0.1f, 200.f);
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

  dx *= 0.5;
  dy *= 0.5;

  glm::quat qyaw = glm::angleAxis(glm::radians(dy), glm::vec3(1, 0, 0));
  glm::quat qpitch = glm::angleAxis(glm::radians(dx), glm::vec3(0, 1, 0));
  orientation = qyaw * orientation * qpitch;

  glm::mat4 inv = glm::inverse(glm::mat4_cast(orientation));

  fdir = glm::vec3(inv * glm::vec4(0, 0, -1, 1));
  sdir = glm::vec3(inv * glm::vec4(1, 0, 0, 1));
}

void Gui::keyCallback(int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_Q) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  } else if (key == GLFW_KEY_F && (mods & GLFW_MOD_CONTROL) &&
             action != GLFW_RELEASE) {
    std::cout << "flying mode toggle" << std::endl;
    flying = !flying;
  }
  if (mods & GLFW_MOD_SHIFT) {
    momentum += fdir;
    eye += momentum;
  }

  if (action == GLFW_PRESS) {
    keyHeld[key] = true;
  } else if (action == GLFW_RELEASE) {
    keyHeld[key] = false;
  }
}

void Gui::applyKeyboardInput() {
  float move_speed = 0.25f;

  if (flying) {
    if (keyHeld[GLFW_KEY_W]) {
      eye += fdir * move_speed;
    }
    if (keyHeld[GLFW_KEY_S]) {
      eye -= fdir * move_speed;
    }
    if (keyHeld[GLFW_KEY_A]) {
      eye -= sdir * move_speed;
    }
    if (keyHeld[GLFW_KEY_D]) {
      eye += sdir * move_speed;
    }
  } else {
    if (!colw && keyHeld[GLFW_KEY_W]) {
      eye += gfdir * move_speed;
    }
    if (!cols && keyHeld[GLFW_KEY_S]) {
      eye -= gfdir * move_speed;
    }
    if (!cola && keyHeld[GLFW_KEY_A]) {
      eye -= gsdir * move_speed;
    }
    if (!cold && keyHeld[GLFW_KEY_D]) {
      eye += gsdir * move_speed;
    }
    if (on_ground && keyHeld[GLFW_KEY_SPACE]) {
      momentum.y = 0.25;
      eye = eye + glm::vec3(0.0f, momentum.y, 0.0f);
    }
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
  // glfwSetCursorPos(window, gui->window_width/ 2, gui->window_height / 2);
  // gui->current_x = gui->window_width/ 2;
  // gui->current_y = gui->window_height / 2;
}

void Gui::KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                      int mods) {
  Gui *gui = (Gui *)glfwGetWindowUserPointer(window);
  gui->keyCallback(key, scancode, action, mods);
}