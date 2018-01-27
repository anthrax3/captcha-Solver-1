#include "captcha.h"

double get_vertical_balance(int height, int width, int pixels[height][width]) {
	double verticalBalance = 0, rowSum = 0, nBlackPixels = 0;
	int x = 0, y = 0;
	
	for (y = 0; y < height; y ++) {
		for (x = 0; x < width; x ++) {
			if (pixels[y][x] == 1) {
				nBlackPixels ++;
				rowSum += y;
			}
		}
	}
	verticalBalance = (rowSum/nBlackPixels + 0.5)/height;

	return verticalBalance;
}