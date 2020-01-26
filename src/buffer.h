#ifndef MURRAYC_OPENGL_EXPERIMENTS_BUFFER_H
#define MURRAYC_OPENGL_EXPERIMENTS_BUFFER_H

#include "shader.h"
#include <GL/glew.h>
#include <vector>


/**
 * Wraps an OpenGL Buffer.
 */
class Buffer {
public:
  Buffer();

  using ID = GLuint;

  ID id() const {
    return id_;
  }

  ~Buffer();

private:
  ID id_{};
};

#endif // MURRAYC_OPENGL_EXPERIMENTS_BUFFER_H
