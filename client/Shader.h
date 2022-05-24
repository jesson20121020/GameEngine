#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Uniform {
  std::string name;
  unsigned int type;
  Uniform(std::string _name, unsigned int _type) : name(_name), type(_type) {}
};

struct BoolUniform : Uniform {
  bool value;
  BoolUniform(std::string _name, unsigned int _type)
      : Uniform(_name, _type) {}
};

struct IntUniform : Uniform {
  int value;
  IntUniform(std::string _name, unsigned int _type)
      : Uniform(_name, _type){}
};

struct FloatUniform : Uniform {
  float value;
  FloatUniform(std::string _name, unsigned int _type)
      : Uniform(_name, _type) {
      value = 0.0f;
  }
};

struct SampleUniform : Uniform {
  char *value;
  int wrap_s, wrap_t, min_filter, mag_filter, pos;
  SampleUniform(std::string _name, unsigned int _type, int _pos)
      : Uniform(_name, _type), pos(_pos) {
      wrap_s = 0;
      wrap_t = 0;
      min_filter = 0;
      mag_filter = 0;
  }
};

class Shader {

public:
  unsigned int ID;
  Shader(const char *vertexPath, const char *fragmentPath);

  void use();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void drawImGui();
private:
  std::vector<Uniform*> _uniforms;
};

#endif
