#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/struct.h>

#include "shader.h"

typedef struct graphics_t 
{
  GLFWwindow *window;
  ivec2s size;

  /* Rendering Information */ 
  enum shader_id 
    active_vertex_shader,
    active_fragment_shader;
  shader_t shaders[NUM_SHADERS];
} graphics_t;

void graphics_initialize(graphics_t *graphics);
void graphics_exit(graphics_t *graphics);
void graphics_render(graphics_t *graphics);

#include "window.h"

#endif
