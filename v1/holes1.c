#include "captcha.h"

double get_y_increments(int height, int width, int pixels[height][width], int *yTicker, int *xTicker) {
	int x = 0, y = 0;
	int ySegmentStart[Y_INCREMENT_SEGMENTS] = {0}, ySegmentEnd[Y_INCREMENT_SEGMENTS] = {0}, ySegmentSize = 0;
	int xSegmentStart[X_INCREMENT_SEGMENTS] = {0}, xSegmentEnd[X_INCREMENT_SEGMENTS] = {0}, xSegmentSize = 0;
	int yLines[Y_INCREMENT_SEGMENTS][X_INCREMENT_SEGMENTS] = {0};
	double averageYLines[Y_INCREMENT_SEGMENTS][X_INCREMENT_SEGMENTS] = {0};

	ySegmentSize = height / Y_INCREMENT_SEGMENTS;
	xSegmentSize = width / X_INCREMENT_SEGMENTS;

	for (int i = 0; i < Y_INCREMENT_SEGMENTS; i ++) {
		if (i == Y_INCREMENT_SEGMENTS - 1) {
			ySegmentStart[i] = i * ySegmentSize;
			ySegmentEnd[i] = height;
		} else {
			ySegmentStart[i] = i * ySegmentSize;
			ySegmentEnd[i] = (i + 1) * ySegmentSize;
		}
	}
	for (int j = 0; j < X_INCREMENT_SEGMENTS; j ++) {
		if (j == X_INCREMENT_SEGMENTS - 1) {
			xSegmentStart[j] = j * xSegmentSize;
			xSegmentEnd[j] = width;
		} else {
			xSegmentStart[j] = j * xSegmentSize;
			xSegmentEnd[j] = (j + 1) * xSegmentSize;
		}
	}
	for (int i = 0; i < Y_INCREMENT_SEGMENTS; i ++) {
		for (y = ySegmentStart[i]; y < ySegmentEnd[i]; y ++) {
			for (int j = 0; j < X_INCREMENT_SEGMENTS; j ++) {
				for (x = xSegmentStart[j]; x < xSegmentEnd[j]; x ++) {
					if (pixels[y][0] == 1 && x == 0) {
						yLines[i][j] ++;
					} else if (pixels[y][x] == 1 && pixels[y][x - 1] == 0) {
						yLines[i][j] ++;
					}
				}
			}		
		}
	}
	for (int i = 0; i < Y_INCREMENT_SEGMENTS; i ++) {
		for (int j = 0; j < X_INCREMENT_SEGMENTS; j ++) {
			averageYLines[i][j] = yLines[i][j];
			averageYLines[i][j] /= ySegmentSize;
			// printf ("yLines[%d][%d] = %d\n", i, j, yLines[i][j]);
			// printf ("averageYLines[%d][%d] = %lf\n", i, j, averageYLines[i][j]);
		}
	}

	return averageYLines[*yTicker][*xTicker];
}

double get_x_increments(int height, int width, int pixels[height][width], int *yTicker, int *xTicker) {
	int x = 0, y = 0;
	int ySegmentStart[Y_INCREMENT_SEGMENTS] = {0}, ySegmentEnd[Y_INCREMENT_SEGMENTS] = {0}, ySegmentSize = 0;
	int xSegmentStart[X_INCREMENT_SEGMENTS] = {0}, xSegmentEnd[X_INCREMENT_SEGMENTS] = {0}, xSegmentSize = 0;
	int xLines[Y_INCREMENT_SEGMENTS][X_INCREMENT_SEGMENTS] = {0};
	double averageXLines[Y_INCREMENT_SEGMENTS][X_INCREMENT_SEGMENTS] = {0};

	ySegmentSize = height / 3;
	xSegmentSize = width / 3;

	for (int i = 0; i < Y_INCREMENT_SEGMENTS; i ++) {
		if (i == Y_INCREMENT_SEGMENTS - 1) {
			ySegmentStart[i] = i * ySegmentSize;
			ySegmentEnd[i] = height;
		} else {
			ySegmentStart[i] = i * ySegmentSize;
			ySegmentEnd[i] = (i + 1) * ySegmentSize;
		}
	}
	for (int j = 0; j < X_INCREMENT_SEGMENTS; j ++) {
		if (j == X_INCREMENT_SEGMENTS - 1) {
			xSegmentStart[j] = j * xSegmentSize;
			xSegmentEnd[j] = width;
		} else {
			xSegmentStart[j] = j * xSegmentSize;
			xSegmentEnd[j] = (j + 1) * xSegmentSize;
		}
	}
	for (int i = 0; i < X_INCREMENT_SEGMENTS; i ++) {
		for (x = xSegmentStart[i]; x < xSegmentEnd[i]; x ++) {
			for (int j = 0; j < Y_INCREMENT_SEGMENTS; j ++) {
				for (y = ySegmentStart[j]; y < ySegmentEnd[j]; y ++) {
					if (pixels[0][x] == 1 && y == 0) {
						xLines[i][j] ++;
					} else if (pixels[y][x] == 1 && pixels[y - 1][x] == 0) {
						xLines[i][j] ++;
					}
				}
			}		
		}
	}
	for (int i = 0; i < Y_INCREMENT_SEGMENTS; i ++) {
		for (int j = 0; j < X_INCREMENT_SEGMENTS; j ++) {
			averageXLines[i][j] = xLines[i][j];
			averageXLines[i][j] /= xSegmentSize;
			// printf ("xLines[%d][%d] = %d\n", i, j, xLines[i][j]);
			// printf ("averageXLines[%d][%d] = %lf\n", i, j, averageXLines[i][j]);
		}
	}

	return averageXLines[*yTicker][*xTicker];
}