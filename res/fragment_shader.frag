#version 450 core

// This is set in our vertex shader,
// though we actually get an interpolated (for a pixel) value
// based on the vertex shader's per-vertex values.
in vec2 texture_pos0;

// (With OpenGL < 3 we would just use gl_FragColor instead.)
out vec4 fragColor;

// This seems to be set just by our call to glBindTexture().
uniform sampler2D diffuse;

void main() {
  fragColor = texture2D(diffuse, texture_pos0);
}
