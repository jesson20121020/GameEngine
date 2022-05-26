#include "Model004.h"
#include "Shader.h"
#include "glheader.h"
#include "imgui.h"
#include "stb_image.h"

Model004::Model004()
{
    _modelName = "入门-坐标系统 ";
}

void Model004::init() {
  float vertices[] = {
      -0.5f, -0.5f, 0.0f, // left
      0.5f,  -0.5f, 0.0f, // right
      0.0f,  0.5f,  0.0f  // top
  };

  unsigned int VBO;
  glGenVertexArrays(1, &_vao);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(_vao);

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
  _shader = new Shader("G:\\Projects\\GitLab\\GameEngine\\client\\res\\test001.vs",
      "G:\\Projects\\GitLab\\GameEngine\\client\\res\\test001.ps");
  _shader->use();
}

void Model004::draw() { 
    glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Model004::destroy() {}
