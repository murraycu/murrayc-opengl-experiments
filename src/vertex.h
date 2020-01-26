#ifndef MURRAYC_OPENGL_EXPERIMENTS_VERTEX_H
#define MURRAYC_OPENGL_EXPERIMENTS_VERTEX_H

#include <glm/glm.hpp>

class Vertex {
public:
  Vertex(glm::vec3&& position, glm::vec2&& texture_pos)
  : position_(position), texture_pos_(texture_pos) {
  }

  Vertex(glm::vec3 const & position, glm::vec2 const & texture_pos)
  : position_(position), texture_pos_(texture_pos) {
  }

  glm::vec3 position_{};
  glm::vec2 texture_pos_{};
};

#endif // MURRAYC_OPENGL_EXPERIMENTS_VERTEX_H
