#ifndef MURRAYC_OPENGL_EXPERIMENTS_VERTEX_ARRAY_H
#define MURRAYC_OPENGL_EXPERIMENTS_VERTEX_ARRAY_H

#include "shader.h"
#include <GL/glew.h>
#include <vector>


class VertexArray {
public:
  VertexArray();

  using ID = GLuint;

  ID id() const {
    return id_;
  }

  ~VertexArray();

private:
  ID id_{};
};

#endif // MURRAYC_OPENGL_EXPERIMENTS_VERTEX_ARRAY_H
