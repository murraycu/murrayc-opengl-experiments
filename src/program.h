#ifndef MURRAYC_OPENGL_EXPERIMENTS_PROGRAM_H
#define MURRAYC_OPENGL_EXPERIMENTS_PROGRAM_H

#include "shader.h"
#include <GL/glew.h>
#include <vector>


/**
 * Wraps an OpenGL Program.
 * First attach() Shaders, then link() and bindAttributeLocation().
 * Then use().
 */
class Program {
public:
  Program();

  using ID = GLuint;

  ID id() const {
    return id_;
  }

  ~Program();

  void attach(Shader const & shader);

  bool link();
  void bindAttributeLocation(GLuint index, std::string const & name);
  void use();

private:

  ID id_{};
  std::vector<Shader::ID> attached_shaders_;

};

#endif // MURRAYC_OPENGL_EXPERIMENTS_PROGRAM_H
