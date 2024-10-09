#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x, y;
} vec2_t;

typedef struct {
    float x, y, z;
} vec3_t;

// Vector 2D functions
float vec2_length(vec2_t v);
vec2_t vec2_add(vec2_t a, vec2_t b);            // ADDITION
vec2_t vec2_sub(vec2_t a, vec2_t b);            // SUBTRACTION
vec2_t vec2_mul(vec2_t v, float factor);        // MULTIPLICATION
vec2_t vec2_div(vec2_t v, float factor);        // DIVISION
float vec2_dot(vec2_t a, vec2_t b);             // DOT PRODUCT

// Vector 3D functions
float vec3_length(vec3_t v);
vec3_t vec3_add(vec3_t a, vec3_t b);            // ADDITION
vec3_t vec3_sub(vec3_t a, vec3_t b);            // SUBTRACTION
vec3_t vec3_mul(vec3_t v, float factor);        // MULTIPLICATION
vec3_t vec3_div(vec3_t v, float factor);        // DIVISION
vec3_t vec3_cross(vec3_t a, vec3_t b);          // CROSS PRODUCT
float vec3_dot(vec3_t a, vec3_t b);             // DOT PRODUCT

void vec3_rotate_x(vec3_t* v, float angle);
void vec3_rotate_y(vec3_t* v, float angle);
void vec3_rotate_z(vec3_t* v, float angle);

#endif
