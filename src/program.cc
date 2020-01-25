#include "program.h"
#include "shader.h"

namespace {

bool
check_program_error(GLuint id, GLuint flag) {
  GLint success = 0;
  GLchar error[1024] = { 0 };

  glGetProgramiv(id, flag, &success);

  if(success == GL_FALSE) {
    glGetProgramInfoLog(id, sizeof(error), nullptr, error);

    std::cerr << error << std::endl;

    return false;
  }

  return true;
}

} // anonymous namespace

Program::Program()
: id_(glCreateProgram()) {
}

Program::~Program() {
  for (auto const shader_id : attached_shaders_) {
    glDetachShader(id_, shader_id);
  }

  glDeleteProgram(id_);
}

void
Program::attach(Shader  const & shader) {
  glAttachShader(id_, shader.id());
  attached_shaders_.emplace_back(shader.id());;
}

void
Program::use() {
  glUseProgram(id_);
}

bool
Program::link() {
  glLinkProgram(id_);
  if (!check_program_error(id_, GL_LINK_STATUS)) {
    std::cerr << "glLinkProgram() failed." << std::endl;
    return false;
  }

  glValidateProgram(id_);
  if (!check_program_error(id_, GL_VALIDATE_STATUS)) {
    std::cerr << "glValidateProgram() failed." << std::endl;
    return false;
  }

  return true;
}

void
Program::bindAttributeLocation(GLuint index, std::string const & name) {
  glBindAttribLocation(id_, index, name.c_str());
}
