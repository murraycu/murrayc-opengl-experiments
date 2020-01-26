#include "shader.h"
#include "program.h"
#include "vertex_array.h"
#include "texture.h"
#include <vector>

#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <unistd.h>

namespace {

bool
setup_program(Program& program) {
  auto const vertex_shader = Shader("res/vertex_shader.vert", GL_VERTEX_SHADER);
  if (!vertex_shader.id()) {
    std::cerr << "Shader failed" << std::endl;
    return false;
  }
  program.attach(vertex_shader);

  auto const fragment_shader = Shader("res/fragment_shader.frag", GL_FRAGMENT_SHADER);
  if (!fragment_shader.id()) {
    std::cerr << "Shader failed" << std::endl;
    return false;
  }
  program.attach(fragment_shader);

  if (!program.link()) {
    std::cerr << "Program::link() failed" << std::endl;
    return false;
  }

  // This is used in the shader.
  program.bindAttributeLocation(0, "position");
  program.bindAttributeLocation(1, "texture_pos");

  return true;
}

} // anonymous namespace

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

  auto const vertex_array1 = VertexArray{
    {
      {{-0.5, -0.5, 0}, {0.0, 0.0}},
      {{0, 0.5, 0}, {0.0, 1.0}},
      {{0.5, -0.5, 0.0}, {1.0, 0.0}}
    }
  };

  auto const vertex_array2 = VertexArray{
    {
      {{-1.0, -0.0, 0}, {0.0, 0.0}},
      {{0, -0.2, 0}, {0.0, 0.7}},
      {{0.0, -0.5, 0.0}, {1.0, 0.0}}
    }
  };

  Texture texture1("res/texture1.jpg");
  Texture texture2("res/texture2.jpg");

  auto program = Program();
  if (!setup_program(program)) {
    std::cerr << "setup_program() failed" << std::endl;
    return EXIT_FAILURE;
  }

  Transform transform1;
  Transform transform2;
  float counter = 0.0f;

  SDL_Event e;
  bool running = true;
  while (running) {
    while (SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT)
        running = false;
    }

    glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    {
      transform1.translation.x = sinf(counter);
      transform1.rotation.z = counter * 5;

      auto const cos_counter = cosf(counter);
      transform1.scale = {cos_counter, cos_counter, cos_counter};
      counter += 0.01f;

      program.set_transform(transform1);
      program.use();

      glBindTexture(GL_TEXTURE_2D, texture1.id());

      vertex_array1.draw_triangles();
    }

    {
      transform2.translation.x = cosf(counter);

      program.set_transform(transform2);
      program.use();

      glBindTexture(GL_TEXTURE_2D, texture2.id());

      vertex_array2.draw_triangles();
    }

    SDL_GL_SwapWindow(win);
    SDL_Delay(1);
  }

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return EXIT_SUCCESS;
}
