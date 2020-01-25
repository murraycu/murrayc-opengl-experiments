#ifndef MURRAYC_OPENGL_EXPERIMENTS_VERTEX_H
#define MURRAYC_OPENGL_EXPERIMENTS_VERTEX_H

#include <glm/glm.hpp>

class Vertex {
public:
  Vertex(glm::vec3&& position)
  : position_(position) {
  }

  Vertex(glm::vec3 const & position)
  : position_(position) {
  }

  glm::vec3 position_;
};

#endif // MURRAYC_OPENGL_EXPERIMENTS_VERTEX_H
