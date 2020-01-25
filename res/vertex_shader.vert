#version 130

// See our call to glBindAttribLocation() which created this attribute name.
attribute vec3 position;

void main() {
  // Use the vec3 position that's in the position attribute.
  gl_Position = vec4(position, 1.0);
}
