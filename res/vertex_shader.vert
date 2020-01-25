#version 130

// See our call to glBindAttribLocation() which created this attribute name.
attribute vec3 position;
attribute vec3 extra;

void main() {
  // Use the vec3 position that's in the position attribute.
  // and the vec3 extra,  that's in the extra attribute,
  // just to show that we can use 2.
  gl_Position = vec4(
    position.x + extra.x,
    position.y + extra.y,
    position.z + extra.z,
    1.0);
}
