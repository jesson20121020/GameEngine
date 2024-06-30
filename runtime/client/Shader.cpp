#include "Shader.h"
#include "glheader.h"
#include "imgui.h"
#include "FileUtils.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {

   auto vsPath = FileUtils::getInstance()->getFullFilePath(vertexPath);
   auto fsPath = FileUtils::getInstance()->getFullFilePath(fragmentPath);

   // 1. 从文件路径读取顶点、片段着色器代码
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // 保证ifstream可以抛出异常
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    //打开文件
    vShaderFile.open(vsPath.c_str());
    fShaderFile.open(fsPath.c_str());
    std::stringstream vShaderStream, fShaderStream;

    // 读取文件缓冲区内容到数据流中
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    // 关闭文件处理器
    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();

  // 2.编译
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  // 顶点着色器

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  // 打印错误信息
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILE_FAILED\n"
              << infoLog << std::endl;
  }

  // 片段着色器
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILE_FAILED\n"
              << infoLog << std::endl;
  }

  // 着色器程序
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::LINK_Failed\n" << infoLog << std::endl;
  }

  // 删除着色器
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  // 读取Shader中的uniforms
  int total = -1;
  glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &total);
  int texCnt = 0;
  for (int i = 0; i < total; ++i) {
      int name_len = -1, num = -1;
      GLenum type = GL_ZERO;
      char name[100];
      glGetActiveUniform(ID, GLuint(i), sizeof(name) - 1, &name_len, &num, &type,
          name);
      name[name_len] = 0;
      GLuint location = glGetUniformLocation(ID, name);
      Uniform* uniform = nullptr;
      if (type == GL_BOOL)
          uniform = new BoolUniform(name, type);
      else if (type == GL_INT)
          uniform = new IntUniform(name, type);
      else if (type == GL_FLOAT)
          uniform = new FloatUniform(name, type);
      else if (type == GL_SAMPLER_2D)
      {
          uniform = new SampleUniform(name, type, texCnt);
          texCnt += 1;
      }
      if (uniform != nullptr)
         _uniforms.push_back(uniform);
  }
 }

  void Shader::use() { glUseProgram(ID); }

  void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
  }

  void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }

  void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }

  void Shader::setMat4(const std::string& name, glm::mat4 trans) const {
      glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
  }

  void Shader::drawImGui() 
  {
      if (_uniforms.size() == 0)
          return;
	  ImGui::Begin("Shader uniform");
	  for(auto iter = _uniforms.begin(); iter != _uniforms.end(); iter++)
	  {
          if ((*iter)->type == GL_FLOAT)
          {
              FloatUniform* uniform = static_cast<FloatUniform*>(*iter);
              glGetUniformfv(ID, glGetUniformLocation(ID, uniform->name.c_str()), &uniform->value);
              ImGui::SliderFloat(uniform->name.c_str(), &uniform->value, 0, 1, "%.2f", 0);
              setFloat(uniform->name, uniform->value);
          }
          else if ((*iter)->type == GL_SAMPLER_2D)
          {
              SampleUniform* uniform = static_cast<SampleUniform*>(*iter);
              char text_wrap_s[21];
              sprintf(text_wrap_s, "%s wrap s", uniform->name.c_str());
              glActiveTexture(GL_TEXTURE0 + uniform->pos);
              static const char* wrap_modes[] = {"GL_REPEAT", "GL_MIRRORED_REPEAT", "GL_CLAMP_TO_EDGE", "GL_CLAMP_TO_BORDER"};
              if (ImGui::Combo(text_wrap_s, &uniform->wrap_s, wrap_modes, 4, 0))
              {
                  int mode = GL_REPEAT;
                  if (uniform->wrap_s == 1)
                      mode = GL_MIRRORED_REPEAT;
                  else if (uniform->wrap_s == 2)
                      mode = GL_CLAMP_TO_EDGE;
                  else if (uniform->wrap_s == 3)
                      mode = GL_CLAMP_TO_BORDER;
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
              }
              char text_wrap_t[21];
              sprintf(text_wrap_t, "%s wrap t", uniform->name.c_str());
              if (ImGui::Combo(text_wrap_t, &uniform->wrap_t, wrap_modes, 4))
              {
                  int mode = GL_REPEAT;
                  if (uniform->wrap_t == 1)
                      mode = GL_MIRRORED_REPEAT;
                  else if (uniform->wrap_t == 2)
                      mode = GL_CLAMP_TO_EDGE;
                  else if (uniform->wrap_t == 3)
                      mode = GL_CLAMP_TO_BORDER;
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
              }

              static const char* filter_modes[] = { "GL_NEAREST_MIPMAP_NEAREST", "GL_LINEAR_MIPMAP_NEAREST", "GL_NEAREST_MIPMAP_LINEAR", "GL_LINEAR_MIPMAP_LINEAR" };
              char text_min_filter[21];
              sprintf(text_min_filter, "%s min filter", uniform->name.c_str());
              if (ImGui::Combo(text_min_filter, &uniform->min_filter, filter_modes, 4))
              {
                  int mode = GL_NEAREST_MIPMAP_NEAREST;
                  if (uniform->min_filter == 1)
                      mode = GL_LINEAR_MIPMAP_NEAREST;
                  else if (uniform->min_filter == 2)
                      mode = GL_NEAREST_MIPMAP_LINEAR;
                  else if (uniform->min_filter == 3)
                      mode = GL_LINEAR_MIPMAP_LINEAR;
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode);
              }

              char text_mag_filter[21];
              sprintf(text_mag_filter, "%s mag filter", uniform->name.c_str());
              if (ImGui::Combo(text_mag_filter, &uniform->mag_filter, filter_modes, 4))
              {
                  int mode = GL_NEAREST_MIPMAP_NEAREST;
                  if (uniform->mag_filter == 1)
                      mode = GL_LINEAR_MIPMAP_NEAREST;
                  else if (uniform->mag_filter == 2)
                      mode = GL_NEAREST_MIPMAP_LINEAR;
                  else if (uniform->mag_filter == 3)
                      mode = GL_LINEAR_MIPMAP_LINEAR;
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode);
              }

          }
	  }
	  ImGui::End();
  }
