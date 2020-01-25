#ifndef MURRAYC_OPENGL_EXPERIMENTS_PROGRAM_H
#define MURRAYC_OPENGL_EXPERIMENTS_PROGRAM_H

#include "shader.h"
#include <GL/glew.h>
#include <vector>


class Program {
public:
  Program();

  using ID = GLuint;

  ID id() const {
    return id_;
  }

  ~Program();

  void attach(Shader  const & shader);

  bool link();
  void use();

private:

  ID id_{};
  std::vector<Shader::ID> attached_shaders_;

};

#endif // MURRAYC_OPENGL_EXPERIMENTS_PROGRAM_H
