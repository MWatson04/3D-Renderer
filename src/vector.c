#include <math.h>
#include "vector.h"

// Vector 2D functions
float vec2_length(vec2_t v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

vec2_t vec2_add(vec2_t a, vec2_t b) {
	vec2_t result = {
		.x = a.x + b.x,
		.y = a.y + b.y
	};
	return result;
}

vec2_t vec2_sub(vec2_t a, vec2_t b) {
	vec2_t result = {
		.x = a.x - b.x,
		.y = a.y - b.y
	};
	return result;
}

vec2_t vec2_mul(vec2_t v, float factor) {
	vec2_t result = {
		.x = v.x * factor,
		.y = v.y * factor
	};
	return result;
}

vec2_t vec2_div(vec2_t v, float factor) {
	vec2_t result = {
		.x = v.x / factor,
		.y = v.y / factor
	};
	return result;
}

// Vector 3D functions
float vec3_length(vec3_t v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3_t vec3_add(vec3_t a, vec3_t b) {
	vec3_t result = {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	};
	return result;
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
	vec3_t result = {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	};
	return result;
}

vec3_t vec3_mul(vec3_t v, float factor) {
	vec3_t result = {
		.x = v.x * factor,
		.y = v.y * factor,
		.z = v.z * factor
	};
	return result;
}

vec3_t vec3_div(vec3_t v, float factor) {
	vec3_t result = {
		.x = v.x / factor,
		.y = v.y / factor,
		.z = v.z / factor
	};
	return result;
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
	vec3_t result = {
		.x = a.y * b.z - a.z * b.y,
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x
	};
	return result;
}

void vec3_rotate_x(vec3_t* v, float angle) {
	float y = v->y;
	float z = v->z;
	v->x = v->x;
	v->y = y * cos(angle) - z * sin(angle);
	v->z = y * sin(angle) + z * cos(angle);
}

void vec3_rotate_y(vec3_t* v, float angle) {
	float x = v->x;
	float z = v->z;
	v->x = x * cos(angle) - z * sin(angle);
	v->y = v->y;
	v->z = x * sin(angle) + z * cos(angle);
}

void vec3_rotate_z(vec3_t* v, float angle) {
	float x = v->x;
	float y = v->y;
	v->x = x * cos(angle) - y * sin(angle);
	v->y = x * sin(angle) + y * cos(angle);
 	v->z = v->z;
}
