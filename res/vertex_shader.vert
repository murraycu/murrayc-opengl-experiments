#version 130

// The position of an individual vertex.
// See our call to glBindAttribLocation() which created this attribute name.
attribute vec3 position;

// A transformation to apply to all vertices.
// See our call to
uniform mat4 transform;

void main() {
  // Use the vec3 position that's in the position attribute.
  // and the transform matrix that's in the transform uniform.
  gl_Position = transform * vec4(position, 1.0);
}
