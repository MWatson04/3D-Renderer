#include <stdint.h>
#include "triangle.h"
#include "display.h"

void int_swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // Calculates change in x per change in y (inverse) since the step in y is always 1
    // dx / dy
    float inv_slope_1 = (float)(x1 - x0) / (y1 - y0);
    float inv_slope_2 = (float)(x2 - x0) / (y2 - y0);

    float x_start = x0;
    float x_end = x0;

    // Loop scanlines from top to bottom
    for (int y = y0; y <= y2; y++) {
        draw_line(x_start, y, x_end, y, color);
        x_start += inv_slope_1;
        x_end += inv_slope_2;
    }
}

void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    float inv_slope_1 = (float)(x2 - x0) / (y2 - y0);
    float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

    float x_start = x2;
    float x_end = x2;

    // Loop scanlines from bottom to top
    for (int y = y2; y >= y1; y--) {
        draw_line(x_start, y, x_end, y, color);
        x_start -= inv_slope_1;
        x_end -= inv_slope_2;
    }
}

void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    if (y0 > y1) {
        int_swap(&y0, &y1);
        int_swap(&x0, &x1);
    }
    if (y1 > y2) {
        int_swap(&y1, &y2);
        int_swap(&x1, &x2);
    }
    if (y0 > y1) {
        int_swap(&y0, &y1);
        int_swap(&x0, &x1);
    }

	/*
	 * if (y1 == y2) is a case where entire triangle can be considered a flat bottom triangle 
	 * if (y0 == y1) is a case where entire triangle can be considered a flat top triangle
	 * if (y1 != y2 && y0 != y1) is a case where entire triangle has a flat top and a flat bottom 
	 */
	if (y1 == y2) {     
		fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
	} else if (y0 == y1) {  
		fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
	} else {   
		// Calculate new midpoint vertex
    	int my = y1;
    	int mx = ( (float)((x2 - x0) * (y1-y0)) / (float)(y2-y0) ) + x0;

    	fill_flat_bottom_triangle(x0, y0, x1, y1, mx, my, color);
    	fill_flat_top_triangle(x1, y1, mx, my, x2, y2, color);	
	}
}
