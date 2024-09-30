#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
int window_width = 800;
int window_height = 600;

bool initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error Initializing SDL.\n");
		return false;
	}

	// Query for maximum monitor resolution
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	window_width = display_mode.w;
	window_height = display_mode.h;

	// Create SDL Window	
	window = SDL_CreateWindow(
		NULL,                        // Window Title, NULL for no name
		SDL_WINDOWPOS_CENTERED,      // Where the window will show up on monitor displayed
		SDL_WINDOWPOS_CENTERED,      // WINDOWPOS_CENTERED for center of monitor
		window_width,                // Window Width
		window_height,               // Window Height
		SDL_WINDOW_BORDERLESS 		 // Any flags for display window, Borderless in this case
	);
	if (!window) {
		fprintf(stderr, "Error Creating SDL Window.\n");
		return false;
	}
	
	// Create SDL Renderer
	renderer = SDL_CreateRenderer(
		window,                      // Pass in window object for the renderer to use
		-1,                          // Get monitor device to render on to, -1 for choose default
		0                            // Flags, 0 for leave everything as default
	);
	if (!renderer) {
		fprintf(stderr, "Error Creating SDL Renderer.\n");
		return false;
	}
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	
	return true;
}

void render_color_buffer(void) {
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)(window_width * sizeof(uint32_t))
	);
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
	for (int y = 0; y < window_height; y++) {
		for (int x = 0; x < window_width; x++) {
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

void draw_grid(void) {
	for (int y = 0; y < window_height; y += 10) {
		for (int x = 0; x < window_width; x += 10) {
			color_buffer[(window_width * y) + x] = 0xFF1e1e1e;
		}
	}
}

void draw_pixel(int x, int y, uint32_t color) {
	if (x < window_width && y < window_height)
		color_buffer[(window_width * y) + x] = color;
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int current_x = x + i;
			int current_y = y + j;
			color_buffer[(window_width * current_y) + current_x] = color;
		}
	}
}

void destroy_window(void) {
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

