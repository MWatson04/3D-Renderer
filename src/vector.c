#include <math.h>
#include "vector.h"

void vec3_rotate_x(vec3_t* v, float angle) {
	v = {
		.x = x,
		.y = y * cos(angle) - z * sin(angle),
		.z = y * sin(angle) + z * cos(angle)
	};
}

void vec3_rotate_y(vec3_t* v, float angle) {
	v = {
		.x = x * cos(angle) - z * sin(angle),
		.y = y,
		.z = x * sin(angle) + z * cos(angle)
	};
}

void vec3_rotate_z(vec3_t* v, float angle) {
	v = {
		.x = x * cos(angle) - y * sin(angle),
		.y = x * sin(angle) + y * cos(angle),
		.z = z
	};
}

