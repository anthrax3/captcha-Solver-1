#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	FILE *fp = fopen ("n_if_conditions.doc", "a");

	for (int i = 0; i < 10; i ++) {
		fprintf (fp, " else if (((horizontalBalance >= (MEAN_%d_HORIZONTAL_BALANCE - N_SD * SD_%d_HORIZONTAL_BALANCE)) && (horizontalBalance <= (MEAN_%d_HORIZONTAL_BALANCE + N_SD * SD_%d_HORIZONTAL_BALANCE))) && \n((verticalBalance >= (MEAN_%d_VERTICAL_BALANCE - N_SD * SD_%d_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_%d_VERTICAL_BALANCE + N_SD * SD_%d_VERTICAL_BALANCE))) && \n((tallness >= (MEAN_%d_TALLNESS - N_SD * SD_%d_TALLNESS)) && (tallness <= (MEAN_%d_TALLNESS + N_SD * SD_%d_TALLNESS))) && \n((density >= (MEAN_%d_DENSITY - N_SD * SD_%d_DENSITY)) && (density <= (MEAN_%d_DENSITY + N_SD * SD_%d_DENSITY))) && \n", i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, i);
		for (int y = 0; y < 5; y ++) {
			for (int x = 0; x < 3; x ++) {
				fprintf (fp, "((segmentDensity[%d][%d] >= (MEAN_%d_SEGMENT_DENSITY_%d_%d - N_SD * SD_%d_SEGMENT_DENSITY_%d_%d)) && (segmentDensity[%d][%d] <= (MEAN_%d_SEGMENT_DENSITY_%d_%d + N_SD * SD_%d_SEGMENT_DENSITY_%d_%d))) &&\n", y, x, i, y, x, i, y, x, y, x, i, y, x, i, y, x);
			}
		}
		// for (int y = 0; y < 3; y ++) {
		// 	for (int x = 0; x < 3; x ++) {
		// 		if (y == 2 && x == 2) {
		// 			fprintf (fp, "((yIncrements[%d][%d] >= (MEAN_%d_Y_INCREMENT_%d_%d - N_SD * SD_%d_Y_INCREMENT_%d_%d)) && (yIncrements[%d][%d] <= (MEAN_%d_Y_INCREMENT_%d_%d + N_SD * SD_%d_Y_INCREMENT_%d_%d))) && \n((xIncrements[%d][%d] >= (MEAN_%d_X_INCREMENT_%d_%d - N_SD * SD_%d_X_INCREMENT_%d_%d)) && (xIncrements[%d][%d] <= (MEAN_%d_X_INCREMENT_%d_%d + N_SD * SD_%d_X_INCREMENT_%d_%d)))", y, x, i, y, x, i, y, x, y, x, i, y, x, i, y, x, y, x, i, y, x, i, y, x, y, x, i, y, x, i, y, x);
		// 		} else {
		// 			fprintf (fp, "((yIncrements[%d][%d] >= (MEAN_%d_Y_INCREMENT_%d_%d - N_SD * SD_%d_Y_INCREMENT_%d_%d)) && (yIncrements[%d][%d] <= (MEAN_%d_Y_INCREMENT_%d_%d + N_SD * SD_%d_Y_INCREMENT_%d_%d))) && \n((xIncrements[%d][%d] >= (MEAN_%d_X_INCREMENT_%d_%d - N_SD * SD_%d_X_INCREMENT_%d_%d)) && (xIncrements[%d][%d] <= (MEAN_%d_X_INCREMENT_%d_%d + N_SD * SD_%d_X_INCREMENT_%d_%d))) &&\n", y, x, i, y, x, i, y, x, y, x, i, y, x, i, y, x, y, x, i, y, x, i, y, x, y, x, i, y, x, i, y, x);
		// 		}
		// 	}
		// }
		fprintf (fp, ") {\n printf ("");\n} ");
	}


	return EXIT_SUCCESS;
}
