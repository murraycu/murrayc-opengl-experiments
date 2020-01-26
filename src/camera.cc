#include "camera.h"

#define  GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

Camera::Camera(const glm::vec3& position, float fov, float aspect, float znear, float zfar)
: pos(position) {
  forward = glm::vec3(0.0f, 0.0f, 1.0f);
  up = glm::vec3(0.0f, 1.0f, 0.0f);
  projection = glm::perspective(fov, aspect, znear, zfar);
}

glm::mat4 Camera::view_projection() const {
  return projection * glm::lookAt(pos, pos + forward, up);
}

void Camera::move_forward() {
  pos += forward * 0.1f;
}

void Camera::move_back() {
  pos -= forward * 0.1f;
}

void Camera::move_left() {
  pos += glm::cross(up, forward) * 0.1f;
}

void Camera::move_right() {
  pos -= glm::cross(up, forward) * 0.1f;
}
