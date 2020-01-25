#include "buffer.h"

Buffer::Buffer() {
  glGenBuffers(1, &id_);
}

Buffer::~Buffer() {
  glDeleteBuffers(1, &id_);
}
