#include "camera.h"
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

/**
 * Attach the shaders to the program,
 * and bind the attributes provided by VertexArray.
 */
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

  // This is used in the shader.
  // These are defined in VertexArray::bind_buffer().
  // These must be specified before the program (and its shaders) is linked.
  // Otherwise this will have no effect.
  // Alternatively, we could use glGetAttribLocation() (after linking) with OpenGL 4.
  program.bindAttributeLocation(VertexArray::AttributeID::POSITION,
    "position");
  program.bindAttributeLocation(VertexArray::AttributeID::NORMAL,
    "normal");
  program.bindAttributeLocation(VertexArray::AttributeID::TEXTURE_POS,
    "texture_pos");

  if (!program.link()) {
    std::cerr << "Program::link() failed" << std::endl;
    return false;
  }

  return true;
}

} // anonymous namespace

int main() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "SDL_Init() failed: " << SDL_GetError() << std::endl;;
    return EXIT_FAILURE;
  }

 constexpr float WINDOW_WIDTH = 1000;
 constexpr float WINDOW_HEIGHT = 1000;

  auto win = SDL_CreateWindow("Example",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
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

  // See the use of GL_DEPTH_BUFFER_BIT with glClear in the drawing loop.
  glEnable(GL_DEPTH_TEST);

  // Make drawing more "correct".
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  auto const vertex_array1 = VertexArray("res/teapot.obj");

  auto const vertex_array2 = VertexArray{
    {
      {{-0.5, -0.5, 0}, {}, {0.0, 0.0}},
      {{0, 0.5, 0}, {}, {0.0, 1.0}},
      {{0.5, -0.5, 0.0}, {}, {1.0, 0.0}}
    },
    {
      0, 1, 2
    }
  };

  Texture texture1("res/texture2.jpg");
  Texture texture2("res/texture1.jpg");

  auto program = Program();
  if (!setup_program(program)) {
    std::cerr << "setup_program() failed" << std::endl;
    return EXIT_FAILURE;
  }

  Camera camera(glm::vec3{0, 0, -3}, 70.0f, WINDOW_WIDTH / WINDOW_HEIGHT, 0.01f, 1000.0f);

  Transform transform1;
  Transform transform2;
  float counter = 0.0f;

  SDL_Event e;
  bool running = true;
  while (running) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN: {
          switch (e.key.keysym.sym) {
            case SDLK_UP:
              camera.move_forward();
              break ;
            case SDLK_DOWN:
              camera.move_back();
              break;
            case SDLK_LEFT:
              camera.move_left();
              break ;
            case SDLK_RIGHT:
              camera.move_right();
              break;
          }
          break;
        }
      }
    }

    glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    {
      transform1.scale.x = 0.01;
      transform1.scale.y = 0.01;
      transform1.scale.z = 0.01;
      transform1.translation.x = sinf(counter);
      transform1.translation.z = sinf(counter);
      transform1.rotation.z = counter * 2;
      transform1.rotation.y = counter * 2;

      // auto const cos_counter = cosf(counter);
      // transform1.scale = {cos_counter, cos_counter, cos_counter};
      counter += 0.01f;

      program.set_transform_and_camera(transform1, camera);
      program.use();

      glBindTexture(GL_TEXTURE_2D, texture1.id());

      vertex_array1.draw_triangles();
    }

    {
      transform2.translation.x = cosf(counter);

      program.set_transform_and_camera(transform2, camera);
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
