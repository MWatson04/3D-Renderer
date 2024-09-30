#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "display.h"

bool is_running = false;

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

void render(void) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);  // Put render color onto display window over everything that has been rendered

	draw_rect(200, 200, 200, 100, 0xFFFF00FF);

	render_color_buffer();	
	clear_color_buffer(0xFF000000);
	
	SDL_RenderPresent(renderer);
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
