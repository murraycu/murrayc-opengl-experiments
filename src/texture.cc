#include "texture.h"
#include <string>
#include <iostream>
#include "stb/stb_image.h"

Texture::Texture(std::string const & filepath) {
  glGenTextures(1, &id_);

  int width = 0;
  int height = 0;
  int numComponents = 0;
  auto data = stbi_load(filepath.c_str(), &width, &height, &numComponents, 4);
  if (!data) {
    std::cerr << "stbi_load() failed for " << filepath << std::endl;
    return;
  }

  glBindTexture(GL_TEXTURE_2D, id_);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);
}

Texture::~Texture() {
  glDeleteTextures(1, &id_);
}
