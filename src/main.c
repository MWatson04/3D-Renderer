#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

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
		800,                         // Window Width
		600,                         // Window Height
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
	// TODO
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

	//...
	
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

	return 0;
}
