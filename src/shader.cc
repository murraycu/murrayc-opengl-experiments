#include "shader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>


namespace {

std::string
load_from_file(std::string const & filepath) {
  std::ifstream t(filepath);
  return std::string(std::istreambuf_iterator<char>(t),
                   std::istreambuf_iterator<char>());
}

bool
check_shader_error(GLuint shader, GLuint flag) {
  GLint success = 0;
  GLchar error[1024] = { 0 };

  glGetShaderiv(shader, flag, &success);

  if(success == GL_FALSE) {
    glGetShaderInfoLog(shader, sizeof(error), nullptr, error);

    std::cerr << error << std::endl;

    return false;
  }

  return true;
}

GLint
load_and_compile_shader(std::string const & filepath, GLenum shaderType) {
  auto shader_contents = load_from_file(filepath);
  if (shader_contents.empty()) {
    std::cerr << "load_from_file() failed." << std::endl;
    return -1;
  }

  auto const id_shader = glCreateShader(shaderType);
  auto const pch = shader_contents.c_str();
  auto const length = static_cast<GLint>(shader_contents.size());
  glShaderSource(id_shader, 1, &pch, &length);
  glCompileShader(id_shader);
  if (!check_shader_error(id_shader, GL_COMPILE_STATUS)) {
    std::cerr << "glCompileShader() failed." << std::endl;
    return -1;
  }

  return id_shader;
}

} // anonymous namespace

Shader::Shader(const std::string& filepath, GLenum shaderType)
: id_(load_and_compile_shader(filepath, shaderType)) {
}

Shader::~Shader() {
  glDeleteShader(id_);
}
