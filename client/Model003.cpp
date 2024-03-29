#include "Model003.h"
#include "Shader.h"
#include "glheader.h"
#include "imgui.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "FileUtils.h"

Model003::Model003() {
	_modelName = "入门-变换";
	for(int i = 0; i < 2; i++)
	{
		_scale[i] = 1.0f;
		_pos[i] = 0.0f;
		_rotate[i] = 0.0f;
	}
}

void Model003::init() {
  float vertices[] = {
      // positions          // colors           // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
  };
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  unsigned int VBO, EBO;
  glGenVertexArrays(1, &_vao);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(_vao);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // load and create a texture
  // -------------------------
  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_2D,
                _texture); // all upcoming GL_TEXTURE_2D operations now have
                           // effect on this texture object
                           // set the texture wrapping parameters
  glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
      GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int width, height, nrChannel;
  // The FileSystem::getPath(...) is part of the GitHub repository so we can
  // find files on any IDE/platform; replace it with your own image path.
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data =
      stbi_load(FileUtils::getInstance()->getFullFilePath("test2.jpg").c_str(), &width,
          &height, &nrChannel, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture";
  }
  stbi_image_free(data);

  // load and create a texture
  // -------------------------
  glGenTextures(1, &_texture1);
  glBindTexture(GL_TEXTURE_2D,
                _texture1); // all upcoming GL_TEXTURE_2D operations now have
                            // effect on this texture object
                            // set the texture wrapping parameters
  glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
      GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  // The FileSystem::getPath(...) is part of the GitHub repository so we can
  // find files on any IDE/platform; replace it with your own image path.
  stbi_set_flip_vertically_on_load(true);
  data = stbi_load(FileUtils::getInstance()->getFullFilePath("test.jpg").c_str(), &width,
      &height, &nrChannel, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture";
  }
  stbi_image_free(data);

  glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
  glBindTexture(GL_TEXTURE_2D, _texture);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, _texture1);

  glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
  glBindTexture(GL_TEXTURE_2D, _texture);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, _texture1);

  _shader = new Shader("test003.vs",
                       "test003.ps");
  _shader->use();
  _shader->setInt("texture1", 0);
  _shader->setInt("texture2", 1);

  glm::mat4 trans;
  trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0, 0, 1));
  trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0));
  _shader->setMat4("transform", trans);
}

void Model003::draw() { glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); }


void Model003::renderImGui()
{
	Model::renderImGui();
	ImGui::Begin("旋转缩放调整");
  ImGui::SliderFloat2("平移", _pos, -1, 1, "%.2f", 0);
  ImGui::SliderFloat2("旋转", _rotate, 0, 360, "%.2f", 0);
  ImGui::SliderFloat2("缩放", _scale, 0, 10, "%.2f");
  ImGui::End();
  glm::mat4 trans;
  trans = glm::rotate(trans, glm::radians(_rotate[0]), glm::vec3(0, 0, 1));
  trans = glm::rotate(trans, glm::radians(_rotate[1]), glm::vec3(1, 0, 0));
  trans = glm::scale(trans, glm::vec3(_scale[0], _scale[1], 0));
  trans = glm::translate(trans, glm::vec3(_pos[0], _pos[1], 0));
  _shader->setMat4("transform", trans);
}

void Model003::destroy() {}
