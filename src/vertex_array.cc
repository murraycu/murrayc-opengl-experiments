#include "vertex_array.h"

VertexArray::VertexArray(Vertices const & vertices, Indices const & indices)
: vertices_(vertices),
  indices_(indices) {
  bind_buffer();
}

VertexArray::VertexArray(Vertices && vertices, Indices && indices)
: vertices_(std::move(vertices)),
  indices_(std::move(indices)) {
  bind_buffer();
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &id_);
}

void VertexArray::bind_buffer() {
  glGenVertexArrays(1, &id_);

  {
    glBindVertexArray(id_);

    glBindBuffer(GL_ARRAY_BUFFER, buffer_vertices_.id());
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices_.size(), &vertices_[0], GL_STATIC_DRAW);

    // Describe the arrangement of bytes in the Vertex:
    // These same attribute ids are used later in the call to
    // glBindAttribLocation().
    glEnableVertexAttribArray(AttributeID::POSITION);
    glVertexAttribPointer(AttributeID::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position_)));

    glEnableVertexAttribArray(AttributeID::NORMAL);
    glVertexAttribPointer(AttributeID::NORMAL, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal_)));

    glEnableVertexAttribArray(AttributeID::TEXTURE_POS);
    glVertexAttribPointer(AttributeID::TEXTURE_POS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texture_pos_)));

    glBindVertexArray(0);
  }

  {
    glBindVertexArray(id_);

    // GL_ELEMENT_ARRAY_BUFFER means that these values reference items in
    // another array.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indices_.id());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices::value_type) * indices_.size(), &indices_[0], GL_STATIC_DRAW);

    // Describe the arrangement of bytes in the Vertex:
    // These same attribute ids are used later in the call to
    // glBindAttribLocation().
    glEnableVertexAttribArray(AttributeID::INDEX);
    glVertexAttribPointer(AttributeID::INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
  }
}

void VertexArray::draw_triangles() const {
  glBindVertexArray(id_);

  // We draw by specifying the indices instead of the elements directly (with
  // glDrawArrays()).
  // TODO: How does OpenGL know that these are indices into the other buffer's data?
  glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
