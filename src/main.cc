#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <unistd.h>

#include "vertex.h"
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>

static std::string
load_from_file(std::string const & filepath) {
  std::ifstream t(filepath);
  return std::string(std::istreambuf_iterator<char>(t),
                   std::istreambuf_iterator<char>());
}

static bool
check_shader_error(GLuint shader, GLuint flag, bool isProgram) {
  GLint success = 0;
  GLchar error[1024] = { 0 };

  if(isProgram)
    glGetProgramiv(shader, flag, &success);
  else
    glGetShaderiv(shader, flag, &success);

  if(success == GL_FALSE) {
    if(isProgram)
      glGetProgramInfoLog(shader, sizeof(error), nullptr, error);
    else
      glGetShaderInfoLog(shader, sizeof(error), nullptr, error);

    std::cerr << error << std::endl;

    return false;
  }

  return true;
}

static GLint
load_and_compile_shader(GLint id_program, std::string const & filepath, GLenum shaderType) {
  auto shader_contents = load_from_file(filepath);
  if (shader_contents.empty()) {
    std::cerr << "load_from_file() failed." << std::endl;
    return -1;
  }

  auto const id_shader = glCreateShader(shaderType);
  auto const pch = shader_contents.c_str();
  auto const length = static_cast<GLint>(shader_contents.size());
  glShaderSource(id_shader, 1, &pch, &length);
  glCompileShader(id_shader);
  if (!check_shader_error(id_shader, GL_COMPILE_STATUS, false)) {
    std::cerr << "glCompileShader() failed." << std::endl;
    return -1;
  }

  glAttachShader(id_program, id_shader);


  return id_shader;
}

int main() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "SDL_Init() failed: " << SDL_GetError() << std::endl;;
    return EXIT_FAILURE;
  }


  auto win = SDL_CreateWindow("Example",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              1000, 1000,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  auto gl_context = SDL_GL_CreateContext(win);

  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // glewExperimental = GL_TRUE;
  auto const res = glewInit();
  if(res != GLEW_OK) {
    std::cerr << "glewInit() failed: " << glewGetErrorString(res) << std::endl;;
    return EXIT_FAILURE;
  }

  using Vertices = std::vector<Vertex>;
  Vertices vec = {
    {{-0.5, -0.5, 0}, {}},
    {{0, 0.5, 0}, {}},
    {{0.5, -0.5, 0.0}, {}}
  };


  GLuint id_vertex_array = 0;
  glGenVertexArrays(1, &id_vertex_array);
  glBindVertexArray(id_vertex_array);

  GLuint id_buffer = 0;
  glGenBuffers(1, &id_buffer);

  glBindBuffer(GL_ARRAY_BUFFER, id_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vec[0]) * vec.size(), &vec[0], GL_STATIC_DRAW);

  // Describe the arrangement of bytes in the Vertex:
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  // glEnableVertexAttribArray(1);
  // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  glBindVertexArray(0);


  auto const id_program = glCreateProgram();
  auto const id_vertex_shader = load_and_compile_shader(id_program, "res/vertex_shader.vert", GL_VERTEX_SHADER);
  if (id_vertex_shader == -1) {
    std::cerr << "load_and_compile_shader() failed" << std::endl;
    return EXIT_FAILURE;
  }

  auto const id_fragment_shader = load_and_compile_shader(id_program, "res/fragment_shader.frag", GL_FRAGMENT_SHADER);
  if (id_fragment_shader == -1) {
    std::cerr << "load_and_compile_shader() failed" << std::endl;
    return EXIT_FAILURE;
  }

  // This is used in the shader.
  glBindAttribLocation(id_program, 0, "position");

  glLinkProgram(id_program);
  if (!check_shader_error(id_program, GL_LINK_STATUS, true)) {
    std::cerr << "glLinkProgram() failed." << std::endl;
    return -1;
  }

  glValidateProgram(id_program);
  if (!check_shader_error(id_program, GL_VALIDATE_STATUS, true)) {
    std::cerr << "glValidateProgram() failed." << std::endl;
    return -1;
  }

  SDL_Event e;
  bool running = true;
  while (running) {
    while (SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT)
        running = false;
    }

    glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(id_program);

    glBindVertexArray(id_vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, vec.size());
    glBindVertexArray(0);

    SDL_GL_SwapWindow(win);
    SDL_Delay(1);
  }

  glDetachShader(id_program, id_fragment_shader);
  glDeleteShader(id_fragment_shader);

  glDetachShader(id_program, id_vertex_shader);
  glDeleteShader(id_vertex_shader);

  glDeleteProgram(id_program);

  glDeleteVertexArrays(1, &id_vertex_array);

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return EXIT_SUCCESS;
}
