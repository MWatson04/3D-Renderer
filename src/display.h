#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define FPS 60 
#define FRAME_TARGET_TIME (1000 / FPS)

// New type for 32-bit color values
typedef uint32_t color_t;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern color_t* color_buffer;
extern SDL_Texture* color_buffer_texture;
extern int window_width;
extern int window_height;

bool initialize_window(void); 
void draw_grid(color_t color);
void draw_pixel(int x, int y, color_t color);
void draw_line(int x0, int y0, int x1, int y1, color_t color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);
void draw_rect(int x, int y, int width, int height, color_t color);
void render_color_buffer(void); 
void clear_color_buffer(color_t color);
void destroy_window(void);

#endif
