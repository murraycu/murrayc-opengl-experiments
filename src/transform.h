#ifndef MURRAYC_OPENGL_EXPERIMENTS_TRANSFORM_H
#define MURRAYC_OPENGL_EXPERIMENTS_TRANSFORM_H

#include "shader.h"
#include <glm/glm.hpp>

#include <vector>

class Transform {
public:
  glm::mat4 model() const;

  glm::vec3 translation{};
  glm::vec3 rotation{};

  // Initialized to identity matrix, so it has no effect.
  glm::vec3 scale{1.0f, 1.0f, 1.0f};
};

#endif // MURRAYC_OPENGL_EXPERIMENTS_TRANSFORM_H
