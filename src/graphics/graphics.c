#include <stdlib.h>

#include <log.h>

#include "graphics.h"
#include "renderer.h"
#include "color.h"

static const fcolor_t 
  __attribute__((unused)) 
  WHITE = { .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 0.0f },
  SLATE = { .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.0f };

static int
graphics_load_shaders(graphics_t *graphics)
{
  __attribute__((unused)) const uint32_t UNINITIALIZED = 0;

  graphics->shaders = {
    /* Triangle Vertex Shader */
    { TRIANGLE_VERTEX, GL_VERTEX_SHADER, "TRIANGLE_VERTEX",
      "./src/graphics/shaders/vertex.glsl", UNITIALIZED },

    /* Triangle Fragment Shader */
    { TRIANGLE_FRAGMENT, GL_FRAGMENT_SHADER, "TRIANGLE_FRAGMENT", 
      "./src/graphics/shaders/fragment.glsl", UNITIALIZED }
  }; 

  for (uint8_t i = 0; i < NUM_SHADERS; ++i)
    graphics->shaders[i].shader = load_shader_from_file(
      graphics->shaders[i].filepath, 
      graphics->shaders[i].shader_type);

  graphics->active_vertex_shader = TRIANGLE_VERTEX;
  graphics->active_fragment_shader = TRIANGLE_FRAGMENT;
}

void 
graphics_render(graphics_t *graphics)
{
  glClearColor(SLATE.r, SLATE.g, SLATE.b, SLATE.a);
  glClear(GL_COLOR_BUFFER_BIT);

  graphics_draw_triangle(graphics);

  glfwSwapBuffers(graphics->window);
  glfwPollEvents();  
}

void
graphics_initialize(graphics_t *graphics)
{
  if (!glfwInit()) {
    log_fatal("Failed to initialize GLFW");
    exit(EXIT_FAILURE);
  }

  window_initialize_context(graphics);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    log_fatal("Failed to initialize GLAD");
    exit(EXIT_FAILURE);
  }

  graphics_load_shaders(graphics);
  window_initialize_frame_buffer(graphics);
}

void
graphics_exit(__attribute__((unused)) graphics_t *graphics)
{
  glfwTerminate();
}
