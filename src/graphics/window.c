#include "../config.h"
#include "graphics.h"

#include <log.h>

static graphics_t *_global_gfx;

static void
framebuffer_size_callback(
    __attribute__((unused)) GLFWwindow *window, 
    int width, int height)
{
  glViewport(0, 0, width, height);
  _global_gfx->size = (ivec2s) {{width, height}};
}

void 
window_initialize_context(graphics_t *graphics) 
{
  _global_gfx = graphics;

  graphics->size = (ivec2s) {{ WIN_WIDTH, WIN_HEIGHT }};
  graphics->window = glfwCreateWindow(
      graphics->size.x, graphics->size.y, 
      TITLE, NULL, NULL);
  if (NULL == graphics->window) {
    log_fatal("Could not initialize GLFW window.");
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(graphics->window);
}

void
window_initialize_frame_buffer(graphics_t *graphics)
{
  glViewport(0, 0, graphics->size.y, graphics->size.x);
  glfwSetFramebufferSizeCallback(
      graphics->window, 
      framebuffer_size_callback);
}
