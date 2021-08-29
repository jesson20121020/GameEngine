#ifndef SHADER_H
#define SHADER_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <OpenGl/gl.h>

class Shader {

public:
  unsigned int ID;
  Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

  void use();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
};

#endif
