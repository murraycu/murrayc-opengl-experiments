#include "vertex_array.h"

VertexArray:: VertexArray(Vertices const & vertices)
: vertices_(vertices) {
  bind_buffer();
}


VertexArray:: VertexArray(Vertices&& vertices)
: vertices_(vertices) {
  bind_buffer();
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &id_);
}

void VertexArray::bind_buffer() {
  glGenVertexArrays(1, &id_);

  glBindVertexArray(id_);

  glBindBuffer(GL_ARRAY_BUFFER, buffer_.id());
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_[0]) * vertices_.size(), &vertices_[0], GL_STATIC_DRAW);

  // Describe the arrangement of bytes in the Vertex:
  // These same attribute ids are used later in the call to
  // glBindAttribLocation().
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), reinterpret_cast<void*>(offsetof(Vertex, position_)));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), reinterpret_cast<void*>(offsetof(Vertex, texture_pos_)));

  glBindVertexArray(0);
}

void VertexArray::draw_triangles() const {
  glBindVertexArray(id_);
  glDrawArrays(GL_TRIANGLES, 0, vertices_.size());
  glBindVertexArray(0);
}
