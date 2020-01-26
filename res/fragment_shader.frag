#version 130

// This is set in our fragment shader,
// though we actually get an interpolated (for a pixel) value
// based on the fragment shader's per-vertex values.
varying vec2 texture_pos0;

// This seems to be set just by our call to glBindTexture().
uniform sampler2D diffuse;

void main() {
  gl_FragColor = texture2D(diffuse, texture_pos0);
}
