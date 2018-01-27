#include "captcha.h"

double get_density(int height, int width, int pixels[height][width]) {
	double density = 0;
	int x = 0, y = 0;

	for (y = 0; y < height; y ++) {
		for (x = 0; x < width; x ++) {
			if (pixels[y][x] == 1) {
				density ++;
			}
		}
	}
	density = density / (width * height);
	
	return density;
}