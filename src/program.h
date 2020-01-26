#ifndef MURRAYC_OPENGL_EXPERIMENTS_PROGRAM_H
#define MURRAYC_OPENGL_EXPERIMENTS_PROGRAM_H

#include "camera.h"
#include "shader.h"
#include "transform.h"
#include <vector>

/**
 * Wraps an OpenGL Program.
 * First attach() Shaders, then link() and bindAttributeLocation().
 * Then use().
 *
 * Use set_tranform() to specify a transformation to be used by the shaders.
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

  /** Set a Transform to be used by the Shaders.
   * This assumes that the vertex shader has a line like this:
   * uniform mat4 transform
   */
  void set_transform_and_camera(Transform const & transform, Camera const & camera);

  void use();

private:

  ID id_{};
  std::vector<Shader::ID> attached_shaders_;

  GLint id_transform_uniform_{-1};
};

#endif // MURRAYC_OPENGL_EXPERIMENTS_PROGRAM_H
