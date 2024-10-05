#include <math.h>
#include "vector.h"

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
