#ifndef MURRAYC_OPENGL_EXPERIMENTS_SHADER_H
#define MURRAYC_OPENGL_EXPERIMENTS_SHADER_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>



class Shader {
public:
  Shader(const std::string& filepath, GLenum shaderType);

  using ID = GLuint;

  ID id() const {
    return id_;
  }

  ~Shader();

private:
  ID id_{};
};

#endif // MURRAYC_OPENGL_EXPERIMENTS_SHADER_H
