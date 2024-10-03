#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

// Declare array of vectors/points
#define N_POINTS (9 * 9 * 9) 
vec3_t cube_points[N_POINTS]; // 9x9x9 cube
vec2_t projected_points[N_POINTS];

vec3_t camera_position = { 0, 0, -5 };
vec3_t cube_rotation = { 0, 0, 0 };

float fov_factor = 640.0;

bool is_running = false;
int previous_frame_time = 0;

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

	// Start loading array of vectors
	// From -1 to 1 in 9x9x9 cube
	int point_count = 0;

	for (float x = -1; x <= 1; x += 0.25) {
		for (float y = -1; y <= 1; y += 0.25) {
			for (float z = -1; z <= 1; z += 0.25) {
				vec3_t new_point = { .x = x, .y = y, .z = z };
				cube_points[point_count++] = new_point;
			}
		}
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

// Takes 3D vector and returns projected 2D point
vec2_t project(vec3_t point) {
	vec2_t projected_point = {
		.x = (fov_factor * point.x) / point.z, // Divide by point.z to properly determine the depth of each pixel
		.y = (fov_factor * point.y) / point.z  // As z gets smaller, the closer a pixel is placed to the center of the cube
	};
	return projected_point;
}

void update(void) {
	// Lock the execution of this function into this while loop if the current SDL 
	// tick time doesn't equal how much time I want to pass (FRAME_TARGET_TIME)
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), previous_frame_time + FRAME_TARGET_TIME));
	previous_frame_time = SDL_GetTicks();

	float rotation_speed = 0.01;
	cube_rotation.x += rotation_speed;
	cube_rotation.y += rotation_speed;
	cube_rotation.z += rotation_speed;

	for (int i = 0; i < N_POINTS; i++) {
		vec3_t point = cube_points[i];
		vec3_rotate_x(&point, cube_rotation.x);
		vec3_rotate_y(&point, cube_rotation.y);
		vec3_rotate_z(&point, cube_rotation.z);
		
		// Translate points away from camera	
		point.z -= camera_position.z;

		// Convert 3D vector to 2D and store it in 2D array
		vec2_t projected_point = project(point);
		projected_points[i] = projected_point;
	}
}

void render(void) {
	draw_grid();

	for (int i = 0; i < N_POINTS; i++) {
		vec2_t projected_point = projected_points[i];
		draw_rect(
			projected_point.x + (window_width / 2),
			projected_point.y + (window_height / 2),
			4,
			4,
			0xFFFFFF00
		);
	}

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
