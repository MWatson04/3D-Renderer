#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "array.h"
#include "display.h"
#include "vector.h"
#include "mesh.h"

triangle_t* triangles_to_render = NULL;

vec3_t camera_position = { 0, 0, 0 };

float fov_factor = 640;

bool is_running = false;
int previous_frame_time = 0;

void setup(void) {
    // Allocate the required memory in bytes to hold the color buffer
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
	if (!color_buffer) {
		fprintf(stderr, "Memory allocation for color buffer failed.\n");
	}
	
    // Creating a SDL texture that is used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

    // Load cube values into mesh data structure
    // load_cube_mesh_data();
    load_obj_file_data("./assets/cube.obj");
    if (!mesh.vertices || !mesh.faces) {
        fprintf(stderr, "Error Loading Mesh Data\n");
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
            if (event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;
            break;
    }
}

// Receive 3D vector and convert to 2D
vec2_t project(vec3_t point) {
    vec2_t projected_point = {
        .x = (fov_factor * point.x) / point.z,  // Divide by point.z to properly determine the depth of each pixel
        .y = (fov_factor * point.y) / point.z   // As z gets bigger, the closer a pixel is placed to center of cube
    }; 
    return projected_point;
}

void update(void) {
    // Get the time to wait until FRAME_TARGET_TIME is met (in milliseconds)
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    // Delay execution if FRAME_TARGET_TIME has not been met
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    previous_frame_time = SDL_GetTicks();

    // Initialize array of triangles to render
    triangles_to_render = NULL;

    mesh.rotation.x += 0.01;
    mesh.rotation.y += 0.01;
    mesh.rotation.z += 0.01;

    // Loop all triangle faces of our mesh
    int num_faces = array_length(mesh.faces);
    for (int i = 0; i < num_faces; i++) {
        face_t mesh_face = mesh.faces[i];

        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.c - 1];

        triangle_t projected_triangle;

        vec3_t transformed_vertices[3];

        // Vertex transformations
        for (int j = 0; j < 3; j++) {
            vec3_t transformed_vertex = face_vertices[j];

            vec3_rotate_x(&transformed_vertex, mesh.rotation.x);
            vec3_rotate_y(&transformed_vertex, mesh.rotation.y);
            vec3_rotate_z(&transformed_vertex, mesh.rotation.z);

            // Translate the vertex away from the camera
            transformed_vertex.z += 5;

            transformed_vertices[j] = transformed_vertex;
        }

        // Backface culling
        vec3_t vec_a = transformed_vertices[0];
        vec3_t vec_b = transformed_vertices[1];
        vec3_t vec_c = transformed_vertices[2];

        // Vectors B-A and C-A
        vec3_t vec_ba = vec3_sub(vec_b, vec_a);
        vec3_t vec_ca = vec3_sub(vec_c, vec_a);

        // Get face normal
        vec3_t normal = vec3_cross(vec_ba, vec_ca);

        // Find camera ray
        vec3_t camera_ray = vec3_sub(camera_position, vec_a);

        // Find dot product of normal and camera_ray (check alignment of camera_ray and normal)
        float alignment = vec3_dot(normal, camera_ray);

        // Skip loop iteration if the normal/camera_ray are facing opposite directions
        if (alignment < 0) {
            continue;
        }

        // Vertex projection
        for (int j = 0; j < 3; j++) {
            // Project the current vertex
            vec2_t projected_vertex = project(transformed_vertices[j]);

            // Scale and translate the projected points to the middle of the screen
            projected_vertex.x += (window_width / 2);
            projected_vertex.y += (window_height / 2);

            projected_triangle.points[j] = projected_vertex;
        }

        // Save the projected triangle in the array of triangles to render
        array_push(triangles_to_render, projected_triangle);
    }
}

void render(void) {
    draw_grid();
  
    // Loop all projected triangles and render them
    int num_triangles = array_length(triangles_to_render);
    for (int i = 0; i < num_triangles; i++) {
        triangle_t current_triangle = triangles_to_render[i];

        // Draw vertices
        draw_rect(current_triangle.points[0].x, current_triangle.points[0].y, 3, 3, 0xFFFFFF00);
        draw_rect(current_triangle.points[1].x, current_triangle.points[1].y, 3, 3, 0xFFFFFF00);
        draw_rect(current_triangle.points[2].x, current_triangle.points[2].y, 3, 3, 0xFFFFFF00);

        // Draw unfilled triangle
        draw_triangle(
            current_triangle.points[0].x,
            current_triangle.points[0].y,
            current_triangle.points[1].x,
            current_triangle.points[1].y,
            current_triangle.points[2].x,
            current_triangle.points[2].y
        );
    }

    // Clear array of triangles
    array_free(triangles_to_render);

    render_color_buffer();
    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

// Remove dynamically allocated resources
void free_resources(void) {
    free(color_buffer);
    array_free(mesh.faces);
    array_free(mesh.vertices);
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
    free_resources();

    return 0;
}
