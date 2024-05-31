#ifndef COLOR_HEADER
#define COLOR_HEADER

typedef struct fcolor_t {
  float r, g, b, a; 
} fcolor_t;

typedef struct icolor_t { 
  uint16_t r, g, b, a;
} icolor_t;

static inline icolor_t 
fcolor_to_icolor(fcolor_t src)
{
  return (icolor_t) {
    .r = (uint16_t) (src.r * 255),
    .g = (uint16_t) (src.g * 255),
    .b = (uint16_t) (src.b * 255),
    .a = (uint16_t) (src.a * 255)
  };
}

static inline fcolor_t
icolor_to_fcolor(icolor_t src)
{
  return (fcolor_t) {
    .r = (uint16_t) (src.r / 255),
    .g = (uint16_t) (src.g / 255),
    .b = (uint16_t) (src.b / 255),
    .a = (uint16_t) (src.a / 255)
  };
}

#endif
