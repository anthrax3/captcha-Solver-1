#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "captcha.h"
#include "metric_statistics_definitions.h"

int main (int argc, char *argv[]) {
    int height, width, start_row, start_column, box_width, box_height, i, j;
    double horizontalBalance = 0;
    double verticalBalance = 0;
    double tallness = 0;
    double density = 0;
    double segmentDensity[Y_DENSITY_SEGMENTS][X_DENSITY_SEGMENTS] = {0};
    double yIncrements[Y_INCREMENT_SEGMENTS][X_INCREMENT_SEGMENTS] = {0};
    double xIncrements[Y_INCREMENT_SEGMENTS][X_INCREMENT_SEGMENTS] = {0};

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }
    if (get_pbm_dimensions (argv[1], &height, &width) != 1) {
        return 1;
    }
    int pixels[height][width];

    if (read_pbm(argv[1], height, width, pixels)) {
        get_bounding_box (height, width, pixels, &start_row, &start_column, &box_height, &box_width);
        int box_pixels[box_height][box_width];
        copy_pixels (height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

        horizontalBalance = get_horizontal_balance (box_height, box_width, box_pixels);
        verticalBalance = get_vertical_balance (box_height, box_width, box_pixels);
        density = get_density (box_height, box_width, box_pixels);
        tallness = get_tallness (box_height, box_width);
        // printf ("horizontalBalance = %lf\n", horizontalBalance);
        // printf ("verticalBalance = %lf\n", verticalBalance);
        // printf ("density = %lf\n", density);
        // printf ("tallness = %lf\n", tallness);
        for (int yTicker = 0; yTicker < Y_DENSITY_SEGMENTS; yTicker ++) {
            for (int xTicker = 0; xTicker < X_DENSITY_SEGMENTS; xTicker ++) {
                segmentDensity[yTicker][xTicker] =  get_segment_density (box_height, box_width, box_pixels, &yTicker, &xTicker);
                // printf ("segmentDensity[%d][%d] = %lf\n", yTicker, xTicker, segmentDensity[yTicker][xTicker]);
            }
        }
        for (int yTicker = 0; yTicker < Y_INCREMENT_SEGMENTS; yTicker ++) {
            for (int xTicker = 0; xTicker < X_INCREMENT_SEGMENTS; xTicker ++) {
                yIncrements[yTicker][xTicker] = get_y_increments (box_height, box_width, box_pixels, &yTicker, &xTicker);
                xIncrements[yTicker][xTicker] = get_x_increments (box_height, box_width, box_pixels, &yTicker, &xTicker);
                // printf ("yIncrements[%d][%d] = %lf\n", yTicker, xTicker, yIncrements[yTicker][xTicker]);
                // printf ("xIncrements[%d][%d] = %lf\n", yTicker, xTicker, xIncrements[yTicker][xTicker]);
            }
        }
    }

    if (((horizontalBalance >= (MEAN_0_HORIZONTAL_BALANCE - N_SD * SD_0_HORIZONTAL_BALANCE)) && (horizontalBalance <= (MEAN_0_HORIZONTAL_BALANCE + N_SD * SD_0_HORIZONTAL_BALANCE))) && 
    ((verticalBalance >= (MEAN_0_VERTICAL_BALANCE - N_SD * SD_0_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_0_VERTICAL_BALANCE + N_SD * SD_0_VERTICAL_BALANCE))) && 
    ((tallness >= (MEAN_0_TALLNESS - N_SD * SD_0_TALLNESS)) && (tallness <= (MEAN_0_TALLNESS + N_SD * SD_0_TALLNESS))) && 
    ((density >= (MEAN_0_VERTICAL_BALANCE - N_SD * SD_0_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_0_VERTICAL_BALANCE + N_SD * SD_0_VERTICAL_BALANCE))) && 
    ((segmentDensity[0][0] >= (MEAN_0_SEGMENT_DENSITY_0_0 - N_SD * SD_0_SEGMENT_DENSITY_0_0)) && (segmentDensity[0][0] <= (MEAN_0_SEGMENT_DENSITY_0_0 + N_SD * SD_0_SEGMENT_DENSITY_0_0))) &&
    ((segmentDensity[0][1] >= (MEAN_0_SEGMENT_DENSITY_0_1 - N_SD * SD_0_SEGMENT_DENSITY_0_1)) && (segmentDensity[0][1] <= (MEAN_0_SEGMENT_DENSITY_0_1 + N_SD * SD_0_SEGMENT_DENSITY_0_1))) &&
    ((segmentDensity[0][2] >= (MEAN_0_SEGMENT_DENSITY_0_2 - N_SD * SD_0_SEGMENT_DENSITY_0_2)) && (segmentDensity[0][2] <= (MEAN_0_SEGMENT_DENSITY_0_2 + N_SD * SD_0_SEGMENT_DENSITY_0_2))) &&
    ((segmentDensity[1][0] >= (MEAN_0_SEGMENT_DENSITY_1_0 - N_SD * SD_0_SEGMENT_DENSITY_1_0)) && (segmentDensity[1][0] <= (MEAN_0_SEGMENT_DENSITY_1_0 + N_SD * SD_0_SEGMENT_DENSITY_1_0))) &&
    ((segmentDensity[1][1] >= (MEAN_0_SEGMENT_DENSITY_1_1 - N_SD * SD_0_SEGMENT_DENSITY_1_1)) && (segmentDensity[1][1] <= (MEAN_0_SEGMENT_DENSITY_1_1 + N_SD * SD_0_SEGMENT_DENSITY_1_1))) &&
    ((segmentDensity[1][2] >= (MEAN_0_SEGMENT_DENSITY_1_2 - N_SD * SD_0_SEGMENT_DENSITY_1_2)) && (segmentDensity[1][2] <= (MEAN_0_SEGMENT_DENSITY_1_2 + N_SD * SD_0_SEGMENT_DENSITY_1_2))) &&
    ((segmentDensity[2][0] >= (MEAN_0_SEGMENT_DENSITY_2_0 - N_SD * SD_0_SEGMENT_DENSITY_2_0)) && (segmentDensity[2][0] <= (MEAN_0_SEGMENT_DENSITY_2_0 + N_SD * SD_0_SEGMENT_DENSITY_2_0))) &&
    ((segmentDensity[2][1] >= (MEAN_0_SEGMENT_DENSITY_2_1 - N_SD * SD_0_SEGMENT_DENSITY_2_1)) && (segmentDensity[2][1] <= (MEAN_0_SEGMENT_DENSITY_2_1 + N_SD * SD_0_SEGMENT_DENSITY_2_1))) &&
    ((segmentDensity[2][2] >= (MEAN_0_SEGMENT_DENSITY_2_2 - N_SD * SD_0_SEGMENT_DENSITY_2_2)) && (segmentDensity[2][2] <= (MEAN_0_SEGMENT_DENSITY_2_2 + N_SD * SD_0_SEGMENT_DENSITY_2_2))) &&
    ((segmentDensity[3][0] >= (MEAN_0_SEGMENT_DENSITY_3_0 - N_SD * SD_0_SEGMENT_DENSITY_3_0)) && (segmentDensity[3][0] <= (MEAN_0_SEGMENT_DENSITY_3_0 + N_SD * SD_0_SEGMENT_DENSITY_3_0))) &&
    ((segmentDensity[3][1] >= (MEAN_0_SEGMENT_DENSITY_3_1 - N_SD * SD_0_SEGMENT_DENSITY_3_1)) && (segmentDensity[3][1] <= (MEAN_0_SEGMENT_DENSITY_3_1 + N_SD * SD_0_SEGMENT_DENSITY_3_1))) &&
    ((segmentDensity[3][2] >= (MEAN_0_SEGMENT_DENSITY_3_2 - N_SD * SD_0_SEGMENT_DENSITY_3_2)) && (segmentDensity[3][2] <= (MEAN_0_SEGMENT_DENSITY_3_2 + N_SD * SD_0_SEGMENT_DENSITY_3_2))) &&
    ((segmentDensity[4][0] >= (MEAN_0_SEGMENT_DENSITY_4_0 - N_SD * SD_0_SEGMENT_DENSITY_4_0)) && (segmentDensity[4][0] <= (MEAN_0_SEGMENT_DENSITY_4_0 + N_SD * SD_0_SEGMENT_DENSITY_4_0))) &&
    ((segmentDensity[4][1] >= (MEAN_0_SEGMENT_DENSITY_4_1 - N_SD * SD_0_SEGMENT_DENSITY_4_1)) && (segmentDensity[4][1] <= (MEAN_0_SEGMENT_DENSITY_4_1 + N_SD * SD_0_SEGMENT_DENSITY_4_1))) &&
    ((segmentDensity[4][2] >= (MEAN_0_SEGMENT_DENSITY_4_2 - N_SD * SD_0_SEGMENT_DENSITY_4_2)) && (segmentDensity[4][2] <= (MEAN_0_SEGMENT_DENSITY_4_2 + N_SD * SD_0_SEGMENT_DENSITY_4_2))) &&
    ((yIncrements[0][0] >= (MEAN_0_Y_INCREMENT_0_0 - N_SD * SD_0_Y_INCREMENT_0_0)) && (yIncrements[0][0] <= (MEAN_0_Y_INCREMENT_0_0 + N_SD * SD_0_Y_INCREMENT_0_0))) && 
    ((xIncrements[0][0] >= (MEAN_0_X_INCREMENT_0_0 - N_SD * SD_0_X_INCREMENT_0_0)) && (xIncrements[0][0] <= (MEAN_0_X_INCREMENT_0_0 + N_SD * SD_0_X_INCREMENT_0_0))) &&
    ((yIncrements[0][1] >= (MEAN_0_Y_INCREMENT_0_1 - N_SD * SD_0_Y_INCREMENT_0_1)) && (yIncrements[0][1] <= (MEAN_0_Y_INCREMENT_0_1 + N_SD * SD_0_Y_INCREMENT_0_1))) && 
    ((xIncrements[0][1] >= (MEAN_0_X_INCREMENT_0_1 - N_SD * SD_0_X_INCREMENT_0_1)) && (xIncrements[0][1] <= (MEAN_0_X_INCREMENT_0_1 + N_SD * SD_0_X_INCREMENT_0_1))) &&
    ((yIncrements[0][2] >= (MEAN_0_Y_INCREMENT_0_2 - N_SD * SD_0_Y_INCREMENT_0_2)) && (yIncrements[0][2] <= (MEAN_0_Y_INCREMENT_0_2 + N_SD * SD_0_Y_INCREMENT_0_2))) && 
    ((xIncrements[0][2] >= (MEAN_0_X_INCREMENT_0_2 - N_SD * SD_0_X_INCREMENT_0_2)) && (xIncrements[0][2] <= (MEAN_0_X_INCREMENT_0_2 + N_SD * SD_0_X_INCREMENT_0_2))) &&
    ((yIncrements[1][0] >= (MEAN_0_Y_INCREMENT_1_0 - N_SD * SD_0_Y_INCREMENT_1_0)) && (yIncrements[1][0] <= (MEAN_0_Y_INCREMENT_1_0 + N_SD * SD_0_Y_INCREMENT_1_0))) && 
    ((xIncrements[1][0] >= (MEAN_0_X_INCREMENT_1_0 - N_SD * SD_0_X_INCREMENT_1_0)) && (xIncrements[1][0] <= (MEAN_0_X_INCREMENT_1_0 + N_SD * SD_0_X_INCREMENT_1_0))) &&
    ((yIncrements[1][1] >= (MEAN_0_Y_INCREMENT_1_1 - N_SD * SD_0_Y_INCREMENT_1_1)) && (yIncrements[1][1] <= (MEAN_0_Y_INCREMENT_1_1 + N_SD * SD_0_Y_INCREMENT_1_1))) && 
    ((xIncrements[1][1] >= (MEAN_0_X_INCREMENT_1_1 - N_SD * SD_0_X_INCREMENT_1_1)) && (xIncrements[1][1] <= (MEAN_0_X_INCREMENT_1_1 + N_SD * SD_0_X_INCREMENT_1_1))) &&
    ((yIncrements[1][2] >= (MEAN_0_Y_INCREMENT_1_2 - N_SD * SD_0_Y_INCREMENT_1_2)) && (yIncrements[1][2] <= (MEAN_0_Y_INCREMENT_1_2 + N_SD * SD_0_Y_INCREMENT_1_2))) && 
    ((xIncrements[1][2] >= (MEAN_0_X_INCREMENT_1_2 - N_SD * SD_0_X_INCREMENT_1_2)) && (xIncrements[1][2] <= (MEAN_0_X_INCREMENT_1_2 + N_SD * SD_0_X_INCREMENT_1_2))) &&
    ((yIncrements[2][0] >= (MEAN_0_Y_INCREMENT_2_0 - N_SD * SD_0_Y_INCREMENT_2_0)) && (yIncrements[2][0] <= (MEAN_0_Y_INCREMENT_2_0 + N_SD * SD_0_Y_INCREMENT_2_0))) && 
    ((xIncrements[2][0] >= (MEAN_0_X_INCREMENT_2_0 - N_SD * SD_0_X_INCREMENT_2_0)) && (xIncrements[2][0] <= (MEAN_0_X_INCREMENT_2_0 + N_SD * SD_0_X_INCREMENT_2_0))) &&
    ((yIncrements[2][1] >= (MEAN_0_Y_INCREMENT_2_1 - N_SD * SD_0_Y_INCREMENT_2_1)) && (yIncrements[2][1] <= (MEAN_0_Y_INCREMENT_2_1 + N_SD * SD_0_Y_INCREMENT_2_1))) && 
    ((xIncrements[2][1] >= (MEAN_0_X_INCREMENT_2_1 - N_SD * SD_0_X_INCREMENT_2_1)) && (xIncrements[2][1] <= (MEAN_0_X_INCREMENT_2_1 + N_SD * SD_0_X_INCREMENT_2_1))) &&
    ((yIncrements[2][2] >= (MEAN_0_Y_INCREMENT_2_2 - N_SD * SD_0_Y_INCREMENT_2_2)) && (yIncrements[2][2] <= (MEAN_0_Y_INCREMENT_2_2 + N_SD * SD_0_Y_INCREMENT_2_2))) && 
    ((xIncrements[2][2] >= (MEAN_0_X_INCREMENT_2_2 - N_SD * SD_0_X_INCREMENT_2_2)) && (xIncrements[2][2] <= (MEAN_0_X_INCREMENT_2_2 + N_SD * SD_0_X_INCREMENT_2_2)))) {
         printf ("0\n");
    }  else if (((horizontalBalance >= (MEAN_1_HORIZONTAL_BALANCE - N_SD * SD_1_HORIZONTAL_BALANCE)) && (horizontalBalance <= (MEAN_1_HORIZONTAL_BALANCE + N_SD * SD_1_HORIZONTAL_BALANCE))) && 
    ((verticalBalance >= (MEAN_1_VERTICAL_BALANCE - N_SD * SD_1_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_1_VERTICAL_BALANCE + N_SD * SD_1_VERTICAL_BALANCE))) && 
    ((tallness >= (MEAN_1_TALLNESS - N_SD * SD_1_TALLNESS)) && (tallness <= (MEAN_1_TALLNESS + N_SD * SD_1_TALLNESS))) && 
    ((density >= (MEAN_1_VERTICAL_BALANCE - N_SD * SD_1_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_1_VERTICAL_BALANCE + N_SD * SD_1_VERTICAL_BALANCE))) && 
    ((segmentDensity[0][0] >= (MEAN_1_SEGMENT_DENSITY_0_0 - N_SD * SD_1_SEGMENT_DENSITY_0_0)) && (segmentDensity[0][0] <= (MEAN_1_SEGMENT_DENSITY_0_0 + N_SD * SD_1_SEGMENT_DENSITY_0_0))) &&
    ((segmentDensity[0][1] >= (MEAN_1_SEGMENT_DENSITY_0_1 - N_SD * SD_1_SEGMENT_DENSITY_0_1)) && (segmentDensity[0][1] <= (MEAN_1_SEGMENT_DENSITY_0_1 + N_SD * SD_1_SEGMENT_DENSITY_0_1))) &&
    ((segmentDensity[0][2] >= (MEAN_1_SEGMENT_DENSITY_0_2 - N_SD * SD_1_SEGMENT_DENSITY_0_2)) && (segmentDensity[0][2] <= (MEAN_1_SEGMENT_DENSITY_0_2 + N_SD * SD_1_SEGMENT_DENSITY_0_2))) &&
    ((segmentDensity[1][0] >= (MEAN_1_SEGMENT_DENSITY_1_0 - N_SD * SD_1_SEGMENT_DENSITY_1_0)) && (segmentDensity[1][0] <= (MEAN_1_SEGMENT_DENSITY_1_0 + N_SD * SD_1_SEGMENT_DENSITY_1_0))) &&
    ((segmentDensity[1][1] >= (MEAN_1_SEGMENT_DENSITY_1_1 - N_SD * SD_1_SEGMENT_DENSITY_1_1)) && (segmentDensity[1][1] <= (MEAN_1_SEGMENT_DENSITY_1_1 + N_SD * SD_1_SEGMENT_DENSITY_1_1))) &&
    ((segmentDensity[1][2] >= (MEAN_1_SEGMENT_DENSITY_1_2 - N_SD * SD_1_SEGMENT_DENSITY_1_2)) && (segmentDensity[1][2] <= (MEAN_1_SEGMENT_DENSITY_1_2 + N_SD * SD_1_SEGMENT_DENSITY_1_2))) &&
    ((segmentDensity[2][0] >= (MEAN_1_SEGMENT_DENSITY_2_0 - N_SD * SD_1_SEGMENT_DENSITY_2_0)) && (segmentDensity[2][0] <= (MEAN_1_SEGMENT_DENSITY_2_0 + N_SD * SD_1_SEGMENT_DENSITY_2_0))) &&
    ((segmentDensity[2][1] >= (MEAN_1_SEGMENT_DENSITY_2_1 - N_SD * SD_1_SEGMENT_DENSITY_2_1)) && (segmentDensity[2][1] <= (MEAN_1_SEGMENT_DENSITY_2_1 + N_SD * SD_1_SEGMENT_DENSITY_2_1))) &&
    ((segmentDensity[2][2] >= (MEAN_1_SEGMENT_DENSITY_2_2 - N_SD * SD_1_SEGMENT_DENSITY_2_2)) && (segmentDensity[2][2] <= (MEAN_1_SEGMENT_DENSITY_2_2 + N_SD * SD_1_SEGMENT_DENSITY_2_2))) &&
    ((segmentDensity[3][0] >= (MEAN_1_SEGMENT_DENSITY_3_0 - N_SD * SD_1_SEGMENT_DENSITY_3_0)) && (segmentDensity[3][0] <= (MEAN_1_SEGMENT_DENSITY_3_0 + N_SD * SD_1_SEGMENT_DENSITY_3_0))) &&
    ((segmentDensity[3][1] >= (MEAN_1_SEGMENT_DENSITY_3_1 - N_SD * SD_1_SEGMENT_DENSITY_3_1)) && (segmentDensity[3][1] <= (MEAN_1_SEGMENT_DENSITY_3_1 + N_SD * SD_1_SEGMENT_DENSITY_3_1))) &&
    ((segmentDensity[3][2] >= (MEAN_1_SEGMENT_DENSITY_3_2 - N_SD * SD_1_SEGMENT_DENSITY_3_2)) && (segmentDensity[3][2] <= (MEAN_1_SEGMENT_DENSITY_3_2 + N_SD * SD_1_SEGMENT_DENSITY_3_2))) &&
    ((segmentDensity[4][0] >= (MEAN_1_SEGMENT_DENSITY_4_0 - N_SD * SD_1_SEGMENT_DENSITY_4_0)) && (segmentDensity[4][0] <= (MEAN_1_SEGMENT_DENSITY_4_0 + N_SD * SD_1_SEGMENT_DENSITY_4_0))) &&
    ((segmentDensity[4][1] >= (MEAN_1_SEGMENT_DENSITY_4_1 - N_SD * SD_1_SEGMENT_DENSITY_4_1)) && (segmentDensity[4][1] <= (MEAN_1_SEGMENT_DENSITY_4_1 + N_SD * SD_1_SEGMENT_DENSITY_4_1))) &&
    ((segmentDensity[4][2] >= (MEAN_1_SEGMENT_DENSITY_4_2 - N_SD * SD_1_SEGMENT_DENSITY_4_2)) && (segmentDensity[4][2] <= (MEAN_1_SEGMENT_DENSITY_4_2 + N_SD * SD_1_SEGMENT_DENSITY_4_2))) &&
    ((yIncrements[0][0] >= (MEAN_1_Y_INCREMENT_0_0 - N_SD * SD_1_Y_INCREMENT_0_0)) && (yIncrements[0][0] <= (MEAN_1_Y_INCREMENT_0_0 + N_SD * SD_1_Y_INCREMENT_0_0))) && 
    ((xIncrements[0][0] >= (MEAN_1_X_INCREMENT_0_0 - N_SD * SD_1_X_INCREMENT_0_0)) && (xIncrements[0][0] <= (MEAN_1_X_INCREMENT_0_0 + N_SD * SD_1_X_INCREMENT_0_0))) &&
    ((yIncrements[0][1] >= (MEAN_1_Y_INCREMENT_0_1 - N_SD * SD_1_Y_INCREMENT_0_1)) && (yIncrements[0][1] <= (MEAN_1_Y_INCREMENT_0_1 + N_SD * SD_1_Y_INCREMENT_0_1))) && 
    ((xIncrements[0][1] >= (MEAN_1_X_INCREMENT_0_1 - N_SD * SD_1_X_INCREMENT_0_1)) && (xIncrements[0][1] <= (MEAN_1_X_INCREMENT_0_1 + N_SD * SD_1_X_INCREMENT_0_1))) &&
    ((yIncrements[0][2] >= (MEAN_1_Y_INCREMENT_0_2 - N_SD * SD_1_Y_INCREMENT_0_2)) && (yIncrements[0][2] <= (MEAN_1_Y_INCREMENT_0_2 + N_SD * SD_1_Y_INCREMENT_0_2))) && 
    ((xIncrements[0][2] >= (MEAN_1_X_INCREMENT_0_2 - N_SD * SD_1_X_INCREMENT_0_2)) && (xIncrements[0][2] <= (MEAN_1_X_INCREMENT_0_2 + N_SD * SD_1_X_INCREMENT_0_2))) &&
    ((yIncrements[1][0] >= (MEAN_1_Y_INCREMENT_1_0 - N_SD * SD_1_Y_INCREMENT_1_0)) && (yIncrements[1][0] <= (MEAN_1_Y_INCREMENT_1_0 + N_SD * SD_1_Y_INCREMENT_1_0))) && 
    ((xIncrements[1][0] >= (MEAN_1_X_INCREMENT_1_0 - N_SD * SD_1_X_INCREMENT_1_0)) && (xIncrements[1][0] <= (MEAN_1_X_INCREMENT_1_0 + N_SD * SD_1_X_INCREMENT_1_0))) &&
    ((yIncrements[1][1] >= (MEAN_1_Y_INCREMENT_1_1 - N_SD * SD_1_Y_INCREMENT_1_1)) && (yIncrements[1][1] <= (MEAN_1_Y_INCREMENT_1_1 + N_SD * SD_1_Y_INCREMENT_1_1))) && 
    ((xIncrements[1][1] >= (MEAN_1_X_INCREMENT_1_1 - N_SD * SD_1_X_INCREMENT_1_1)) && (xIncrements[1][1] <= (MEAN_1_X_INCREMENT_1_1 + N_SD * SD_1_X_INCREMENT_1_1))) &&
    ((yIncrements[1][2] >= (MEAN_1_Y_INCREMENT_1_2 - N_SD * SD_1_Y_INCREMENT_1_2)) && (yIncrements[1][2] <= (MEAN_1_Y_INCREMENT_1_2 + N_SD * SD_1_Y_INCREMENT_1_2))) && 
    ((xIncrements[1][2] >= (MEAN_1_X_INCREMENT_1_2 - N_SD * SD_1_X_INCREMENT_1_2)) && (xIncrements[1][2] <= (MEAN_1_X_INCREMENT_1_2 + N_SD * SD_1_X_INCREMENT_1_2))) &&
    ((yIncrements[2][0] >= (MEAN_1_Y_INCREMENT_2_0 - N_SD * SD_1_Y_INCREMENT_2_0)) && (yIncrements[2][0] <= (MEAN_1_Y_INCREMENT_2_0 + N_SD * SD_1_Y_INCREMENT_2_0))) && 
    ((xIncrements[2][0] >= (MEAN_1_X_INCREMENT_2_0 - N_SD * SD_1_X_INCREMENT_2_0)) && (xIncrements[2][0] <= (MEAN_1_X_INCREMENT_2_0 + N_SD * SD_1_X_INCREMENT_2_0))) &&
    ((yIncrements[2][1] >= (MEAN_1_Y_INCREMENT_2_1 - N_SD * SD_1_Y_INCREMENT_2_1)) && (yIncrements[2][1] <= (MEAN_1_Y_INCREMENT_2_1 + N_SD * SD_1_Y_INCREMENT_2_1))) && 
    ((xIncrements[2][1] >= (MEAN_1_X_INCREMENT_2_1 - N_SD * SD_1_X_INCREMENT_2_1)) && (xIncrements[2][1] <= (MEAN_1_X_INCREMENT_2_1 + N_SD * SD_1_X_INCREMENT_2_1))) &&
    ((yIncrements[2][2] >= (MEAN_1_Y_INCREMENT_2_2 - N_SD * SD_1_Y_INCREMENT_2_2)) && (yIncrements[2][2] <= (MEAN_1_Y_INCREMENT_2_2 + N_SD * SD_1_Y_INCREMENT_2_2))) && 
    ((xIncrements[2][2] >= (MEAN_1_X_INCREMENT_2_2 - N_SD * SD_1_X_INCREMENT_2_2)) && (xIncrements[2][2] <= (MEAN_1_X_INCREMENT_2_2 + N_SD * SD_1_X_INCREMENT_2_2)))) {
         printf ("1\n");
    }  else if (((horizontalBalance >= (MEAN_2_HORIZONTAL_BALANCE - N_SD * SD_2_HORIZONTAL_BALANCE)) && (horizontalBalance <= (MEAN_2_HORIZONTAL_BALANCE + N_SD * SD_2_HORIZONTAL_BALANCE))) && 
    ((verticalBalance >= (MEAN_2_VERTICAL_BALANCE - N_SD * SD_2_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_2_VERTICAL_BALANCE + N_SD * SD_2_VERTICAL_BALANCE))) && 
    ((tallness >= (MEAN_2_TALLNESS - N_SD * SD_2_TALLNESS)) && (tallness <= (MEAN_2_TALLNESS + N_SD * SD_2_TALLNESS))) && 
    ((density >= (MEAN_2_VERTICAL_BALANCE - N_SD * SD_2_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_2_VERTICAL_BALANCE + N_SD * SD_2_VERTICAL_BALANCE))) && 
    ((segmentDensity[0][0] >= (MEAN_2_SEGMENT_DENSITY_0_0 - N_SD * SD_2_SEGMENT_DENSITY_0_0)) && (segmentDensity[0][0] <= (MEAN_2_SEGMENT_DENSITY_0_0 + N_SD * SD_2_SEGMENT_DENSITY_0_0))) &&
    ((segmentDensity[0][1] >= (MEAN_2_SEGMENT_DENSITY_0_1 - N_SD * SD_2_SEGMENT_DENSITY_0_1)) && (segmentDensity[0][1] <= (MEAN_2_SEGMENT_DENSITY_0_1 + N_SD * SD_2_SEGMENT_DENSITY_0_1))) &&
    ((segmentDensity[0][2] >= (MEAN_2_SEGMENT_DENSITY_0_2 - N_SD * SD_2_SEGMENT_DENSITY_0_2)) && (segmentDensity[0][2] <= (MEAN_2_SEGMENT_DENSITY_0_2 + N_SD * SD_2_SEGMENT_DENSITY_0_2))) &&
    ((segmentDensity[1][0] >= (MEAN_2_SEGMENT_DENSITY_1_0 - N_SD * SD_2_SEGMENT_DENSITY_1_0)) && (segmentDensity[1][0] <= (MEAN_2_SEGMENT_DENSITY_1_0 + N_SD * SD_2_SEGMENT_DENSITY_1_0))) &&
    ((segmentDensity[1][1] >= (MEAN_2_SEGMENT_DENSITY_1_1 - N_SD * SD_2_SEGMENT_DENSITY_1_1)) && (segmentDensity[1][1] <= (MEAN_2_SEGMENT_DENSITY_1_1 + N_SD * SD_2_SEGMENT_DENSITY_1_1))) &&
    ((segmentDensity[1][2] >= (MEAN_2_SEGMENT_DENSITY_1_2 - N_SD * SD_2_SEGMENT_DENSITY_1_2)) && (segmentDensity[1][2] <= (MEAN_2_SEGMENT_DENSITY_1_2 + N_SD * SD_2_SEGMENT_DENSITY_1_2))) &&
    ((segmentDensity[2][0] >= (MEAN_2_SEGMENT_DENSITY_2_0 - N_SD * SD_2_SEGMENT_DENSITY_2_0)) && (segmentDensity[2][0] <= (MEAN_2_SEGMENT_DENSITY_2_0 + N_SD * SD_2_SEGMENT_DENSITY_2_0))) &&
    ((segmentDensity[2][1] >= (MEAN_2_SEGMENT_DENSITY_2_1 - N_SD * SD_2_SEGMENT_DENSITY_2_1)) && (segmentDensity[2][1] <= (MEAN_2_SEGMENT_DENSITY_2_1 + N_SD * SD_2_SEGMENT_DENSITY_2_1))) &&
    ((segmentDensity[2][2] >= (MEAN_2_SEGMENT_DENSITY_2_2 - N_SD * SD_2_SEGMENT_DENSITY_2_2)) && (segmentDensity[2][2] <= (MEAN_2_SEGMENT_DENSITY_2_2 + N_SD * SD_2_SEGMENT_DENSITY_2_2))) &&
    ((segmentDensity[3][0] >= (MEAN_2_SEGMENT_DENSITY_3_0 - N_SD * SD_2_SEGMENT_DENSITY_3_0)) && (segmentDensity[3][0] <= (MEAN_2_SEGMENT_DENSITY_3_0 + N_SD * SD_2_SEGMENT_DENSITY_3_0))) &&
    ((segmentDensity[3][1] >= (MEAN_2_SEGMENT_DENSITY_3_1 - N_SD * SD_2_SEGMENT_DENSITY_3_1)) && (segmentDensity[3][1] <= (MEAN_2_SEGMENT_DENSITY_3_1 + N_SD * SD_2_SEGMENT_DENSITY_3_1))) &&
    ((segmentDensity[3][2] >= (MEAN_2_SEGMENT_DENSITY_3_2 - N_SD * SD_2_SEGMENT_DENSITY_3_2)) && (segmentDensity[3][2] <= (MEAN_2_SEGMENT_DENSITY_3_2 + N_SD * SD_2_SEGMENT_DENSITY_3_2))) &&
    ((segmentDensity[4][0] >= (MEAN_2_SEGMENT_DENSITY_4_0 - N_SD * SD_2_SEGMENT_DENSITY_4_0)) && (segmentDensity[4][0] <= (MEAN_2_SEGMENT_DENSITY_4_0 + N_SD * SD_2_SEGMENT_DENSITY_4_0))) &&
    ((segmentDensity[4][1] >= (MEAN_2_SEGMENT_DENSITY_4_1 - N_SD * SD_2_SEGMENT_DENSITY_4_1)) && (segmentDensity[4][1] <= (MEAN_2_SEGMENT_DENSITY_4_1 + N_SD * SD_2_SEGMENT_DENSITY_4_1))) &&
    ((segmentDensity[4][2] >= (MEAN_2_SEGMENT_DENSITY_4_2 - N_SD * SD_2_SEGMENT_DENSITY_4_2)) && (segmentDensity[4][2] <= (MEAN_2_SEGMENT_DENSITY_4_2 + N_SD * SD_2_SEGMENT_DENSITY_4_2))) &&
    ((yIncrements[0][0] >= (MEAN_2_Y_INCREMENT_0_0 - N_SD * SD_2_Y_INCREMENT_0_0)) && (yIncrements[0][0] <= (MEAN_2_Y_INCREMENT_0_0 + N_SD * SD_2_Y_INCREMENT_0_0))) && 
    ((xIncrements[0][0] >= (MEAN_2_X_INCREMENT_0_0 - N_SD * SD_2_X_INCREMENT_0_0)) && (xIncrements[0][0] <= (MEAN_2_X_INCREMENT_0_0 + N_SD * SD_2_X_INCREMENT_0_0))) &&
    ((yIncrements[0][1] >= (MEAN_2_Y_INCREMENT_0_1 - N_SD * SD_2_Y_INCREMENT_0_1)) && (yIncrements[0][1] <= (MEAN_2_Y_INCREMENT_0_1 + N_SD * SD_2_Y_INCREMENT_0_1))) && 
    ((xIncrements[0][1] >= (MEAN_2_X_INCREMENT_0_1 - N_SD * SD_2_X_INCREMENT_0_1)) && (xIncrements[0][1] <= (MEAN_2_X_INCREMENT_0_1 + N_SD * SD_2_X_INCREMENT_0_1))) &&
    ((yIncrements[0][2] >= (MEAN_2_Y_INCREMENT_0_2 - N_SD * SD_2_Y_INCREMENT_0_2)) && (yIncrements[0][2] <= (MEAN_2_Y_INCREMENT_0_2 + N_SD * SD_2_Y_INCREMENT_0_2))) && 
    ((xIncrements[0][2] >= (MEAN_2_X_INCREMENT_0_2 - N_SD * SD_2_X_INCREMENT_0_2)) && (xIncrements[0][2] <= (MEAN_2_X_INCREMENT_0_2 + N_SD * SD_2_X_INCREMENT_0_2))) &&
    ((yIncrements[1][0] >= (MEAN_2_Y_INCREMENT_1_0 - N_SD * SD_2_Y_INCREMENT_1_0)) && (yIncrements[1][0] <= (MEAN_2_Y_INCREMENT_1_0 + N_SD * SD_2_Y_INCREMENT_1_0))) && 
    ((xIncrements[1][0] >= (MEAN_2_X_INCREMENT_1_0 - N_SD * SD_2_X_INCREMENT_1_0)) && (xIncrements[1][0] <= (MEAN_2_X_INCREMENT_1_0 + N_SD * SD_2_X_INCREMENT_1_0))) &&
    ((yIncrements[1][1] >= (MEAN_2_Y_INCREMENT_1_1 - N_SD * SD_2_Y_INCREMENT_1_1)) && (yIncrements[1][1] <= (MEAN_2_Y_INCREMENT_1_1 + N_SD * SD_2_Y_INCREMENT_1_1))) && 
    ((xIncrements[1][1] >= (MEAN_2_X_INCREMENT_1_1 - N_SD * SD_2_X_INCREMENT_1_1)) && (xIncrements[1][1] <= (MEAN_2_X_INCREMENT_1_1 + N_SD * SD_2_X_INCREMENT_1_1))) &&
    ((yIncrements[1][2] >= (MEAN_2_Y_INCREMENT_1_2 - N_SD * SD_2_Y_INCREMENT_1_2)) && (yIncrements[1][2] <= (MEAN_2_Y_INCREMENT_1_2 + N_SD * SD_2_Y_INCREMENT_1_2))) && 
    ((xIncrements[1][2] >= (MEAN_2_X_INCREMENT_1_2 - N_SD * SD_2_X_INCREMENT_1_2)) && (xIncrements[1][2] <= (MEAN_2_X_INCREMENT_1_2 + N_SD * SD_2_X_INCREMENT_1_2))) &&
    ((yIncrements[2][0] >= (MEAN_2_Y_INCREMENT_2_0 - N_SD * SD_2_Y_INCREMENT_2_0)) && (yIncrements[2][0] <= (MEAN_2_Y_INCREMENT_2_0 + N_SD * SD_2_Y_INCREMENT_2_0))) && 
    ((xIncrements[2][0] >= (MEAN_2_X_INCREMENT_2_0 - N_SD * SD_2_X_INCREMENT_2_0)) && (xIncrements[2][0] <= (MEAN_2_X_INCREMENT_2_0 + N_SD * SD_2_X_INCREMENT_2_0))) &&
    ((yIncrements[2][1] >= (MEAN_2_Y_INCREMENT_2_1 - N_SD * SD_2_Y_INCREMENT_2_1)) && (yIncrements[2][1] <= (MEAN_2_Y_INCREMENT_2_1 + N_SD * SD_2_Y_INCREMENT_2_1))) && 
    ((xIncrements[2][1] >= (MEAN_2_X_INCREMENT_2_1 - N_SD * SD_2_X_INCREMENT_2_1)) && (xIncrements[2][1] <= (MEAN_2_X_INCREMENT_2_1 + N_SD * SD_2_X_INCREMENT_2_1))) &&
    ((yIncrements[2][2] >= (MEAN_2_Y_INCREMENT_2_2 - N_SD * SD_2_Y_INCREMENT_2_2)) && (yIncrements[2][2] <= (MEAN_2_Y_INCREMENT_2_2 + N_SD * SD_2_Y_INCREMENT_2_2))) && 
    ((xIncrements[2][2] >= (MEAN_2_X_INCREMENT_2_2 - N_SD * SD_2_X_INCREMENT_2_2)) && (xIncrements[2][2] <= (MEAN_2_X_INCREMENT_2_2 + N_SD * SD_2_X_INCREMENT_2_2)))) {
         printf ("2\n");
    }  else if (((horizontalBalance >= (MEAN_3_HORIZONTAL_BALANCE - N_SD * SD_3_HORIZONTAL_BALANCE)) && (horizontalBalance <= (MEAN_3_HORIZONTAL_BALANCE + N_SD * SD_3_HORIZONTAL_BALANCE))) && 
    ((verticalBalance >= (MEAN_3_VERTICAL_BALANCE - N_SD * SD_3_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_3_VERTICAL_BALANCE + N_SD * SD_3_VERTICAL_BALANCE))) && 
    ((tallness >= (MEAN_3_TALLNESS - N_SD * SD_3_TALLNESS)) && (tallness <= (MEAN_3_TALLNESS + N_SD * SD_3_TALLNESS))) && 
    ((density >= (MEAN_3_VERTICAL_BALANCE - N_SD * SD_3_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_3_VERTICAL_BALANCE + N_SD * SD_3_VERTICAL_BALANCE))) && 
    ((segmentDensity[0][0] >= (MEAN_3_SEGMENT_DENSITY_0_0 - N_SD * SD_3_SEGMENT_DENSITY_0_0)) && (segmentDensity[0][0] <= (MEAN_3_SEGMENT_DENSITY_0_0 + N_SD * SD_3_SEGMENT_DENSITY_0_0))) &&
    ((segmentDensity[0][1] >= (MEAN_3_SEGMENT_DENSITY_0_1 - N_SD * SD_3_SEGMENT_DENSITY_0_1)) && (segmentDensity[0][1] <= (MEAN_3_SEGMENT_DENSITY_0_1 + N_SD * SD_3_SEGMENT_DENSITY_0_1))) &&
    ((segmentDensity[0][2] >= (MEAN_3_SEGMENT_DENSITY_0_2 - N_SD * SD_3_SEGMENT_DENSITY_0_2)) && (segmentDensity[0][2] <= (MEAN_3_SEGMENT_DENSITY_0_2 + N_SD * SD_3_SEGMENT_DENSITY_0_2))) &&
    ((segmentDensity[1][0] >= (MEAN_3_SEGMENT_DENSITY_1_0 - N_SD * SD_3_SEGMENT_DENSITY_1_0)) && (segmentDensity[1][0] <= (MEAN_3_SEGMENT_DENSITY_1_0 + N_SD * SD_3_SEGMENT_DENSITY_1_0))) &&
    ((segmentDensity[1][1] >= (MEAN_3_SEGMENT_DENSITY_1_1 - N_SD * SD_3_SEGMENT_DENSITY_1_1)) && (segmentDensity[1][1] <= (MEAN_3_SEGMENT_DENSITY_1_1 + N_SD * SD_3_SEGMENT_DENSITY_1_1))) &&
    ((segmentDensity[1][2] >= (MEAN_3_SEGMENT_DENSITY_1_2 - N_SD * SD_3_SEGMENT_DENSITY_1_2)) && (segmentDensity[1][2] <= (MEAN_3_SEGMENT_DENSITY_1_2 + N_SD * SD_3_SEGMENT_DENSITY_1_2))) &&
    ((segmentDensity[2][0] >= (MEAN_3_SEGMENT_DENSITY_2_0 - N_SD * SD_3_SEGMENT_DENSITY_2_0)) && (segmentDensity[2][0] <= (MEAN_3_SEGMENT_DENSITY_2_0 + N_SD * SD_3_SEGMENT_DENSITY_2_0))) &&
    ((segmentDensity[2][1] >= (MEAN_3_SEGMENT_DENSITY_2_1 - N_SD * SD_3_SEGMENT_DENSITY_2_1)) && (segmentDensity[2][1] <= (MEAN_3_SEGMENT_DENSITY_2_1 + N_SD * SD_3_SEGMENT_DENSITY_2_1))) &&
    ((segmentDensity[2][2] >= (MEAN_3_SEGMENT_DENSITY_2_2 - N_SD * SD_3_SEGMENT_DENSITY_2_2)) && (segmentDensity[2][2] <= (MEAN_3_SEGMENT_DENSITY_2_2 + N_SD * SD_3_SEGMENT_DENSITY_2_2))) &&
    ((segmentDensity[3][0] >= (MEAN_3_SEGMENT_DENSITY_3_0 - N_SD * SD_3_SEGMENT_DENSITY_3_0)) && (segmentDensity[3][0] <= (MEAN_3_SEGMENT_DENSITY_3_0 + N_SD * SD_3_SEGMENT_DENSITY_3_0))) &&
    ((segmentDensity[3][1] >= (MEAN_3_SEGMENT_DENSITY_3_1 - N_SD * SD_3_SEGMENT_DENSITY_3_1)) && (segmentDensity[3][1] <= (MEAN_3_SEGMENT_DENSITY_3_1 + N_SD * SD_3_SEGMENT_DENSITY_3_1))) &&
    ((segmentDensity[3][2] >= (MEAN_3_SEGMENT_DENSITY_3_2 - N_SD * SD_3_SEGMENT_DENSITY_3_2)) && (segmentDensity[3][2] <= (MEAN_3_SEGMENT_DENSITY_3_2 + N_SD * SD_3_SEGMENT_DENSITY_3_2))) &&
    ((segmentDensity[4][0] >= (MEAN_3_SEGMENT_DENSITY_4_0 - N_SD * SD_3_SEGMENT_DENSITY_4_0)) && (segmentDensity[4][0] <= (MEAN_3_SEGMENT_DENSITY_4_0 + N_SD * SD_3_SEGMENT_DENSITY_4_0))) &&
    ((segmentDensity[4][1] >= (MEAN_3_SEGMENT_DENSITY_4_1 - N_SD * SD_3_SEGMENT_DENSITY_4_1)) && (segmentDensity[4][1] <= (MEAN_3_SEGMENT_DENSITY_4_1 + N_SD * SD_3_SEGMENT_DENSITY_4_1))) &&
    ((segmentDensity[4][2] >= (MEAN_3_SEGMENT_DENSITY_4_2 - N_SD * SD_3_SEGMENT_DENSITY_4_2)) && (segmentDensity[4][2] <= (MEAN_3_SEGMENT_DENSITY_4_2 + N_SD * SD_3_SEGMENT_DENSITY_4_2))) &&
    ((yIncrements[0][0] >= (MEAN_3_Y_INCREMENT_0_0 - N_SD * SD_3_Y_INCREMENT_0_0)) && (yIncrements[0][0] <= (MEAN_3_Y_INCREMENT_0_0 + N_SD * SD_3_Y_INCREMENT_0_0))) && 
    ((xIncrements[0][0] >= (MEAN_3_X_INCREMENT_0_0 - N_SD * SD_3_X_INCREMENT_0_0)) && (xIncrements[0][0] <= (MEAN_3_X_INCREMENT_0_0 + N_SD * SD_3_X_INCREMENT_0_0))) &&
    ((yIncrements[0][1] >= (MEAN_3_Y_INCREMENT_0_1 - N_SD * SD_3_Y_INCREMENT_0_1)) && (yIncrements[0][1] <= (MEAN_3_Y_INCREMENT_0_1 + N_SD * SD_3_Y_INCREMENT_0_1))) && 
    ((xIncrements[0][1] >= (MEAN_3_X_INCREMENT_0_1 - N_SD * SD_3_X_INCREMENT_0_1)) && (xIncrements[0][1] <= (MEAN_3_X_INCREMENT_0_1 + N_SD * SD_3_X_INCREMENT_0_1))) &&
    ((yIncrements[0][2] >= (MEAN_3_Y_INCREMENT_0_2 - N_SD * SD_3_Y_INCREMENT_0_2)) && (yIncrements[0][2] <= (MEAN_3_Y_INCREMENT_0_2 + N_SD * SD_3_Y_INCREMENT_0_2))) && 
    ((xIncrements[0][2] >= (MEAN_3_X_INCREMENT_0_2 - N_SD * SD_3_X_INCREMENT_0_2)) && (xIncrements[0][2] <= (MEAN_3_X_INCREMENT_0_2 + N_SD * SD_3_X_INCREMENT_0_2))) &&
    ((yIncrements[1][0] >= (MEAN_3_Y_INCREMENT_1_0 - N_SD * SD_3_Y_INCREMENT_1_0)) && (yIncrements[1][0] <= (MEAN_3_Y_INCREMENT_1_0 + N_SD * SD_3_Y_INCREMENT_1_0))) && 
    ((xIncrements[1][0] >= (MEAN_3_X_INCREMENT_1_0 - N_SD * SD_3_X_INCREMENT_1_0)) && (xIncrements[1][0] <= (MEAN_3_X_INCREMENT_1_0 + N_SD * SD_3_X_INCREMENT_1_0))) &&
    ((yIncrements[1][1] >= (MEAN_3_Y_INCREMENT_1_1 - N_SD * SD_3_Y_INCREMENT_1_1)) && (yIncrements[1][1] <= (MEAN_3_Y_INCREMENT_1_1 + N_SD * SD_3_Y_INCREMENT_1_1))) && 
    ((xIncrements[1][1] >= (MEAN_3_X_INCREMENT_1_1 - N_SD * SD_3_X_INCREMENT_1_1)) && (xIncrements[1][1] <= (MEAN_3_X_INCREMENT_1_1 + N_SD * SD_3_X_INCREMENT_1_1))) &&
    ((yIncrements[1][2] >= (MEAN_3_Y_INCREMENT_1_2 - N_SD * SD_3_Y_INCREMENT_1_2)) && (yIncrements[1][2] <= (MEAN_3_Y_INCREMENT_1_2 + N_SD * SD_3_Y_INCREMENT_1_2))) && 
    ((xIncrements[1][2] >= (MEAN_3_X_INCREMENT_1_2 - N_SD * SD_3_X_INCREMENT_1_2)) && (xIncrements[1][2] <= (MEAN_3_X_INCREMENT_1_2 + N_SD * SD_3_X_INCREMENT_1_2))) &&
    ((yIncrements[2][0] >= (MEAN_3_Y_INCREMENT_2_0 - N_SD * SD_3_Y_INCREMENT_2_0)) && (yIncrements[2][0] <= (MEAN_3_Y_INCREMENT_2_0 + N_SD * SD_3_Y_INCREMENT_2_0))) && 
    ((xIncrements[2][0] >= (MEAN_3_X_INCREMENT_2_0 - N_SD * SD_3_X_INCREMENT_2_0)) && (xIncrements[2][0] <= (MEAN_3_X_INCREMENT_2_0 + N_SD * SD_3_X_INCREMENT_2_0))) &&
    ((yIncrements[2][1] >= (MEAN_3_Y_INCREMENT_2_1 - N_SD * SD_3_Y_INCREMENT_2_1)) && (yIncrements[2][1] <= (MEAN_3_Y_INCREMENT_2_1 + N_SD * SD_3_Y_INCREMENT_2_1))) && 
    ((xIncrements[2][1] >= (MEAN_3_X_INCREMENT_2_1 - N_SD * SD_3_X_INCREMENT_2_1)) && (xIncrements[2][1] <= (MEAN_3_X_INCREMENT_2_1 + N_SD * SD_3_X_INCREMENT_2_1))) &&
    ((yIncrements[2][2] >= (MEAN_3_Y_INCREMENT_2_2 - N_SD * SD_3_Y_INCREMENT_2_2)) && (yIncrements[2][2] <= (MEAN_3_Y_INCREMENT_2_2 + N_SD * SD_3_Y_INCREMENT_2_2))) && 
    ((xIncrements[2][2] >= (MEAN_3_X_INCREMENT_2_2 - N_SD * SD_3_X_INCREMENT_2_2)) && (xIncrements[2][2] <= (MEAN_3_X_INCREMENT_2_2 + N_SD * SD_3_X_INCREMENT_2_2)))) {
         printf ("3\n");
    }  else if (((horizontalBalance >= (MEAN_4_HORIZONTAL_BALANCE - N_SD * SD_4_HORIZONTAL_BALANCE)) && (horizontalBalance <= (MEAN_4_HORIZONTAL_BALANCE + N_SD * SD_4_HORIZONTAL_BALANCE))) && 
    ((verticalBalance >= (MEAN_4_VERTICAL_BALANCE - N_SD * SD_4_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_4_VERTICAL_BALANCE + N_SD * SD_4_VERTICAL_BALANCE))) && 
    ((tallness >= (MEAN_4_TALLNESS - N_SD * SD_4_TALLNESS)) && (tallness <= (MEAN_4_TALLNESS + N_SD * SD_4_TALLNESS))) && 
    ((density >= (MEAN_4_VERTICAL_BALANCE - N_SD * SD_4_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_4_VERTICAL_BALANCE + N_SD * SD_4_VERTICAL_BALANCE))) && 
    ((segmentDensity[0][0] >= (MEAN_4_SEGMENT_DENSITY_0_0 - N_SD * SD_4_SEGMENT_DENSITY_0_0)) && (segmentDensity[0][0] <= (MEAN_4_SEGMENT_DENSITY_0_0 + N_SD * SD_4_SEGMENT_DENSITY_0_0))) &&
    ((segmentDensity[0][1] >= (MEAN_4_SEGMENT_DENSITY_0_1 - N_SD * SD_4_SEGMENT_DENSITY_0_1)) && (segmentDensity[0][1] <= (MEAN_4_SEGMENT_DENSITY_0_1 + N_SD * SD_4_SEGMENT_DENSITY_0_1))) &&
    ((segmentDensity[0][2] >= (MEAN_4_SEGMENT_DENSITY_0_2 - N_SD * SD_4_SEGMENT_DENSITY_0_2)) && (segmentDensity[0][2] <= (MEAN_4_SEGMENT_DENSITY_0_2 + N_SD * SD_4_SEGMENT_DENSITY_0_2))) &&
    ((segmentDensity[1][0] >= (MEAN_4_SEGMENT_DENSITY_1_0 - N_SD * SD_4_SEGMENT_DENSITY_1_0)) && (segmentDensity[1][0] <= (MEAN_4_SEGMENT_DENSITY_1_0 + N_SD * SD_4_SEGMENT_DENSITY_1_0))) &&
    ((segmentDensity[1][1] >= (MEAN_4_SEGMENT_DENSITY_1_1 - N_SD * SD_4_SEGMENT_DENSITY_1_1)) && (segmentDensity[1][1] <= (MEAN_4_SEGMENT_DENSITY_1_1 + N_SD * SD_4_SEGMENT_DENSITY_1_1))) &&
    ((segmentDensity[1][2] >= (MEAN_4_SEGMENT_DENSITY_1_2 - N_SD * SD_4_SEGMENT_DENSITY_1_2)) && (segmentDensity[1][2] <= (MEAN_4_SEGMENT_DENSITY_1_2 + N_SD * SD_4_SEGMENT_DENSITY_1_2))) &&
    ((segmentDensity[2][0] >= (MEAN_4_SEGMENT_DENSITY_2_0 - N_SD * SD_4_SEGMENT_DENSITY_2_0)) && (segmentDensity[2][0] <= (MEAN_4_SEGMENT_DENSITY_2_0 + N_SD * SD_4_SEGMENT_DENSITY_2_0))) &&
    ((segmentDensity[2][1] >= (MEAN_4_SEGMENT_DENSITY_2_1 - N_SD * SD_4_SEGMENT_DENSITY_2_1)) && (segmentDensity[2][1] <= (MEAN_4_SEGMENT_DENSITY_2_1 + N_SD * SD_4_SEGMENT_DENSITY_2_1))) &&
    ((segmentDensity[2][2] >= (MEAN_4_SEGMENT_DENSITY_2_2 - N_SD * SD_4_SEGMENT_DENSITY_2_2)) && (segmentDensity[2][2] <= (MEAN_4_SEGMENT_DENSITY_2_2 + N_SD * SD_4_SEGMENT_DENSITY_2_2))) &&
    ((segmentDensity[3][0] >= (MEAN_4_SEGMENT_DENSITY_3_0 - N_SD * SD_4_SEGMENT_DENSITY_3_0)) && (segmentDensity[3][0] <= (MEAN_4_SEGMENT_DENSITY_3_0 + N_SD * SD_4_SEGMENT_DENSITY_3_0))) &&
    ((segmentDensity[3][1] >= (MEAN_4_SEGMENT_DENSITY_3_1 - N_SD * SD_4_SEGMENT_DENSITY_3_1)) && (segmentDensity[3][1] <= (MEAN_4_SEGMENT_DENSITY_3_1 + N_SD * SD_4_SEGMENT_DENSITY_3_1))) &&
    ((segmentDensity[3][2] >= (MEAN_4_SEGMENT_DENSITY_3_2 - N_SD * SD_4_SEGMENT_DENSITY_3_2)) && (segmentDensity[3][2] <= (MEAN_4_SEGMENT_DENSITY_3_2 + N_SD * SD_4_SEGMENT_DENSITY_3_2))) &&
    ((segmentDensity[4][0] >= (MEAN_4_SEGMENT_DENSITY_4_0 - N_SD * SD_4_SEGMENT_DENSITY_4_0)) && (segmentDensity[4][0] <= (MEAN_4_SEGMENT_DENSITY_4_0 + N_SD * SD_4_SEGMENT_DENSITY_4_0))) &&
    ((segmentDensity[4][1] >= (MEAN_4_SEGMENT_DENSITY_4_1 - N_SD * SD_4_SEGMENT_DENSITY_4_1)) && (segmentDensity[4][1] <= (MEAN_4_SEGMENT_DENSITY_4_1 + N_SD * SD_4_SEGMENT_DENSITY_4_1))) &&
    ((segmentDensity[4][2] >= (MEAN_4_SEGMENT_DENSITY_4_2 - N_SD * SD_4_SEGMENT_DENSITY_4_2)) && (segmentDensity[4][2] <= (MEAN_4_SEGMENT_DENSITY_4_2 + N_SD * SD_4_SEGMENT_DENSITY_4_2))) &&
    ((yIncrements[0][0] >= (MEAN_4_Y_INCREMENT_0_0 - N_SD * SD_4_Y_INCREMENT_0_0)) && (yIncrements[0][0] <= (MEAN_4_Y_INCREMENT_0_0 + N_SD * SD_4_Y_INCREMENT_0_0))) && 
    ((xIncrements[0][0] >= (MEAN_4_X_INCREMENT_0_0 - N_SD * SD_4_X_INCREMENT_0_0)) && (xIncrements[0][0] <= (MEAN_4_X_INCREMENT_0_0 + N_SD * SD_4_X_INCREMENT_0_0))) &&
    ((yIncrements[0][1] >= (MEAN_4_Y_INCREMENT_0_1 - N_SD * SD_4_Y_INCREMENT_0_1)) && (yIncrements[0][1] <= (MEAN_4_Y_INCREMENT_0_1 + N_SD * SD_4_Y_INCREMENT_0_1))) && 
    ((xIncrements[0][1] >= (MEAN_4_X_INCREMENT_0_1 - N_SD * SD_4_X_INCREMENT_0_1)) && (xIncrements[0][1] <= (MEAN_4_X_INCREMENT_0_1 + N_SD * SD_4_X_INCREMENT_0_1))) &&
    ((yIncrements[0][2] >= (MEAN_4_Y_INCREMENT_0_2 - N_SD * SD_4_Y_INCREMENT_0_2)) && (yIncrements[0][2] <= (MEAN_4_Y_INCREMENT_0_2 + N_SD * SD_4_Y_INCREMENT_0_2))) && 
    ((xIncrements[0][2] >= (MEAN_4_X_INCREMENT_0_2 - N_SD * SD_4_X_INCREMENT_0_2)) && (xIncrements[0][2] <= (MEAN_4_X_INCREMENT_0_2 + N_SD * SD_4_X_INCREMENT_0_2))) &&
    ((yIncrements[1][0] >= (MEAN_4_Y_INCREMENT_1_0 - N_SD * SD_4_Y_INCREMENT_1_0)) && (yIncrements[1][0] <= (MEAN_4_Y_INCREMENT_1_0 + N_SD * SD_4_Y_INCREMENT_1_0))) && 
    ((xIncrements[1][0] >= (MEAN_4_X_INCREMENT_1_0 - N_SD * SD_4_X_INCREMENT_1_0)) && (xIncrements[1][0] <= (MEAN_4_X_INCREMENT_1_0 + N_SD * SD_4_X_INCREMENT_1_0))) &&
    ((yIncrements[1][1] >= (MEAN_4_Y_INCREMENT_1_1 - N_SD * SD_4_Y_INCREMENT_1_1)) && (yIncrements[1][1] <= (MEAN_4_Y_INCREMENT_1_1 + N_SD * SD_4_Y_INCREMENT_1_1))) && 
    ((xIncrements[1][1] >= (MEAN_4_X_INCREMENT_1_1 - N_SD * SD_4_X_INCREMENT_1_1)) && (xIncrements[1][1] <= (MEAN_4_X_INCREMENT_1_1 + N_SD * SD_4_X_INCREMENT_1_1))) &&
    ((yIncrements[1][2] >= (MEAN_4_Y_INCREMENT_1_2 - N_SD * SD_4_Y_INCREMENT_1_2)) && (yIncrements[1][2] <= (MEAN_4_Y_INCREMENT_1_2 + N_SD * SD_4_Y_INCREMENT_1_2))) && 
    ((xIncrements[1][2] >= (MEAN_4_X_INCREMENT_1_2 - N_SD * SD_4_X_INCREMENT_1_2)) && (xIncrements[1][2] <= (MEAN_4_X_INCREMENT_1_2 + N_SD * SD_4_X_INCREMENT_1_2))) &&
    ((yIncrements[2][0] >= (MEAN_4_Y_INCREMENT_2_0 - N_SD * SD_4_Y_INCREMENT_2_0)) && (yIncrements[2][0] <= (MEAN_4_Y_INCREMENT_2_0 + N_SD * SD_4_Y_INCREMENT_2_0))) && 
    ((xIncrements[2][0] >= (MEAN_4_X_INCREMENT_2_0 - N_SD * SD_4_X_INCREMENT_2_0)) && (xIncrements[2][0] <= (MEAN_4_X_INCREMENT_2_0 + N_SD * SD_4_X_INCREMENT_2_0))) &&
    ((yIncrements[2][1] >= (MEAN_4_Y_INCREMENT_2_1 - N_SD * SD_4_Y_INCREMENT_2_1)) && (yIncrements[2][1] <= (MEAN_4_Y_INCREMENT_2_1 + N_SD * SD_4_Y_INCREMENT_2_1))) && 
    ((xIncrements[2][1] >= (MEAN_4_X_INCREMENT_2_1 - N_SD * SD_4_X_INCREMENT_2_1)) && (xIncrements[2][1] <= (MEAN_4_X_INCREMENT_2_1 + N_SD * SD_4_X_INCREMENT_2_1))) &&
    ((yIncrements[2][2] >= (MEAN_4_Y_INCREMENT_2_2 - N_SD * SD_4_Y_INCREMENT_2_2)) && (yIncrements[2][2] <= (MEAN_4_Y_INCREMENT_2_2 + N_SD * SD_4_Y_INCREMENT_2_2))) && 
    ((xIncrements[2][2] >= (MEAN_4_X_INCREMENT_2_2 - N_SD * SD_4_X_INCREMENT_2_2)) && (xIncrements[2][2] <= (MEAN_4_X_INCREMENT_2_2 + N_SD * SD_4_X_INCREMENT_2_2)))) {
         printf ("4\n");
    }  else if (((horizontalBalance >= (MEAN_5_HORIZONTAL_BALANCE - N_SD * SD_5_HORIZONTAL_BALANCE)) && (horizontalBalance <= (MEAN_5_HORIZONTAL_BALANCE + N_SD * SD_5_HORIZONTAL_BALANCE))) && 
    ((verticalBalance >= (MEAN_5_VERTICAL_BALANCE - N_SD * SD_5_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_5_VERTICAL_BALANCE + N_SD * SD_5_VERTICAL_BALANCE))) && 
    ((tallness >= (MEAN_5_TALLNESS - N_SD * SD_5_TALLNESS)) && (tallness <= (MEAN_5_TALLNESS + N_SD * SD_5_TALLNESS))) && 
    ((density >= (MEAN_5_VERTICAL_BALANCE - N_SD * SD_5_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_5_VERTICAL_BALANCE + N_SD * SD_5_VERTICAL_BALANCE))) && 
    ((segmentDensity[0][0] >= (MEAN_5_SEGMENT_DENSITY_0_0 - N_SD * SD_5_SEGMENT_DENSITY_0_0)) && (segmentDensity[0][0] <= (MEAN_5_SEGMENT_DENSITY_0_0 + N_SD * SD_5_SEGMENT_DENSITY_0_0))) &&
    ((segmentDensity[0][1] >= (MEAN_5_SEGMENT_DENSITY_0_1 - N_SD * SD_5_SEGMENT_DENSITY_0_1)) && (segmentDensity[0][1] <= (MEAN_5_SEGMENT_DENSITY_0_1 + N_SD * SD_5_SEGMENT_DENSITY_0_1))) &&
    ((segmentDensity[0][2] >= (MEAN_5_SEGMENT_DENSITY_0_2 - N_SD * SD_5_SEGMENT_DENSITY_0_2)) && (segmentDensity[0][2] <= (MEAN_5_SEGMENT_DENSITY_0_2 + N_SD * SD_5_SEGMENT_DENSITY_0_2))) &&
    ((segmentDensity[1][0] >= (MEAN_5_SEGMENT_DENSITY_1_0 - N_SD * SD_5_SEGMENT_DENSITY_1_0)) && (segmentDensity[1][0] <= (MEAN_5_SEGMENT_DENSITY_1_0 + N_SD * SD_5_SEGMENT_DENSITY_1_0))) &&
    ((segmentDensity[1][1] >= (MEAN_5_SEGMENT_DENSITY_1_1 - N_SD * SD_5_SEGMENT_DENSITY_1_1)) && (segmentDensity[1][1] <= (MEAN_5_SEGMENT_DENSITY_1_1 + N_SD * SD_5_SEGMENT_DENSITY_1_1))) &&
    ((segmentDensity[1][2] >= (MEAN_5_SEGMENT_DENSITY_1_2 - N_SD * SD_5_SEGMENT_DENSITY_1_2)) && (segmentDensity[1][2] <= (MEAN_5_SEGMENT_DENSITY_1_2 + N_SD * SD_5_SEGMENT_DENSITY_1_2))) &&
    ((segmentDensity[2][0] >= (MEAN_5_SEGMENT_DENSITY_2_0 - N_SD * SD_5_SEGMENT_DENSITY_2_0)) && (segmentDensity[2][0] <= (MEAN_5_SEGMENT_DENSITY_2_0 + N_SD * SD_5_SEGMENT_DENSITY_2_0))) &&
    ((segmentDensity[2][1] >= (MEAN_5_SEGMENT_DENSITY_2_1 - N_SD * SD_5_SEGMENT_DENSITY_2_1)) && (segmentDensity[2][1] <= (MEAN_5_SEGMENT_DENSITY_2_1 + N_SD * SD_5_SEGMENT_DENSITY_2_1))) &&
    ((segmentDensity[2][2] >= (MEAN_5_SEGMENT_DENSITY_2_2 - N_SD * SD_5_SEGMENT_DENSITY_2_2)) && (segmentDensity[2][2] <= (MEAN_5_SEGMENT_DENSITY_2_2 + N_SD * SD_5_SEGMENT_DENSITY_2_2))) &&
    ((segmentDensity[3][0] >= (MEAN_5_SEGMENT_DENSITY_3_0 - N_SD * SD_5_SEGMENT_DENSITY_3_0)) && (segmentDensity[3][0] <= (MEAN_5_SEGMENT_DENSITY_3_0 + N_SD * SD_5_SEGMENT_DENSITY_3_0))) &&
    ((segmentDensity[3][1] >= (MEAN_5_SEGMENT_DENSITY_3_1 - N_SD * SD_5_SEGMENT_DENSITY_3_1)) && (segmentDensity[3][1] <= (MEAN_5_SEGMENT_DENSITY_3_1 + N_SD * SD_5_SEGMENT_DENSITY_3_1))) &&
    ((segmentDensity[3][2] >= (MEAN_5_SEGMENT_DENSITY_3_2 - N_SD * SD_5_SEGMENT_DENSITY_3_2)) && (segmentDensity[3][2] <= (MEAN_5_SEGMENT_DENSITY_3_2 + N_SD * SD_5_SEGMENT_DENSITY_3_2))) &&
    ((segmentDensity[4][0] >= (MEAN_5_SEGMENT_DENSITY_4_0 - N_SD * SD_5_SEGMENT_DENSITY_4_0)) && (segmentDensity[4][0] <= (MEAN_5_SEGMENT_DENSITY_4_0 + N_SD * SD_5_SEGMENT_DENSITY_4_0))) &&
    ((segmentDensity[4][1] >= (MEAN_5_SEGMENT_DENSITY_4_1 - N_SD * SD_5_SEGMENT_DENSITY_4_1)) && (segmentDensity[4][1] <= (MEAN_5_SEGMENT_DENSITY_4_1 + N_SD * SD_5_SEGMENT_DENSITY_4_1))) &&
    ((segmentDensity[4][2] >= (MEAN_5_SEGMENT_DENSITY_4_2 - N_SD * SD_5_SEGMENT_DENSITY_4_2)) && (segmentDensity[4][2] <= (MEAN_5_SEGMENT_DENSITY_4_2 + N_SD * SD_5_SEGMENT_DENSITY_4_2))) &&
    ((yIncrements[0][0] >= (MEAN_5_Y_INCREMENT_0_0 - N_SD * SD_5_Y_INCREMENT_0_0)) && (yIncrements[0][0] <= (MEAN_5_Y_INCREMENT_0_0 + N_SD * SD_5_Y_INCREMENT_0_0))) && 
    ((xIncrements[0][0] >= (MEAN_5_X_INCREMENT_0_0 - N_SD * SD_5_X_INCREMENT_0_0)) && (xIncrements[0][0] <= (MEAN_5_X_INCREMENT_0_0 + N_SD * SD_5_X_INCREMENT_0_0))) &&
    ((yIncrements[0][1] >= (MEAN_5_Y_INCREMENT_0_1 - N_SD * SD_5_Y_INCREMENT_0_1)) && (yIncrements[0][1] <= (MEAN_5_Y_INCREMENT_0_1 + N_SD * SD_5_Y_INCREMENT_0_1))) && 
    ((xIncrements[0][1] >= (MEAN_5_X_INCREMENT_0_1 - N_SD * SD_5_X_INCREMENT_0_1)) && (xIncrements[0][1] <= (MEAN_5_X_INCREMENT_0_1 + N_SD * SD_5_X_INCREMENT_0_1))) &&
    ((yIncrements[0][2] >= (MEAN_5_Y_INCREMENT_0_2 - N_SD * SD_5_Y_INCREMENT_0_2)) && (yIncrements[0][2] <= (MEAN_5_Y_INCREMENT_0_2 + N_SD * SD_5_Y_INCREMENT_0_2))) && 
    ((xIncrements[0][2] >= (MEAN_5_X_INCREMENT_0_2 - N_SD * SD_5_X_INCREMENT_0_2)) && (xIncrements[0][2] <= (MEAN_5_X_INCREMENT_0_2 + N_SD * SD_5_X_INCREMENT_0_2))) &&
    ((yIncrements[1][0] >= (MEAN_5_Y_INCREMENT_1_0 - N_SD * SD_5_Y_INCREMENT_1_0)) && (yIncrements[1][0] <= (MEAN_5_Y_INCREMENT_1_0 + N_SD * SD_5_Y_INCREMENT_1_0))) && 
    ((xIncrements[1][0] >= (MEAN_5_X_INCREMENT_1_0 - N_SD * SD_5_X_INCREMENT_1_0)) && (xIncrements[1][0] <= (MEAN_5_X_INCREMENT_1_0 + N_SD * SD_5_X_INCREMENT_1_0))) &&
    ((yIncrements[1][1] >= (MEAN_5_Y_INCREMENT_1_1 - N_SD * SD_5_Y_INCREMENT_1_1)) && (yIncrements[1][1] <= (MEAN_5_Y_INCREMENT_1_1 + N_SD * SD_5_Y_INCREMENT_1_1))) && 
    ((xIncrements[1][1] >= (MEAN_5_X_INCREMENT_1_1 - N_SD * SD_5_X_INCREMENT_1_1)) && (xIncrements[1][1] <= (MEAN_5_X_INCREMENT_1_1 + N_SD * SD_5_X_INCREMENT_1_1))) &&
    ((yIncrements[1][2] >= (MEAN_5_Y_INCREMENT_1_2 - N_SD * SD_5_Y_INCREMENT_1_2)) && (yIncrements[1][2] <= (MEAN_5_Y_INCREMENT_1_2 + N_SD * SD_5_Y_INCREMENT_1_2))) && 
    ((xIncrements[1][2] >= (MEAN_5_X_INCREMENT_1_2 - N_SD * SD_5_X_INCREMENT_1_2)) && (xIncrements[1][2] <= (MEAN_5_X_INCREMENT_1_2 + N_SD * SD_5_X_INCREMENT_1_2))) &&
    ((yIncrements[2][0] >= (MEAN_5_Y_INCREMENT_2_0 - N_SD * SD_5_Y_INCREMENT_2_0)) && (yIncrements[2][0] <= (MEAN_5_Y_INCREMENT_2_0 + N_SD * SD_5_Y_INCREMENT_2_0))) && 
    ((xIncrements[2][0] >= (MEAN_5_X_INCREMENT_2_0 - N_SD * SD_5_X_INCREMENT_2_0)) && (xIncrements[2][0] <= (MEAN_5_X_INCREMENT_2_0 + N_SD * SD_5_X_INCREMENT_2_0))) &&
    ((yIncrements[2][1] >= (MEAN_5_Y_INCREMENT_2_1 - N_SD * SD_5_Y_INCREMENT_2_1)) && (yIncrements[2][1] <= (MEAN_5_Y_INCREMENT_2_1 + N_SD * SD_5_Y_INCREMENT_2_1))) && 
    ((xIncrements[2][1] >= (MEAN_5_X_INCREMENT_2_1 - N_SD * SD_5_X_INCREMENT_2_1)) && (xIncrements[2][1] <= (MEAN_5_X_INCREMENT_2_1 + N_SD * SD_5_X_INCREMENT_2_1))) &&
    ((yIncrements[2][2] >= (MEAN_5_Y_INCREMENT_2_2 - N_SD * SD_5_Y_INCREMENT_2_2)) && (yIncrements[2][2] <= (MEAN_5_Y_INCREMENT_2_2 + N_SD * SD_5_Y_INCREMENT_2_2))) && 
    ((xIncrements[2][2] >= (MEAN_5_X_INCREMENT_2_2 - N_SD * SD_5_X_INCREMENT_2_2)) && (xIncrements[2][2] <= (MEAN_5_X_INCREMENT_2_2 + N_SD * SD_5_X_INCREMENT_2_2)))) {
         printf ("5\n");
    }  else if (((horizontalBalance >= (MEAN_6_HORIZONTAL_BALANCE - N_SD * SD_6_HORIZONTAL_BALANCE)) && (horizontalBalance <= (MEAN_6_HORIZONTAL_BALANCE + N_SD * SD_6_HORIZONTAL_BALANCE))) && 
    ((verticalBalance >= (MEAN_6_VERTICAL_BALANCE - N_SD * SD_6_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_6_VERTICAL_BALANCE + N_SD * SD_6_VERTICAL_BALANCE))) && 
    ((tallness >= (MEAN_6_TALLNESS - N_SD * SD_6_TALLNESS)) && (tallness <= (MEAN_6_TALLNESS + N_SD * SD_6_TALLNESS))) && 
    ((density >= (MEAN_6_VERTICAL_BALANCE - N_SD * SD_6_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_6_VERTICAL_BALANCE + N_SD * SD_6_VERTICAL_BALANCE))) && 
    ((segmentDensity[0][0] >= (MEAN_6_SEGMENT_DENSITY_0_0 - N_SD * SD_6_SEGMENT_DENSITY_0_0)) && (segmentDensity[0][0] <= (MEAN_6_SEGMENT_DENSITY_0_0 + N_SD * SD_6_SEGMENT_DENSITY_0_0))) &&
    ((segmentDensity[0][1] >= (MEAN_6_SEGMENT_DENSITY_0_1 - N_SD * SD_6_SEGMENT_DENSITY_0_1)) && (segmentDensity[0][1] <= (MEAN_6_SEGMENT_DENSITY_0_1 + N_SD * SD_6_SEGMENT_DENSITY_0_1))) &&
    ((segmentDensity[0][2] >= (MEAN_6_SEGMENT_DENSITY_0_2 - N_SD * SD_6_SEGMENT_DENSITY_0_2)) && (segmentDensity[0][2] <= (MEAN_6_SEGMENT_DENSITY_0_2 + N_SD * SD_6_SEGMENT_DENSITY_0_2))) &&
    ((segmentDensity[1][0] >= (MEAN_6_SEGMENT_DENSITY_1_0 - N_SD * SD_6_SEGMENT_DENSITY_1_0)) && (segmentDensity[1][0] <= (MEAN_6_SEGMENT_DENSITY_1_0 + N_SD * SD_6_SEGMENT_DENSITY_1_0))) &&
    ((segmentDensity[1][1] >= (MEAN_6_SEGMENT_DENSITY_1_1 - N_SD * SD_6_SEGMENT_DENSITY_1_1)) && (segmentDensity[1][1] <= (MEAN_6_SEGMENT_DENSITY_1_1 + N_SD * SD_6_SEGMENT_DENSITY_1_1))) &&
    ((segmentDensity[1][2] >= (MEAN_6_SEGMENT_DENSITY_1_2 - N_SD * SD_6_SEGMENT_DENSITY_1_2)) && (segmentDensity[1][2] <= (MEAN_6_SEGMENT_DENSITY_1_2 + N_SD * SD_6_SEGMENT_DENSITY_1_2))) &&
    ((segmentDensity[2][0] >= (MEAN_6_SEGMENT_DENSITY_2_0 - N_SD * SD_6_SEGMENT_DENSITY_2_0)) && (segmentDensity[2][0] <= (MEAN_6_SEGMENT_DENSITY_2_0 + N_SD * SD_6_SEGMENT_DENSITY_2_0))) &&
    ((segmentDensity[2][1] >= (MEAN_6_SEGMENT_DENSITY_2_1 - N_SD * SD_6_SEGMENT_DENSITY_2_1)) && (segmentDensity[2][1] <= (MEAN_6_SEGMENT_DENSITY_2_1 + N_SD * SD_6_SEGMENT_DENSITY_2_1))) &&
    ((segmentDensity[2][2] >= (MEAN_6_SEGMENT_DENSITY_2_2 - N_SD * SD_6_SEGMENT_DENSITY_2_2)) && (segmentDensity[2][2] <= (MEAN_6_SEGMENT_DENSITY_2_2 + N_SD * SD_6_SEGMENT_DENSITY_2_2))) &&
    ((segmentDensity[3][0] >= (MEAN_6_SEGMENT_DENSITY_3_0 - N_SD * SD_6_SEGMENT_DENSITY_3_0)) && (segmentDensity[3][0] <= (MEAN_6_SEGMENT_DENSITY_3_0 + N_SD * SD_6_SEGMENT_DENSITY_3_0))) &&
    ((segmentDensity[3][1] >= (MEAN_6_SEGMENT_DENSITY_3_1 - N_SD * SD_6_SEGMENT_DENSITY_3_1)) && (segmentDensity[3][1] <= (MEAN_6_SEGMENT_DENSITY_3_1 + N_SD * SD_6_SEGMENT_DENSITY_3_1))) &&
    ((segmentDensity[3][2] >= (MEAN_6_SEGMENT_DENSITY_3_2 - N_SD * SD_6_SEGMENT_DENSITY_3_2)) && (segmentDensity[3][2] <= (MEAN_6_SEGMENT_DENSITY_3_2 + N_SD * SD_6_SEGMENT_DENSITY_3_2))) &&
    ((segmentDensity[4][0] >= (MEAN_6_SEGMENT_DENSITY_4_0 - N_SD * SD_6_SEGMENT_DENSITY_4_0)) && (segmentDensity[4][0] <= (MEAN_6_SEGMENT_DENSITY_4_0 + N_SD * SD_6_SEGMENT_DENSITY_4_0))) &&
    ((segmentDensity[4][1] >= (MEAN_6_SEGMENT_DENSITY_4_1 - N_SD * SD_6_SEGMENT_DENSITY_4_1)) && (segmentDensity[4][1] <= (MEAN_6_SEGMENT_DENSITY_4_1 + N_SD * SD_6_SEGMENT_DENSITY_4_1))) &&
    ((segmentDensity[4][2] >= (MEAN_6_SEGMENT_DENSITY_4_2 - N_SD * SD_6_SEGMENT_DENSITY_4_2)) && (segmentDensity[4][2] <= (MEAN_6_SEGMENT_DENSITY_4_2 + N_SD * SD_6_SEGMENT_DENSITY_4_2))) &&
    ((yIncrements[0][0] >= (MEAN_6_Y_INCREMENT_0_0 - N_SD * SD_6_Y_INCREMENT_0_0)) && (yIncrements[0][0] <= (MEAN_6_Y_INCREMENT_0_0 + N_SD * SD_6_Y_INCREMENT_0_0))) && 
    ((xIncrements[0][0] >= (MEAN_6_X_INCREMENT_0_0 - N_SD * SD_6_X_INCREMENT_0_0)) && (xIncrements[0][0] <= (MEAN_6_X_INCREMENT_0_0 + N_SD * SD_6_X_INCREMENT_0_0))) &&
    ((yIncrements[0][1] >= (MEAN_6_Y_INCREMENT_0_1 - N_SD * SD_6_Y_INCREMENT_0_1)) && (yIncrements[0][1] <= (MEAN_6_Y_INCREMENT_0_1 + N_SD * SD_6_Y_INCREMENT_0_1))) && 
    ((xIncrements[0][1] >= (MEAN_6_X_INCREMENT_0_1 - N_SD * SD_6_X_INCREMENT_0_1)) && (xIncrements[0][1] <= (MEAN_6_X_INCREMENT_0_1 + N_SD * SD_6_X_INCREMENT_0_1))) &&
    ((yIncrements[0][2] >= (MEAN_6_Y_INCREMENT_0_2 - N_SD * SD_6_Y_INCREMENT_0_2)) && (yIncrements[0][2] <= (MEAN_6_Y_INCREMENT_0_2 + N_SD * SD_6_Y_INCREMENT_0_2))) && 
    ((xIncrements[0][2] >= (MEAN_6_X_INCREMENT_0_2 - N_SD * SD_6_X_INCREMENT_0_2)) && (xIncrements[0][2] <= (MEAN_6_X_INCREMENT_0_2 + N_SD * SD_6_X_INCREMENT_0_2))) &&
    ((yIncrements[1][0] >= (MEAN_6_Y_INCREMENT_1_0 - N_SD * SD_6_Y_INCREMENT_1_0)) && (yIncrements[1][0] <= (MEAN_6_Y_INCREMENT_1_0 + N_SD * SD_6_Y_INCREMENT_1_0))) && 
    ((xIncrements[1][0] >= (MEAN_6_X_INCREMENT_1_0 - N_SD * SD_6_X_INCREMENT_1_0)) && (xIncrements[1][0] <= (MEAN_6_X_INCREMENT_1_0 + N_SD * SD_6_X_INCREMENT_1_0))) &&
    ((yIncrements[1][1] >= (MEAN_6_Y_INCREMENT_1_1 - N_SD * SD_6_Y_INCREMENT_1_1)) && (yIncrements[1][1] <= (MEAN_6_Y_INCREMENT_1_1 + N_SD * SD_6_Y_INCREMENT_1_1))) && 
    ((xIncrements[1][1] >= (MEAN_6_X_INCREMENT_1_1 - N_SD * SD_6_X_INCREMENT_1_1)) && (xIncrements[1][1] <= (MEAN_6_X_INCREMENT_1_1 + N_SD * SD_6_X_INCREMENT_1_1))) &&
    ((yIncrements[1][2] >= (MEAN_6_Y_INCREMENT_1_2 - N_SD * SD_6_Y_INCREMENT_1_2)) && (yIncrements[1][2] <= (MEAN_6_Y_INCREMENT_1_2 + N_SD * SD_6_Y_INCREMENT_1_2))) && 
    ((xIncrements[1][2] >= (MEAN_6_X_INCREMENT_1_2 - N_SD * SD_6_X_INCREMENT_1_2)) && (xIncrements[1][2] <= (MEAN_6_X_INCREMENT_1_2 + N_SD * SD_6_X_INCREMENT_1_2))) &&
    ((yIncrements[2][0] >= (MEAN_6_Y_INCREMENT_2_0 - N_SD * SD_6_Y_INCREMENT_2_0)) && (yIncrements[2][0] <= (MEAN_6_Y_INCREMENT_2_0 + N_SD * SD_6_Y_INCREMENT_2_0))) && 
    ((xIncrements[2][0] >= (MEAN_6_X_INCREMENT_2_0 - N_SD * SD_6_X_INCREMENT_2_0)) && (xIncrements[2][0] <= (MEAN_6_X_INCREMENT_2_0 + N_SD * SD_6_X_INCREMENT_2_0))) &&
    ((yIncrements[2][1] >= (MEAN_6_Y_INCREMENT_2_1 - N_SD * SD_6_Y_INCREMENT_2_1)) && (yIncrements[2][1] <= (MEAN_6_Y_INCREMENT_2_1 + N_SD * SD_6_Y_INCREMENT_2_1))) && 
    ((xIncrements[2][1] >= (MEAN_6_X_INCREMENT_2_1 - N_SD * SD_6_X_INCREMENT_2_1)) && (xIncrements[2][1] <= (MEAN_6_X_INCREMENT_2_1 + N_SD * SD_6_X_INCREMENT_2_1))) &&
    ((yIncrements[2][2] >= (MEAN_6_Y_INCREMENT_2_2 - N_SD * SD_6_Y_INCREMENT_2_2)) && (yIncrements[2][2] <= (MEAN_6_Y_INCREMENT_2_2 + N_SD * SD_6_Y_INCREMENT_2_2))) && 
    ((xIncrements[2][2] >= (MEAN_6_X_INCREMENT_2_2 - N_SD * SD_6_X_INCREMENT_2_2)) && (xIncrements[2][2] <= (MEAN_6_X_INCREMENT_2_2 + N_SD * SD_6_X_INCREMENT_2_2)))) {
        printf ("6\n");
    }  else if (((horizontalBalance >= (MEAN_7_HORIZONTAL_BALANCE - N_SD * SD_7_HORIZONTAL_BALANCE)) && (horizontalBalance <= (MEAN_7_HORIZONTAL_BALANCE + N_SD * SD_7_HORIZONTAL_BALANCE))) && 
    ((verticalBalance >= (MEAN_7_VERTICAL_BALANCE - N_SD * SD_7_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_7_VERTICAL_BALANCE + N_SD * SD_7_VERTICAL_BALANCE))) && 
    ((tallness >= (MEAN_7_TALLNESS - N_SD * SD_7_TALLNESS)) && (tallness <= (MEAN_7_TALLNESS + N_SD * SD_7_TALLNESS))) && 
    ((density >= (MEAN_7_VERTICAL_BALANCE - N_SD * SD_7_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_7_VERTICAL_BALANCE + N_SD * SD_7_VERTICAL_BALANCE))) && 
    ((segmentDensity[0][0] >= (MEAN_7_SEGMENT_DENSITY_0_0 - N_SD * SD_7_SEGMENT_DENSITY_0_0)) && (segmentDensity[0][0] <= (MEAN_7_SEGMENT_DENSITY_0_0 + N_SD * SD_7_SEGMENT_DENSITY_0_0))) &&
    ((segmentDensity[0][1] >= (MEAN_7_SEGMENT_DENSITY_0_1 - N_SD * SD_7_SEGMENT_DENSITY_0_1)) && (segmentDensity[0][1] <= (MEAN_7_SEGMENT_DENSITY_0_1 + N_SD * SD_7_SEGMENT_DENSITY_0_1))) &&
    ((segmentDensity[0][2] >= (MEAN_7_SEGMENT_DENSITY_0_2 - N_SD * SD_7_SEGMENT_DENSITY_0_2)) && (segmentDensity[0][2] <= (MEAN_7_SEGMENT_DENSITY_0_2 + N_SD * SD_7_SEGMENT_DENSITY_0_2))) &&
    ((segmentDensity[1][0] >= (MEAN_7_SEGMENT_DENSITY_1_0 - N_SD * SD_7_SEGMENT_DENSITY_1_0)) && (segmentDensity[1][0] <= (MEAN_7_SEGMENT_DENSITY_1_0 + N_SD * SD_7_SEGMENT_DENSITY_1_0))) &&
    ((segmentDensity[1][1] >= (MEAN_7_SEGMENT_DENSITY_1_1 - N_SD * SD_7_SEGMENT_DENSITY_1_1)) && (segmentDensity[1][1] <= (MEAN_7_SEGMENT_DENSITY_1_1 + N_SD * SD_7_SEGMENT_DENSITY_1_1))) &&
    ((segmentDensity[1][2] >= (MEAN_7_SEGMENT_DENSITY_1_2 - N_SD * SD_7_SEGMENT_DENSITY_1_2)) && (segmentDensity[1][2] <= (MEAN_7_SEGMENT_DENSITY_1_2 + N_SD * SD_7_SEGMENT_DENSITY_1_2))) &&
    ((segmentDensity[2][0] >= (MEAN_7_SEGMENT_DENSITY_2_0 - N_SD * SD_7_SEGMENT_DENSITY_2_0)) && (segmentDensity[2][0] <= (MEAN_7_SEGMENT_DENSITY_2_0 + N_SD * SD_7_SEGMENT_DENSITY_2_0))) &&
    ((segmentDensity[2][1] >= (MEAN_7_SEGMENT_DENSITY_2_1 - N_SD * SD_7_SEGMENT_DENSITY_2_1)) && (segmentDensity[2][1] <= (MEAN_7_SEGMENT_DENSITY_2_1 + N_SD * SD_7_SEGMENT_DENSITY_2_1))) &&
    ((segmentDensity[2][2] >= (MEAN_7_SEGMENT_DENSITY_2_2 - N_SD * SD_7_SEGMENT_DENSITY_2_2)) && (segmentDensity[2][2] <= (MEAN_7_SEGMENT_DENSITY_2_2 + N_SD * SD_7_SEGMENT_DENSITY_2_2))) &&
    ((segmentDensity[3][0] >= (MEAN_7_SEGMENT_DENSITY_3_0 - N_SD * SD_7_SEGMENT_DENSITY_3_0)) && (segmentDensity[3][0] <= (MEAN_7_SEGMENT_DENSITY_3_0 + N_SD * SD_7_SEGMENT_DENSITY_3_0))) &&
    ((segmentDensity[3][1] >= (MEAN_7_SEGMENT_DENSITY_3_1 - N_SD * SD_7_SEGMENT_DENSITY_3_1)) && (segmentDensity[3][1] <= (MEAN_7_SEGMENT_DENSITY_3_1 + N_SD * SD_7_SEGMENT_DENSITY_3_1))) &&
    ((segmentDensity[3][2] >= (MEAN_7_SEGMENT_DENSITY_3_2 - N_SD * SD_7_SEGMENT_DENSITY_3_2)) && (segmentDensity[3][2] <= (MEAN_7_SEGMENT_DENSITY_3_2 + N_SD * SD_7_SEGMENT_DENSITY_3_2))) &&
    ((segmentDensity[4][0] >= (MEAN_7_SEGMENT_DENSITY_4_0 - N_SD * SD_7_SEGMENT_DENSITY_4_0)) && (segmentDensity[4][0] <= (MEAN_7_SEGMENT_DENSITY_4_0 + N_SD * SD_7_SEGMENT_DENSITY_4_0))) &&
    ((segmentDensity[4][1] >= (MEAN_7_SEGMENT_DENSITY_4_1 - N_SD * SD_7_SEGMENT_DENSITY_4_1)) && (segmentDensity[4][1] <= (MEAN_7_SEGMENT_DENSITY_4_1 + N_SD * SD_7_SEGMENT_DENSITY_4_1))) &&
    ((segmentDensity[4][2] >= (MEAN_7_SEGMENT_DENSITY_4_2 - N_SD * SD_7_SEGMENT_DENSITY_4_2)) && (segmentDensity[4][2] <= (MEAN_7_SEGMENT_DENSITY_4_2 + N_SD * SD_7_SEGMENT_DENSITY_4_2))) &&
    ((yIncrements[0][0] >= (MEAN_7_Y_INCREMENT_0_0 - N_SD * SD_7_Y_INCREMENT_0_0)) && (yIncrements[0][0] <= (MEAN_7_Y_INCREMENT_0_0 + N_SD * SD_7_Y_INCREMENT_0_0))) && 
    ((xIncrements[0][0] >= (MEAN_7_X_INCREMENT_0_0 - N_SD * SD_7_X_INCREMENT_0_0)) && (xIncrements[0][0] <= (MEAN_7_X_INCREMENT_0_0 + N_SD * SD_7_X_INCREMENT_0_0))) &&
    ((yIncrements[0][1] >= (MEAN_7_Y_INCREMENT_0_1 - N_SD * SD_7_Y_INCREMENT_0_1)) && (yIncrements[0][1] <= (MEAN_7_Y_INCREMENT_0_1 + N_SD * SD_7_Y_INCREMENT_0_1))) && 
    ((xIncrements[0][1] >= (MEAN_7_X_INCREMENT_0_1 - N_SD * SD_7_X_INCREMENT_0_1)) && (xIncrements[0][1] <= (MEAN_7_X_INCREMENT_0_1 + N_SD * SD_7_X_INCREMENT_0_1))) &&
    ((yIncrements[0][2] >= (MEAN_7_Y_INCREMENT_0_2 - N_SD * SD_7_Y_INCREMENT_0_2)) && (yIncrements[0][2] <= (MEAN_7_Y_INCREMENT_0_2 + N_SD * SD_7_Y_INCREMENT_0_2))) && 
    ((xIncrements[0][2] >= (MEAN_7_X_INCREMENT_0_2 - N_SD * SD_7_X_INCREMENT_0_2)) && (xIncrements[0][2] <= (MEAN_7_X_INCREMENT_0_2 + N_SD * SD_7_X_INCREMENT_0_2))) &&
    ((yIncrements[1][0] >= (MEAN_7_Y_INCREMENT_1_0 - N_SD * SD_7_Y_INCREMENT_1_0)) && (yIncrements[1][0] <= (MEAN_7_Y_INCREMENT_1_0 + N_SD * SD_7_Y_INCREMENT_1_0))) && 
    ((xIncrements[1][0] >= (MEAN_7_X_INCREMENT_1_0 - N_SD * SD_7_X_INCREMENT_1_0)) && (xIncrements[1][0] <= (MEAN_7_X_INCREMENT_1_0 + N_SD * SD_7_X_INCREMENT_1_0))) &&
    ((yIncrements[1][1] >= (MEAN_7_Y_INCREMENT_1_1 - N_SD * SD_7_Y_INCREMENT_1_1)) && (yIncrements[1][1] <= (MEAN_7_Y_INCREMENT_1_1 + N_SD * SD_7_Y_INCREMENT_1_1))) && 
    ((xIncrements[1][1] >= (MEAN_7_X_INCREMENT_1_1 - N_SD * SD_7_X_INCREMENT_1_1)) && (xIncrements[1][1] <= (MEAN_7_X_INCREMENT_1_1 + N_SD * SD_7_X_INCREMENT_1_1))) &&
    ((yIncrements[1][2] >= (MEAN_7_Y_INCREMENT_1_2 - N_SD * SD_7_Y_INCREMENT_1_2)) && (yIncrements[1][2] <= (MEAN_7_Y_INCREMENT_1_2 + N_SD * SD_7_Y_INCREMENT_1_2))) && 
    ((xIncrements[1][2] >= (MEAN_7_X_INCREMENT_1_2 - N_SD * SD_7_X_INCREMENT_1_2)) && (xIncrements[1][2] <= (MEAN_7_X_INCREMENT_1_2 + N_SD * SD_7_X_INCREMENT_1_2))) &&
    ((yIncrements[2][0] >= (MEAN_7_Y_INCREMENT_2_0 - N_SD * SD_7_Y_INCREMENT_2_0)) && (yIncrements[2][0] <= (MEAN_7_Y_INCREMENT_2_0 + N_SD * SD_7_Y_INCREMENT_2_0))) && 
    ((xIncrements[2][0] >= (MEAN_7_X_INCREMENT_2_0 - N_SD * SD_7_X_INCREMENT_2_0)) && (xIncrements[2][0] <= (MEAN_7_X_INCREMENT_2_0 + N_SD * SD_7_X_INCREMENT_2_0))) &&
    ((yIncrements[2][1] >= (MEAN_7_Y_INCREMENT_2_1 - N_SD * SD_7_Y_INCREMENT_2_1)) && (yIncrements[2][1] <= (MEAN_7_Y_INCREMENT_2_1 + N_SD * SD_7_Y_INCREMENT_2_1))) && 
    ((xIncrements[2][1] >= (MEAN_7_X_INCREMENT_2_1 - N_SD * SD_7_X_INCREMENT_2_1)) && (xIncrements[2][1] <= (MEAN_7_X_INCREMENT_2_1 + N_SD * SD_7_X_INCREMENT_2_1))) &&
    ((yIncrements[2][2] >= (MEAN_7_Y_INCREMENT_2_2 - N_SD * SD_7_Y_INCREMENT_2_2)) && (yIncrements[2][2] <= (MEAN_7_Y_INCREMENT_2_2 + N_SD * SD_7_Y_INCREMENT_2_2))) && 
    ((xIncrements[2][2] >= (MEAN_7_X_INCREMENT_2_2 - N_SD * SD_7_X_INCREMENT_2_2)) && (xIncrements[2][2] <= (MEAN_7_X_INCREMENT_2_2 + N_SD * SD_7_X_INCREMENT_2_2)))) {
        printf ("8\n");
    }  else if (((horizontalBalance >= (MEAN_8_HORIZONTAL_BALANCE - N_SD * SD_8_HORIZONTAL_BALANCE)) && (horizontalBalance <= (MEAN_8_HORIZONTAL_BALANCE + N_SD * SD_8_HORIZONTAL_BALANCE))) && 
    ((verticalBalance >= (MEAN_8_VERTICAL_BALANCE - N_SD * SD_8_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_8_VERTICAL_BALANCE + N_SD * SD_8_VERTICAL_BALANCE))) && 
    ((tallness >= (MEAN_8_TALLNESS - N_SD * SD_8_TALLNESS)) && (tallness <= (MEAN_8_TALLNESS + N_SD * SD_8_TALLNESS))) && 
    ((density >= (MEAN_8_VERTICAL_BALANCE - N_SD * SD_8_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_8_VERTICAL_BALANCE + N_SD * SD_8_VERTICAL_BALANCE))) && 
    ((segmentDensity[0][0] >= (MEAN_8_SEGMENT_DENSITY_0_0 - N_SD * SD_8_SEGMENT_DENSITY_0_0)) && (segmentDensity[0][0] <= (MEAN_8_SEGMENT_DENSITY_0_0 + N_SD * SD_8_SEGMENT_DENSITY_0_0))) &&
    ((segmentDensity[0][1] >= (MEAN_8_SEGMENT_DENSITY_0_1 - N_SD * SD_8_SEGMENT_DENSITY_0_1)) && (segmentDensity[0][1] <= (MEAN_8_SEGMENT_DENSITY_0_1 + N_SD * SD_8_SEGMENT_DENSITY_0_1))) &&
    ((segmentDensity[0][2] >= (MEAN_8_SEGMENT_DENSITY_0_2 - N_SD * SD_8_SEGMENT_DENSITY_0_2)) && (segmentDensity[0][2] <= (MEAN_8_SEGMENT_DENSITY_0_2 + N_SD * SD_8_SEGMENT_DENSITY_0_2))) &&
    ((segmentDensity[1][0] >= (MEAN_8_SEGMENT_DENSITY_1_0 - N_SD * SD_8_SEGMENT_DENSITY_1_0)) && (segmentDensity[1][0] <= (MEAN_8_SEGMENT_DENSITY_1_0 + N_SD * SD_8_SEGMENT_DENSITY_1_0))) &&
    ((segmentDensity[1][1] >= (MEAN_8_SEGMENT_DENSITY_1_1 - N_SD * SD_8_SEGMENT_DENSITY_1_1)) && (segmentDensity[1][1] <= (MEAN_8_SEGMENT_DENSITY_1_1 + N_SD * SD_8_SEGMENT_DENSITY_1_1))) &&
    ((segmentDensity[1][2] >= (MEAN_8_SEGMENT_DENSITY_1_2 - N_SD * SD_8_SEGMENT_DENSITY_1_2)) && (segmentDensity[1][2] <= (MEAN_8_SEGMENT_DENSITY_1_2 + N_SD * SD_8_SEGMENT_DENSITY_1_2))) &&
    ((segmentDensity[2][0] >= (MEAN_8_SEGMENT_DENSITY_2_0 - N_SD * SD_8_SEGMENT_DENSITY_2_0)) && (segmentDensity[2][0] <= (MEAN_8_SEGMENT_DENSITY_2_0 + N_SD * SD_8_SEGMENT_DENSITY_2_0))) &&
    ((segmentDensity[2][1] >= (MEAN_8_SEGMENT_DENSITY_2_1 - N_SD * SD_8_SEGMENT_DENSITY_2_1)) && (segmentDensity[2][1] <= (MEAN_8_SEGMENT_DENSITY_2_1 + N_SD * SD_8_SEGMENT_DENSITY_2_1))) &&
    ((segmentDensity[2][2] >= (MEAN_8_SEGMENT_DENSITY_2_2 - N_SD * SD_8_SEGMENT_DENSITY_2_2)) && (segmentDensity[2][2] <= (MEAN_8_SEGMENT_DENSITY_2_2 + N_SD * SD_8_SEGMENT_DENSITY_2_2))) &&
    ((segmentDensity[3][0] >= (MEAN_8_SEGMENT_DENSITY_3_0 - N_SD * SD_8_SEGMENT_DENSITY_3_0)) && (segmentDensity[3][0] <= (MEAN_8_SEGMENT_DENSITY_3_0 + N_SD * SD_8_SEGMENT_DENSITY_3_0))) &&
    ((segmentDensity[3][1] >= (MEAN_8_SEGMENT_DENSITY_3_1 - N_SD * SD_8_SEGMENT_DENSITY_3_1)) && (segmentDensity[3][1] <= (MEAN_8_SEGMENT_DENSITY_3_1 + N_SD * SD_8_SEGMENT_DENSITY_3_1))) &&
    ((segmentDensity[3][2] >= (MEAN_8_SEGMENT_DENSITY_3_2 - N_SD * SD_8_SEGMENT_DENSITY_3_2)) && (segmentDensity[3][2] <= (MEAN_8_SEGMENT_DENSITY_3_2 + N_SD * SD_8_SEGMENT_DENSITY_3_2))) &&
    ((segmentDensity[4][0] >= (MEAN_8_SEGMENT_DENSITY_4_0 - N_SD * SD_8_SEGMENT_DENSITY_4_0)) && (segmentDensity[4][0] <= (MEAN_8_SEGMENT_DENSITY_4_0 + N_SD * SD_8_SEGMENT_DENSITY_4_0))) &&
    ((segmentDensity[4][1] >= (MEAN_8_SEGMENT_DENSITY_4_1 - N_SD * SD_8_SEGMENT_DENSITY_4_1)) && (segmentDensity[4][1] <= (MEAN_8_SEGMENT_DENSITY_4_1 + N_SD * SD_8_SEGMENT_DENSITY_4_1))) &&
    ((segmentDensity[4][2] >= (MEAN_8_SEGMENT_DENSITY_4_2 - N_SD * SD_8_SEGMENT_DENSITY_4_2)) && (segmentDensity[4][2] <= (MEAN_8_SEGMENT_DENSITY_4_2 + N_SD * SD_8_SEGMENT_DENSITY_4_2))) &&
    ((yIncrements[0][0] >= (MEAN_8_Y_INCREMENT_0_0 - N_SD * SD_8_Y_INCREMENT_0_0)) && (yIncrements[0][0] <= (MEAN_8_Y_INCREMENT_0_0 + N_SD * SD_8_Y_INCREMENT_0_0))) && 
    ((xIncrements[0][0] >= (MEAN_8_X_INCREMENT_0_0 - N_SD * SD_8_X_INCREMENT_0_0)) && (xIncrements[0][0] <= (MEAN_8_X_INCREMENT_0_0 + N_SD * SD_8_X_INCREMENT_0_0))) &&
    ((yIncrements[0][1] >= (MEAN_8_Y_INCREMENT_0_1 - N_SD * SD_8_Y_INCREMENT_0_1)) && (yIncrements[0][1] <= (MEAN_8_Y_INCREMENT_0_1 + N_SD * SD_8_Y_INCREMENT_0_1))) && 
    ((xIncrements[0][1] >= (MEAN_8_X_INCREMENT_0_1 - N_SD * SD_8_X_INCREMENT_0_1)) && (xIncrements[0][1] <= (MEAN_8_X_INCREMENT_0_1 + N_SD * SD_8_X_INCREMENT_0_1))) &&
    ((yIncrements[0][2] >= (MEAN_8_Y_INCREMENT_0_2 - N_SD * SD_8_Y_INCREMENT_0_2)) && (yIncrements[0][2] <= (MEAN_8_Y_INCREMENT_0_2 + N_SD * SD_8_Y_INCREMENT_0_2))) && 
    ((xIncrements[0][2] >= (MEAN_8_X_INCREMENT_0_2 - N_SD * SD_8_X_INCREMENT_0_2)) && (xIncrements[0][2] <= (MEAN_8_X_INCREMENT_0_2 + N_SD * SD_8_X_INCREMENT_0_2))) &&
    ((yIncrements[1][0] >= (MEAN_8_Y_INCREMENT_1_0 - N_SD * SD_8_Y_INCREMENT_1_0)) && (yIncrements[1][0] <= (MEAN_8_Y_INCREMENT_1_0 + N_SD * SD_8_Y_INCREMENT_1_0))) && 
    ((xIncrements[1][0] >= (MEAN_8_X_INCREMENT_1_0 - N_SD * SD_8_X_INCREMENT_1_0)) && (xIncrements[1][0] <= (MEAN_8_X_INCREMENT_1_0 + N_SD * SD_8_X_INCREMENT_1_0))) &&
    ((yIncrements[1][1] >= (MEAN_8_Y_INCREMENT_1_1 - N_SD * SD_8_Y_INCREMENT_1_1)) && (yIncrements[1][1] <= (MEAN_8_Y_INCREMENT_1_1 + N_SD * SD_8_Y_INCREMENT_1_1))) && 
    ((xIncrements[1][1] >= (MEAN_8_X_INCREMENT_1_1 - N_SD * SD_8_X_INCREMENT_1_1)) && (xIncrements[1][1] <= (MEAN_8_X_INCREMENT_1_1 + N_SD * SD_8_X_INCREMENT_1_1))) &&
    ((yIncrements[1][2] >= (MEAN_8_Y_INCREMENT_1_2 - N_SD * SD_8_Y_INCREMENT_1_2)) && (yIncrements[1][2] <= (MEAN_8_Y_INCREMENT_1_2 + N_SD * SD_8_Y_INCREMENT_1_2))) && 
    ((xIncrements[1][2] >= (MEAN_8_X_INCREMENT_1_2 - N_SD * SD_8_X_INCREMENT_1_2)) && (xIncrements[1][2] <= (MEAN_8_X_INCREMENT_1_2 + N_SD * SD_8_X_INCREMENT_1_2))) &&
    ((yIncrements[2][0] >= (MEAN_8_Y_INCREMENT_2_0 - N_SD * SD_8_Y_INCREMENT_2_0)) && (yIncrements[2][0] <= (MEAN_8_Y_INCREMENT_2_0 + N_SD * SD_8_Y_INCREMENT_2_0))) && 
    ((xIncrements[2][0] >= (MEAN_8_X_INCREMENT_2_0 - N_SD * SD_8_X_INCREMENT_2_0)) && (xIncrements[2][0] <= (MEAN_8_X_INCREMENT_2_0 + N_SD * SD_8_X_INCREMENT_2_0))) &&
    ((yIncrements[2][1] >= (MEAN_8_Y_INCREMENT_2_1 - N_SD * SD_8_Y_INCREMENT_2_1)) && (yIncrements[2][1] <= (MEAN_8_Y_INCREMENT_2_1 + N_SD * SD_8_Y_INCREMENT_2_1))) && 
    ((xIncrements[2][1] >= (MEAN_8_X_INCREMENT_2_1 - N_SD * SD_8_X_INCREMENT_2_1)) && (xIncrements[2][1] <= (MEAN_8_X_INCREMENT_2_1 + N_SD * SD_8_X_INCREMENT_2_1))) &&
    ((yIncrements[2][2] >= (MEAN_8_Y_INCREMENT_2_2 - N_SD * SD_8_Y_INCREMENT_2_2)) && (yIncrements[2][2] <= (MEAN_8_Y_INCREMENT_2_2 + N_SD * SD_8_Y_INCREMENT_2_2))) && 
    ((xIncrements[2][2] >= (MEAN_8_X_INCREMENT_2_2 - N_SD * SD_8_X_INCREMENT_2_2)) && (xIncrements[2][2] <= (MEAN_8_X_INCREMENT_2_2 + N_SD * SD_8_X_INCREMENT_2_2)))) {
         printf ("9\n");
    }  else if (((horizontalBalance >= (MEAN_9_HORIZONTAL_BALANCE - N_SD * SD_9_HORIZONTAL_BALANCE)) && (horizontalBalance <= (MEAN_9_HORIZONTAL_BALANCE + N_SD * SD_9_HORIZONTAL_BALANCE))) && 
    ((verticalBalance >= (MEAN_9_VERTICAL_BALANCE - N_SD * SD_9_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_9_VERTICAL_BALANCE + N_SD * SD_9_VERTICAL_BALANCE))) && 
    ((tallness >= (MEAN_9_TALLNESS - N_SD * SD_9_TALLNESS)) && (tallness <= (MEAN_9_TALLNESS + N_SD * SD_9_TALLNESS))) && 
    ((density >= (MEAN_9_VERTICAL_BALANCE - N_SD * SD_9_VERTICAL_BALANCE)) && (verticalBalance <= (MEAN_9_VERTICAL_BALANCE + N_SD * SD_9_VERTICAL_BALANCE))) && 
    ((segmentDensity[0][0] >= (MEAN_9_SEGMENT_DENSITY_0_0 - N_SD * SD_9_SEGMENT_DENSITY_0_0)) && (segmentDensity[0][0] <= (MEAN_9_SEGMENT_DENSITY_0_0 + N_SD * SD_9_SEGMENT_DENSITY_0_0))) &&
    ((segmentDensity[0][1] >= (MEAN_9_SEGMENT_DENSITY_0_1 - N_SD * SD_9_SEGMENT_DENSITY_0_1)) && (segmentDensity[0][1] <= (MEAN_9_SEGMENT_DENSITY_0_1 + N_SD * SD_9_SEGMENT_DENSITY_0_1))) &&
    ((segmentDensity[0][2] >= (MEAN_9_SEGMENT_DENSITY_0_2 - N_SD * SD_9_SEGMENT_DENSITY_0_2)) && (segmentDensity[0][2] <= (MEAN_9_SEGMENT_DENSITY_0_2 + N_SD * SD_9_SEGMENT_DENSITY_0_2))) &&
    ((segmentDensity[1][0] >= (MEAN_9_SEGMENT_DENSITY_1_0 - N_SD * SD_9_SEGMENT_DENSITY_1_0)) && (segmentDensity[1][0] <= (MEAN_9_SEGMENT_DENSITY_1_0 + N_SD * SD_9_SEGMENT_DENSITY_1_0))) &&
    ((segmentDensity[1][1] >= (MEAN_9_SEGMENT_DENSITY_1_1 - N_SD * SD_9_SEGMENT_DENSITY_1_1)) && (segmentDensity[1][1] <= (MEAN_9_SEGMENT_DENSITY_1_1 + N_SD * SD_9_SEGMENT_DENSITY_1_1))) &&
    ((segmentDensity[1][2] >= (MEAN_9_SEGMENT_DENSITY_1_2 - N_SD * SD_9_SEGMENT_DENSITY_1_2)) && (segmentDensity[1][2] <= (MEAN_9_SEGMENT_DENSITY_1_2 + N_SD * SD_9_SEGMENT_DENSITY_1_2))) &&
    ((segmentDensity[2][0] >= (MEAN_9_SEGMENT_DENSITY_2_0 - N_SD * SD_9_SEGMENT_DENSITY_2_0)) && (segmentDensity[2][0] <= (MEAN_9_SEGMENT_DENSITY_2_0 + N_SD * SD_9_SEGMENT_DENSITY_2_0))) &&
    ((segmentDensity[2][1] >= (MEAN_9_SEGMENT_DENSITY_2_1 - N_SD * SD_9_SEGMENT_DENSITY_2_1)) && (segmentDensity[2][1] <= (MEAN_9_SEGMENT_DENSITY_2_1 + N_SD * SD_9_SEGMENT_DENSITY_2_1))) &&
    ((segmentDensity[2][2] >= (MEAN_9_SEGMENT_DENSITY_2_2 - N_SD * SD_9_SEGMENT_DENSITY_2_2)) && (segmentDensity[2][2] <= (MEAN_9_SEGMENT_DENSITY_2_2 + N_SD * SD_9_SEGMENT_DENSITY_2_2))) &&
    ((segmentDensity[3][0] >= (MEAN_9_SEGMENT_DENSITY_3_0 - N_SD * SD_9_SEGMENT_DENSITY_3_0)) && (segmentDensity[3][0] <= (MEAN_9_SEGMENT_DENSITY_3_0 + N_SD * SD_9_SEGMENT_DENSITY_3_0))) &&
    ((segmentDensity[3][1] >= (MEAN_9_SEGMENT_DENSITY_3_1 - N_SD * SD_9_SEGMENT_DENSITY_3_1)) && (segmentDensity[3][1] <= (MEAN_9_SEGMENT_DENSITY_3_1 + N_SD * SD_9_SEGMENT_DENSITY_3_1))) &&
    ((segmentDensity[3][2] >= (MEAN_9_SEGMENT_DENSITY_3_2 - N_SD * SD_9_SEGMENT_DENSITY_3_2)) && (segmentDensity[3][2] <= (MEAN_9_SEGMENT_DENSITY_3_2 + N_SD * SD_9_SEGMENT_DENSITY_3_2))) &&
    ((segmentDensity[4][0] >= (MEAN_9_SEGMENT_DENSITY_4_0 - N_SD * SD_9_SEGMENT_DENSITY_4_0)) && (segmentDensity[4][0] <= (MEAN_9_SEGMENT_DENSITY_4_0 + N_SD * SD_9_SEGMENT_DENSITY_4_0))) &&
    ((segmentDensity[4][1] >= (MEAN_9_SEGMENT_DENSITY_4_1 - N_SD * SD_9_SEGMENT_DENSITY_4_1)) && (segmentDensity[4][1] <= (MEAN_9_SEGMENT_DENSITY_4_1 + N_SD * SD_9_SEGMENT_DENSITY_4_1))) &&
    ((segmentDensity[4][2] >= (MEAN_9_SEGMENT_DENSITY_4_2 - N_SD * SD_9_SEGMENT_DENSITY_4_2)) && (segmentDensity[4][2] <= (MEAN_9_SEGMENT_DENSITY_4_2 + N_SD * SD_9_SEGMENT_DENSITY_4_2))) &&
    ((yIncrements[0][0] >= (MEAN_9_Y_INCREMENT_0_0 - N_SD * SD_9_Y_INCREMENT_0_0)) && (yIncrements[0][0] <= (MEAN_9_Y_INCREMENT_0_0 + N_SD * SD_9_Y_INCREMENT_0_0))) && 
    ((xIncrements[0][0] >= (MEAN_9_X_INCREMENT_0_0 - N_SD * SD_9_X_INCREMENT_0_0)) && (xIncrements[0][0] <= (MEAN_9_X_INCREMENT_0_0 + N_SD * SD_9_X_INCREMENT_0_0))) &&
    ((yIncrements[0][1] >= (MEAN_9_Y_INCREMENT_0_1 - N_SD * SD_9_Y_INCREMENT_0_1)) && (yIncrements[0][1] <= (MEAN_9_Y_INCREMENT_0_1 + N_SD * SD_9_Y_INCREMENT_0_1))) && 
    ((xIncrements[0][1] >= (MEAN_9_X_INCREMENT_0_1 - N_SD * SD_9_X_INCREMENT_0_1)) && (xIncrements[0][1] <= (MEAN_9_X_INCREMENT_0_1 + N_SD * SD_9_X_INCREMENT_0_1))) &&
    ((yIncrements[0][2] >= (MEAN_9_Y_INCREMENT_0_2 - N_SD * SD_9_Y_INCREMENT_0_2)) && (yIncrements[0][2] <= (MEAN_9_Y_INCREMENT_0_2 + N_SD * SD_9_Y_INCREMENT_0_2))) && 
    ((xIncrements[0][2] >= (MEAN_9_X_INCREMENT_0_2 - N_SD * SD_9_X_INCREMENT_0_2)) && (xIncrements[0][2] <= (MEAN_9_X_INCREMENT_0_2 + N_SD * SD_9_X_INCREMENT_0_2))) &&
    ((yIncrements[1][0] >= (MEAN_9_Y_INCREMENT_1_0 - N_SD * SD_9_Y_INCREMENT_1_0)) && (yIncrements[1][0] <= (MEAN_9_Y_INCREMENT_1_0 + N_SD * SD_9_Y_INCREMENT_1_0))) && 
    ((xIncrements[1][0] >= (MEAN_9_X_INCREMENT_1_0 - N_SD * SD_9_X_INCREMENT_1_0)) && (xIncrements[1][0] <= (MEAN_9_X_INCREMENT_1_0 + N_SD * SD_9_X_INCREMENT_1_0))) &&
    ((yIncrements[1][1] >= (MEAN_9_Y_INCREMENT_1_1 - N_SD * SD_9_Y_INCREMENT_1_1)) && (yIncrements[1][1] <= (MEAN_9_Y_INCREMENT_1_1 + N_SD * SD_9_Y_INCREMENT_1_1))) && 
    ((xIncrements[1][1] >= (MEAN_9_X_INCREMENT_1_1 - N_SD * SD_9_X_INCREMENT_1_1)) && (xIncrements[1][1] <= (MEAN_9_X_INCREMENT_1_1 + N_SD * SD_9_X_INCREMENT_1_1))) &&
    ((yIncrements[1][2] >= (MEAN_9_Y_INCREMENT_1_2 - N_SD * SD_9_Y_INCREMENT_1_2)) && (yIncrements[1][2] <= (MEAN_9_Y_INCREMENT_1_2 + N_SD * SD_9_Y_INCREMENT_1_2))) && 
    ((xIncrements[1][2] >= (MEAN_9_X_INCREMENT_1_2 - N_SD * SD_9_X_INCREMENT_1_2)) && (xIncrements[1][2] <= (MEAN_9_X_INCREMENT_1_2 + N_SD * SD_9_X_INCREMENT_1_2))) &&
    ((yIncrements[2][0] >= (MEAN_9_Y_INCREMENT_2_0 - N_SD * SD_9_Y_INCREMENT_2_0)) && (yIncrements[2][0] <= (MEAN_9_Y_INCREMENT_2_0 + N_SD * SD_9_Y_INCREMENT_2_0))) && 
    ((xIncrements[2][0] >= (MEAN_9_X_INCREMENT_2_0 - N_SD * SD_9_X_INCREMENT_2_0)) && (xIncrements[2][0] <= (MEAN_9_X_INCREMENT_2_0 + N_SD * SD_9_X_INCREMENT_2_0))) &&
    ((yIncrements[2][1] >= (MEAN_9_Y_INCREMENT_2_1 - N_SD * SD_9_Y_INCREMENT_2_1)) && (yIncrements[2][1] <= (MEAN_9_Y_INCREMENT_2_1 + N_SD * SD_9_Y_INCREMENT_2_1))) && 
    ((xIncrements[2][1] >= (MEAN_9_X_INCREMENT_2_1 - N_SD * SD_9_X_INCREMENT_2_1)) && (xIncrements[2][1] <= (MEAN_9_X_INCREMENT_2_1 + N_SD * SD_9_X_INCREMENT_2_1))) &&
    ((yIncrements[2][2] >= (MEAN_9_Y_INCREMENT_2_2 - N_SD * SD_9_Y_INCREMENT_2_2)) && (yIncrements[2][2] <= (MEAN_9_Y_INCREMENT_2_2 + N_SD * SD_9_Y_INCREMENT_2_2))) && 
    ((xIncrements[2][2] >= (MEAN_9_X_INCREMENT_2_2 - N_SD * SD_9_X_INCREMENT_2_2)) && (xIncrements[2][2] <= (MEAN_9_X_INCREMENT_2_2 + N_SD * SD_9_X_INCREMENT_2_2)))) {
        printf ("9\n");
    } else {
        printf ("fail\n");
    }



    






    return EXIT_SUCCESS;
}