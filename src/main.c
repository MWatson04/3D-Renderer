#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

bool is_running = false;

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
	// Create SDL Window	
	window = SDL_CreateWindow(
		NULL,                        // Window Title, NULL for no name
		SDL_WINDOWPOS_CENTERED,      // Where the window will show up on monitor displayed
		SDL_WINDOWPOS_CENTERED,      // WINDOWPOS_CENTERED for center of monitor
		window_width,                // Window Width
		window_height,               // Window Height
		SDL_WINDOW_BORDERLESS        // Any flags for display window, Borderless in this case
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
	
	return true;
}

void setup(void) {
	// Allocate memory to hold color buffer
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
	if (!color_buffer) {
		fprintf(stderr, "Memory allocation for color buffer failed.\n");
	}

	// Create SDL Texture to display color buffer
	color_buffer_texture = SDL_CreateTexture (
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);
	if (!color_buffer_texture) {
		fprintf(stderr, "Error Creating Color Buffer Texture.\n");
	}
}

void process_input(void) {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) // keysym & sym = symbol
				is_running = false;
			break;
	}
}

void update(void) {
	// TODO
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

void render(void) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);  // Put render color onto display window over everything that has been rendered

	render_color_buffer();	
	clear_color_buffer(0xFFFFFF00);
	
	SDL_RenderPresent(renderer);
}

void destroy_window(void) {
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(void) {
	is_running = initialize_window();

	setup();

	while (is_running) {
		process_input();
		update();
		render();
	}

	destroy_window();

	return 0;
}
