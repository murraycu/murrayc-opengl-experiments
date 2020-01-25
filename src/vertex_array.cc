#include "vertex_array.h"

VertexArray::VertexArray() {
  glGenVertexArrays(1, &id_);
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &id_);
}
