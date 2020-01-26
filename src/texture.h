#ifndef MURRAYC_OPENGL_EXPERIMENTS_TEXTURE_H
#define MURRAYC_OPENGL_EXPERIMENTS_TEXTURE_H

#include <GL/glew.h>
#include <string>


/**
 * Wraps an OpenGL Texture.
 */
class Texture {
public:
 Texture(std::string const & filepath);

  using ID = GLuint;

  ID id() const {
    return id_;
  }

  ~Texture();

private:
  ID id_{};
};

#endif // MURRAYC_OPENGL_EXPERIMENTS_TEXTURE_H
