#include "buffer.h"
#include "shader.h"
#include "program.h"
#include "vertex.h"
#include "vertex_array.h"
#include <vector>

#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <unistd.h>

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


  auto vertex_array = VertexArray();
  auto buffer = Buffer();
  {
    glBindVertexArray(vertex_array.id());

    glBindBuffer(GL_ARRAY_BUFFER, buffer.id());
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec[0]) * vec.size(), &vec[0], GL_STATIC_DRAW);

    // Describe the arrangement of bytes in the Vertex:
    // These same attribute ids are used later in the call to
    // glBindAttribLocation().
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec[0]), reinterpret_cast<void*>(offsetof(Vertex, position_)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec[0]), reinterpret_cast<void*>(offsetof(Vertex, extra_)));

    glBindVertexArray(0);
  }


  auto program = Program();
  auto const vertex_shader = Shader("res/vertex_shader.vert", GL_VERTEX_SHADER);
  if (!vertex_shader.id()) {
    std::cerr << "Shader failed" << std::endl;
    return EXIT_FAILURE;
  }
  program.attach(vertex_shader);

  auto const fragment_shader = Shader("res/fragment_shader.frag", GL_FRAGMENT_SHADER);
  if (!fragment_shader.id()) {
    std::cerr << "Shader failed" << std::endl;
    return EXIT_FAILURE;
  }
  program.attach(fragment_shader);

  if (!program.link()) {
    std::cerr << "Program::link() failed" << std::endl;
    return EXIT_FAILURE;
  }

  // This is used in the shader.
  program.bindAttributeLocation(0, "position");
  program.bindAttributeLocation(1, "extra");

  SDL_Event e;
  bool running = true;
  while (running) {
    while (SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT)
        running = false;
    }

    glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    program.use();

    glBindVertexArray(vertex_array.id());
    glDrawArrays(GL_TRIANGLES, 0, vec.size());
    glBindVertexArray(0);

    SDL_GL_SwapWindow(win);
    SDL_Delay(1);
  }

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return EXIT_SUCCESS;
}
