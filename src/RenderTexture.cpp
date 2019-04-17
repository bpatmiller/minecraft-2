#include <glad/glad.h>

#include "RenderTexture.h"
#include <GLFW/glfw3.h>
#include <iostream>

RenderTexture::RenderTexture() {}

void RenderTexture::create(int width, int height) {
  w = width;
  h = height;

  fb = 0;
  tex = 0;

  glGenFramebuffers(1, &fb);
  glBindFramebuffer(GL_FRAMEBUFFER, fb);

  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glGenRenderbuffers(1, &dep);
  glBindRenderbuffer(GL_RENDERBUFFER, dep);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, dep);

  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);
  GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1, DrawBuffers);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "Failed to create framebuffer object as render target"
              << std::endl;
  } else {
    std::cerr << "Framebuffer ready" << std::endl;
  }
  unbind();
}

void RenderTexture::bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, fb);
  glViewport(0, 0, w, h);
}

void RenderTexture::unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void RenderTexture::bindTexture() { glBindTexture(GL_TEXTURE_2D, tex); }

void RenderTexture::unbindTexture() { glBindTexture(GL_TEXTURE_2D, 0); }

void RenderTexture::changeSize(int width, int height) {
  if (width != w || height != h) {
    w = width;
    h = height;
    bind();
    bindTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unbindTexture();

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tex, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, dep);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, dep);

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "ERROR framebuffer not complete" << std::endl;

    unbind();
  }
}

void RenderTexture::release() {
  if (fb == (unsigned int)-1)
    return;

  unbind();

  glDeleteFramebuffers(1, &fb);
  glDeleteTextures(1, &tex);
  glDeleteRenderbuffers(1, &dep);

  fb = 0;
  tex = 0;
  dep = 0;
}