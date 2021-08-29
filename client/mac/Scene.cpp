//
//  scene.cpp
//  client
//
//  Created by jesson on 2021/8/28.
//

#include "Scene.h"
#include <OpenGL //gl.h>
#include <OpenGL/OpenGL.h>
#include <OpenGl/glu.h>

void Init(float width, float height) {
  glMatrixMode(GL_PROJECTION);
  gluPerspective(50.0f, width / height, 0.1f, 1000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Renderer() {
  glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

/*
 * 你好，三角形
 * */
void OpenGL_Hello_Triangle() {
  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


  char* vsShader = "
#version 330 core
	  layout (location 0) in vec3 aPos;
  void main(){
	  gl_Position =
  }
	  "


}
