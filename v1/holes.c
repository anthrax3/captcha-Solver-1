// Flood fill
#include "captcha.h"

void flood_fill (int x, int y, int height, int width, int pixels[height][width]) {

	if (x >= 0 && x < width && y >= 0 && y < height && pixels[y][x] == 0) {
		// printf ("in the flood_fill if\n");
		pixels[y][x] = 1;
		flood_fill (x, y + 1, height, width, pixels);
		flood_fill (x + 1, y + 1, height, width, pixels);
		flood_fill (x + 1, y, height, width, pixels);
		flood_fill (x + 1, y - 1, height, width, pixels);
		flood_fill (x, y - 1, height, width, pixels);
		flood_fill (x - 1, y - 1, height, width, pixels);
		flood_fill (x - 1, y, height, width, pixels);
		flood_fill (x - 1, y + 1, height, width, pixels);
	} 

	// printf ("y = %d, x = %d\n", *y, *x);
}

int get_holes (int height, int width, int pixels[height][width]) {
	int holes = -1, y = 0, x = 0;
	int floodPixels[height][width];
	for (y = 0; y < height; y ++) {
		for (x = 0; x < width; x ++) {
			floodPixels[y][x] = pixels[y][x];
		}
	}
	
	for (y = 0; y < height; y ++) {
		for (x = 0; x < width; x ++) {
			if (floodPixels[y][x] == 0) {
				flood_fill (x, y, height, width, floodPixels);
				holes ++;
			}
		}
	}
	//print_image (height, width, floodPixels);
	
	return holes;
}

