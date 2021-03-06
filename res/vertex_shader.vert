#version 450 core

// The position of an individual vertex.
// See our call to glBindAttribLocation() which created this attribute name.
in vec3 position;

in vec3 normal;

// The texture position of an individual vertex.
// See our call to glBindAttribLocation() which created this attribute name.
in vec2 texture_pos;

out vec2 texture_pos0;

// A transformation to apply to all vertices.
// See our call to
uniform mat4 transform;

void main() {
  // Use the vec3 position that's in the position attribute.
  // and the transform matrix that's in the transform uniform.
  gl_Position = transform * vec4(position, 1.0);


  // Pass this to the fragment shader.
  texture_pos0 = texture_pos;
}
