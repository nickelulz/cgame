#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgc.h>
#include <log.h>
#include "graphics.h"

static tgc_t local_gc;

static void
begin_file_read(const char *filepath, 
    FILE *file, long *filesize)
{
  file = fopen(filepath, "rb");
  if (!file) {
    ferrror("Could not load file %s from memory", 
        filepath);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  flength = tell(f);
  fseek(f, 0, SEEK_SET); 
}

static void
end_file_read(FILE *file)
{
  if (file)
    fclose(f);
}

uint32_t 
load_shader_from_file(const char *filepath, 
    GLenum shader_type)
{
  int _unused;
  tgc_start(&local_gc, &_unused);

  long filesize;
  FILE *file;
  char *buffer;

  begin_file_read(filepath, file, filesize);
    if (buffer = tgc_alloc(&local_gc, length))
      fread(buffer, 1, length, f);

    uint32_t shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, buffer, NULL);
    glCompileShader(shader);
  end_file_read(file);

  /* verify shader */

  int compilation_health;
  glGetShaderiv(vertex_shader, 
      GL_COMPILE_STATUS, &compilation_health);

  if (!compilation_health) {
    char info_log[512];
    glGetShaderInfoLog(
        vertex_shader, 512, NULL, info_log);
    log_error("Unable to compile shader: %s", 
        info_log);
  }

  tgc_stop(&local_gc);
}
