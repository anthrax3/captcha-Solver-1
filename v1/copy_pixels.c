#include "captcha.h"

void copy_pixels(int height, int width, int pixels[height][width],
                 int start_row, int start_column, int copy_height, int copy_width,
                 int copy[copy_height][copy_width]) {
	int x = 0, y = 0, i = 0, j = 0;
	for (y = start_row; y < start_row + copy_height; y ++) {
		i = 0;
		for (x = start_column; x < start_column + copy_width; x ++){
			copy[j][i] = pixels[y][x];
			i ++;
		}
		j ++;
	}
}