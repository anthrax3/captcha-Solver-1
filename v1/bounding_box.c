#include "captcha.h"
#define MAX_CHARACTERS 4096

void get_bounding_box(int height, int width, int pixels[height][width],
                  int *start_row, int *start_column, int *box_height, int *box_width) {
	int x = 0, y = 0, xCheck[MAX_CHARACTERS] = {0}, yCheck[MAX_CHARACTERS] = {0}, startRowTick = 0, heightTick = 0, startColumnTick = 0, widthTick = 0;
	// remember to always set the size of the array
	for (y = 0; y < height; y ++) {
		for (x = 0; x < width; x ++) {
			if (pixels[y][x] == 1) {
				xCheck[x] = 1;
				yCheck[y] = 1;
			}
		}
	}
	for (y = 0; y < height; y ++) {
		if (yCheck[0] == 1 && y == 0) {
			*start_row = y;
		} else if (yCheck[y] == 1 && yCheck[y - 1] == 0) {
			*start_row = y;
		} else if (yCheck[height - 1] == 1 && y == height - 1) {
			*box_height = y - *start_row + 1;
		} else if (yCheck[y + 1] == 0 && yCheck[y] == 1) {
			*box_height = y - *start_row + 1;
		}
	}
	for (x = 0; x < width; x ++) {
		if (xCheck[0] == 1 && x == 0) {
			*start_column = x;
		} else if (xCheck[x] == 1 && xCheck[x - 1] == 0) {
			*start_column = x;
		} else if (xCheck[width - 1] == 1 && x == width - 1) {
			*box_width = x - *start_column + 1;
		} else if (xCheck[x + 1] == 0 && xCheck[x] == 1) {
			*box_width = x - *start_column + 1;
		}
	}
}