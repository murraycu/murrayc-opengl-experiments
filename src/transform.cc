#include "transform.h"

glm::mat4 Transform::model() const {
  // TODO: Cache this instead of recalculating if nothing has changed?
  auto const rot = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0))
      * glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0))
      * glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));

  return glm::translate(translation)
      * rot
      * glm::scale(scale);
}

