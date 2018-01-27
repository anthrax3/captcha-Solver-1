#include "captcha.h"

double get_segment_density(int height, int width, int pixels[height][width], int *yTicker, int *xTicker) {
	int x = 0, y = 0;
	int ySegmentStart[Y_DENSITY_SEGMENTS] = {0}, ySegmentEnd[Y_DENSITY_SEGMENTS] = {0}, ySegmentSize = 0;
	int xSegmentStart[X_DENSITY_SEGMENTS] = {0}, xSegmentEnd[X_DENSITY_SEGMENTS] = {0}, xSegmentSize = 0;
	double segmentDensity[Y_DENSITY_SEGMENTS][X_DENSITY_SEGMENTS] = {0};

	ySegmentSize = height / Y_DENSITY_SEGMENTS;
	xSegmentSize = width / X_DENSITY_SEGMENTS;
	// printf ("height = %d\n", height);
	// printf ("width = %d\n", width);

	for (int i = 0; i < Y_DENSITY_SEGMENTS; i ++) {
		if (i == Y_DENSITY_SEGMENTS - 1) {
			ySegmentStart[i] = i * ySegmentSize;
			ySegmentEnd[i] = height;
		} else {
			ySegmentStart[i] = i * ySegmentSize;
			ySegmentEnd[i] = (i + 1) * ySegmentSize;
		}
	}
	for (int j = 0; j < X_DENSITY_SEGMENTS; j ++) {
		if (j == X_DENSITY_SEGMENTS - 1) {
			xSegmentStart[j] = j * xSegmentSize;
			xSegmentEnd[j] = width;
		} else {
			xSegmentStart[j] = j * xSegmentSize;
			xSegmentEnd[j] = (j + 1) * xSegmentSize;
		}
	}

	for (int i = 0; i < Y_DENSITY_SEGMENTS; i ++) {
		for (y = ySegmentStart[i]; y < ySegmentEnd[i]; y ++) {
			for (int j = 0; j < X_DENSITY_SEGMENTS; j ++) {
				for (x = xSegmentStart[j]; x < xSegmentEnd[j]; x ++) {
					if (pixels[y][x] == 1) {
						segmentDensity[i][j] ++;
					}
				}
			}		
		}
	}
	for (int i = 0; i < Y_DENSITY_SEGMENTS; i ++) {
		for (int j = 0; j < X_DENSITY_SEGMENTS; j ++) {
			// printf ("segmentDensity[%d][%d](before) = %lf\n", i, j, segmentDensity[i][j]);
			segmentDensity[i][j] /= ((ySegmentEnd[i] - ySegmentStart[i]) * (xSegmentEnd[j] - xSegmentStart[j]));
			// printf ("ySegmentEnd[%d](%d) - ySegmentStart[%d](%d) = %d\n", i, ySegmentEnd[i], i, ySegmentStart[i], ySegmentEnd[i] - ySegmentStart[i]);
			// printf ("xSegmentEnd[%d](%d) - xSegmentStart[%d](%d) = %d\n", j, xSegmentEnd[j], j, xSegmentStart[j], xSegmentEnd[j] - xSegmentStart[j]);
			// printf ("segmentDensity[%d][%d](after) = %lf\n", i, j, segmentDensity[i][j]);
		}
	}

	return segmentDensity[*yTicker][*xTicker];
}