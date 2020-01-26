#ifndef MURRAYC_OPENGL_EXPERIMENTS_CAMERA_H
#define MURRAYC_OPENGL_EXPERIMENTS_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
  Camera(const glm::vec3& pos, float fov, float aspect, float znear, float zfar);

  glm::mat4 view_projection() const;

  void move_forward();
  void move_back();
  void move_left();
  void move_right();

private:
  glm::mat4 projection;
  glm::vec3 pos;
  glm::vec3 forward;
  glm::vec3 up;
};

#endif // MURRAYC_OPENGL_EXPERIMENTS_CAMERA_H
