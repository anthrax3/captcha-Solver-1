#include "captcha.h"

void print_image(int height, int width, int pixels[height][width]) {
	int x = 0, y = 0;

	for (y = height - 1; y >= 0; y --) {
		for (x = 0; x < width; x ++) {
			if (pixels[y][x] == 0) {
				printf (".");
			} else if (pixels[y][x] == 1) {
				printf ("*");
			}
		}
		printf ("\n");
	}
}