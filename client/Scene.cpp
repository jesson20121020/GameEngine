//
//  scene.cpp
//  client
//
//  Created by jesson on 2021/8/28.
//

#include "Scene.h"
#include "Shader.h"
#include "glheader.h"

// https://learnopengl-cn.github.io/01%20Getting%20started/05%20Shaders/
void Test_Init_DrawTriangle() {
  float vertices[] = {
      -0.5f, -0.5f, 0.0f, // left
      0.5f,  -0.5f, 0.0f, // right
      0.0f,  0.5f,  0.0f  // top
  };

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO
  // as the vertex attribute's bound vertex buffer object so afterwards we can
  // safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally
  // modify this VAO, but this rarely happens. Modifying other VAOs requires a
  // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
  // VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  Shader shader("G:\\Projects\\GitLab\\GameEngine\\client\\res\\test001.vs", "G:\\Projects\\GitLab\\GameEngine\\client\\res\\test001.ps");
  shader.use();
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Init(float width, float height) {
  glewInit();
  glMatrixMode(GL_PROJECTION);
  gluPerspective(50.0f, width / height, 0.1f, 1000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Renderer() {
  glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  
  // Test_Init_DrawTriangle();
  glFlush();
}
