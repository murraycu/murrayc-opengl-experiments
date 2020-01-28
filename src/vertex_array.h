#ifndef MURRAYC_OPENGL_EXPERIMENTS_VERTEX_ARRAY_H
#define MURRAYC_OPENGL_EXPERIMENTS_VERTEX_ARRAY_H

#include "buffer.h"
#include "vertex.h"
#include <GL/glew.h>
#include <vector>


class VertexArray {
public:
  using Vertices = std::vector<Vertex>;

  explicit VertexArray(Vertices const & vertices);
  explicit VertexArray(Vertices&& vertices);
  ~VertexArray();

  using ID = GLuint;

  ID id() const {
    return id_;
  }

  enum AttributeID{
    POSITION = 0,
    TEXTURE_POS,
  };

  void draw_triangles() const;

private:
  void bind_buffer();

  ID id_{};
  Buffer buffer_;
  Vertices const vertices_;
};

#endif // MURRAYC_OPENGL_EXPERIMENTS_VERTEX_ARRAY_H
