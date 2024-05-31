#include <stdio.h>
#include <stdint.h>

#include <log.h>
#include <tgc.h>

#include "graphics/graphics.h"

int 
main(int argc, __attribute__((unused)) char *argv[]) 
{
  tgc_t global_gc;
  tgc_start(&global_gc, &argc);

  graphics_t graphics;
  graphics_initialize(&graphics); 

  while (!glfwWindowShouldClose(graphics.window)) {
    graphics_render(&graphics); 
  }

  graphics_exit(&graphics);

  tgc_stop(&global_gc);
  return 0;
}
