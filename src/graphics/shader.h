#ifndef SHADER_HEADER
#define SHADER_HEADER

#include <GLFW/glfw3.h>

enum shader_id {
  TRIANGLE_VERTEX = 0,
  TRIANGLE_FRAGMENT,

  NUM_SHADERS
};

typedef struct shader_t {
  const enum shader_id id;
  const GLenum shader_type;
  const char *name;
  const char *filepath;
  uint32_t shader;
} shader_t;

uint32_t  load_shader_from_file(const char *filepath, GLenum shader_type)

#endif
