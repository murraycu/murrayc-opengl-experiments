#include "camera.h"
#include "shader.h"
#include "program.h"
#include "vertex_array.h"
#include "texture.h"
#include <vector>

#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <unistd.h>

Camera camera;

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


void on_glfw_key(GLFWwindow* /* window */, int key, int /* scancode */, int action, int /* mods */)
{
    if (action != GLFW_PRESS && action != GLFW_REPEAT) {
      return;
    }

    switch (key) {
      case GLFW_KEY_UP:
        camera.move_forward();
        break ;
      case GLFW_KEY_DOWN:
        camera.move_back();
        break;
      case GLFW_KEY_LEFT:
        camera.move_left();
        break ;
      case GLFW_KEY_RIGHT:
        camera.move_right();
        break;
    }
}

} // anonymous namespace


int main() {
  if (glfwInit() != GLFW_TRUE) {
    std::cerr << "glfwInit() failed: " << glfwGetError(nullptr) << std::endl;;
    return EXIT_FAILURE;
  }

  // Allow use of OpenGL 4.5 (Core) in the shader programs.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //OpenGL core profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

  constexpr float WINDOW_WIDTH = 1000;
  constexpr float WINDOW_HEIGHT = 1000;

  glfwWindowHint(GLFW_GREEN_BITS, 8);
  glfwWindowHint(GLFW_BLUE_BITS, 8);
  glfwWindowHint(GLFW_ALPHA_BITS, 8);
  // TODO: glfw equivalent for this: SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  glfwWindowHint(GLFW_DEPTH_BITS, 16);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
  auto win = glfwCreateWindow(WINDOW_WIDTH,
                              WINDOW_HEIGHT,
                              "Example",
                              nullptr, nullptr);
  if (!win) {
    std::cerr << "glfwCreateWindow() failed: " << glfwGetError(nullptr) << std::endl;;
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(win);



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

  camera = Camera(glm::vec3{0, 0, -3}, 70.0f, WINDOW_WIDTH / WINDOW_HEIGHT, 0.01f, 1000.0f);

  Transform transform1;
  Transform transform2;
  float counter = 0.0f;

  glfwSetKeyCallback(win, &on_glfw_key);

  while (!glfwWindowShouldClose(win)) {
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

    glfwSwapBuffers(win);
    glfwPollEvents();
  }

  glfwDestroyWindow(win);
  glfwTerminate();

  return EXIT_SUCCESS;
}
