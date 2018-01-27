#include "captcha.h"

double get_horizontal_balance(int height, int width, int pixels[height][width]) {
	double horizontalBalance = 0, columnSum = 0, nBlackPixels = 0;
	int x = 0, y = 0;
	
	for (x = 0; x < width; x ++) {
		for (y = 0; y < height; y ++) {
			if (pixels[y][x] == 1) {
				nBlackPixels ++;
				columnSum += x;
			}
		}
	}
	horizontalBalance = (columnSum/nBlackPixels + 0.5)/width;

	return horizontalBalance;
}