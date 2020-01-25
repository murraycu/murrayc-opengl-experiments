#ifndef MURRAYC_OPENGL_EXPERIMENTS_VERTEX_H
#define MURRAYC_OPENGL_EXPERIMENTS_VERTEX_H

#include <glm/glm.hpp>

class Vertex {
public:
  Vertex(glm::vec3&& position, glm::vec3&& extra)
  : position_(position), extra_(extra) {
  }

  Vertex(glm::vec3 const & position, glm::vec3 const & extra)
  : position_(position), extra_(extra) {
  }

  glm::vec3 position_;
  glm::vec3 extra_;
};

#endif // MURRAYC_OPENGL_EXPERIMENTS_VERTEX_H
