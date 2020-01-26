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

  id_transform_uniform_ = glGetUniformLocation(id_, "transform");
  if (id_transform_uniform_ == -1) {
    std::cerr << "glGetUniformLocation() failed." << std::endl;
    return false;
  }

  return true;
}

void
Program::bindAttributeLocation(GLuint index, std::string const & name) {
  glBindAttribLocation(id_, index, name.c_str());
}

/*
std::ostream& operator<<(std::ostream& stream, const glm::mat4 &matrix) {

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      stream << matrix[i][j] << " ";
    }
    stream << std::endl;
  }

  return stream;
}
*/

void Program::set_transform_and_camera(Transform const & transform, Camera const & camera) {
  if (id_transform_uniform_ == -1) {
    std::cerr << "id_transform_uniform_ is 0. Maybe link() has not been called, or has failed." << std::endl;
    return;
  }

  auto const model = camera.view_projection() * transform.model();
  // std::cout << "debug model: " << std::endl << model << std::endl;
  glUniformMatrix4fv(id_transform_uniform_, 1, GL_FALSE, &model[0][0]);
}
