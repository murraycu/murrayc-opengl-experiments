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


  auto win = SDL_CreateWindow("Exam ple",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              1000, 1000,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  auto gl_context = SDL_GL_CreateContext(win);

  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

  // glewExperimental = GL_TRUE;
  auto const res = glewInit();
  if(res != GLEW_OK) {
    std::cerr << "glewInit() failed: " << glewGetErrorString(res) << std::endl;;
    return EXIT_FAILURE;
  }

  sleep(2);


  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return EXIT_SUCCESS;
}
