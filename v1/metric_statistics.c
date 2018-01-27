#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "captcha.h"
#include "metric_statistics_definitions.h"

#define N 9

int main (int argc, char *argv[]) {
    int height, width, start_row, start_column, box_width, box_height, i, j;
    double horizontalBalance, averageHorizontalBalance = 0, standardDeviationHorizontalBalance = 0;
    double verticalBalance, averageVerticalBalance = 0, standardDeviationVerticalBalance = 0;
    double tallness, averageTallness = 0, standardDeviationTallness = 0;
    double density, averageDensity = 0, standardDeviationDensity = 0;
    double yIncrements[DIGIT_SAMPLE_SIZE][Y_INCREMENT_SEGMENTS][X_INCREMENT_SEGMENTS] = {0}, averageYIncrements[Y_INCREMENT_SEGMENTS][X_INCREMENT_SEGMENTS] = {0}, standardDeviationYIncrements[Y_INCREMENT_SEGMENTS][X_INCREMENT_SEGMENTS] = {0};
    double xIncrements[DIGIT_SAMPLE_SIZE][Y_INCREMENT_SEGMENTS][X_INCREMENT_SEGMENTS] = {0}, averageXIncrements[Y_INCREMENT_SEGMENTS][X_INCREMENT_SEGMENTS] = {0}, standardDeviationXIncrements[Y_INCREMENT_SEGMENTS][X_INCREMENT_SEGMENTS] = {0};
    double segmentDensity[DIGIT_SAMPLE_SIZE][Y_DENSITY_SEGMENTS][X_DENSITY_SEGMENTS] = {0}, averageSegmentDensity[Y_DENSITY_SEGMENTS][X_DENSITY_SEGMENTS] = {0}, standardDeviationSegmentDensity[Y_DENSITY_SEGMENTS][X_DENSITY_SEGMENTS] = {0};
    FILE *fp = fopen ("definitions.doc", "a");

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }
    if (get_pbm_dimensions (argv[1], &height, &width) != 1) {
        return 1;
    }

    int pixels[height][width];

    for (i = 1; read_pbm (argv[i], height, width, pixels) == 1; i ++) {
        get_bounding_box (height, width, pixels, &start_row, &start_column, &box_height, &box_width);
        int box_pixels[box_height][box_width];
        copy_pixels (height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

        // print_image (box_height, box_width, box_pixels);
        // printf ("\n");

        for (int yTicker = 0; yTicker < Y_DENSITY_SEGMENTS; yTicker ++) {
            for (int xTicker = 0; xTicker < X_DENSITY_SEGMENTS; xTicker ++) {
                segmentDensity[i][yTicker][xTicker] =  get_segment_density (box_height, box_width, box_pixels, &yTicker, &xTicker);
                averageSegmentDensity[yTicker][xTicker] += get_segment_density (box_height, box_width, box_pixels, &yTicker, &xTicker);
                //fprintf (fp, "segmentDensity[%d][%d] = %lf\n", yTicker, xTicker, segmentDensity[i][yTicker][xTicker]);
            }
        }
       

        horizontalBalance = get_horizontal_balance (box_height, box_width, box_pixels);
        verticalBalance = get_vertical_balance (box_height, box_width, box_pixels);
        density = get_density (box_height, box_width, box_pixels);
        tallness = get_tallness (box_height, box_width);
        // fprintf (fp, "horizontalBalance = %lf\n", horizontalBalance);
        // fprintf (fp, "verticalBalance = %lf\n", verticalBalance);
        // fprintf (fp, "density = %lf\n", density);
        // fprintf (fp, "tallness = %lf\n", tallness);

        averageHorizontalBalance += horizontalBalance;
        averageVerticalBalance += verticalBalance;
        averageDensity += density;
        averageTallness += tallness;
        // for (int yTicker = 0; yTicker < Y_INCREMENT_SEGMENTS; yTicker ++) {
        //     for (int xTicker = 0; xTicker < X_INCREMENT_SEGMENTS; xTicker ++) {
        //         yIncrements[i][yTicker][xTicker] = get_y_increments (box_height, box_width, box_pixels, &yTicker, &xTicker);
        //         xIncrements[i][yTicker][xTicker] = get_x_increments (box_height, box_width, box_pixels, &yTicker, &xTicker);
        //         // fprintf (fp, "yIncrements[%d][%d] = %lf\n", yTicker, xTicker, yIncrements[i][yTicker][xTicker]);
        //         // fprintf (fp, "xIncrements[%d][%d] = %lf\n", yTicker, xTicker, xIncrements[i][yTicker][xTicker]);

        //         averageYIncrements[yTicker][xTicker] += get_y_increments (box_height, box_width, box_pixels, &yTicker, &xTicker);
        //         averageXIncrements[yTicker][xTicker] += get_x_increments (box_height, box_width, box_pixels, &yTicker, &xTicker);
        //     }
        // }
    }

    i --;
    
    printf ("i = %d\n", i);
    averageHorizontalBalance /= i;
    averageVerticalBalance /= i;
    averageDensity /= i;
    averageTallness /= i;
   
    fprintf (fp, "#define MEAN_%d_HORIZONTAL_BALANCE %lf\n", N, averageHorizontalBalance);
    fprintf (fp, "#define MEAN_%d_VERTICAL_BALANCE %lf\n", N, averageVerticalBalance);
    fprintf (fp, "#define MEAN_%d_DENSITY %lf\n", N, averageDensity);
    fprintf (fp, "#define MEAN_%d_TALLNESS %lf\n", N, averageTallness);
    for (int yTicker = 0; yTicker < Y_DENSITY_SEGMENTS; yTicker ++) {
        for (int xTicker = 0; xTicker < X_DENSITY_SEGMENTS; xTicker ++) {
            averageSegmentDensity[yTicker][xTicker] /= i;
            fprintf (fp, "#define MEAN_%d_SEGMENT_DENSITY_%d_%d %lf\n", N, yTicker, xTicker, averageSegmentDensity[yTicker][xTicker]);
        }
    }
    // for (int yTicker = 0; yTicker < Y_INCREMENT_SEGMENTS; yTicker ++) {
    //     for (int xTicker = 0; xTicker < X_INCREMENT_SEGMENTS; xTicker ++) {
    //         averageYIncrements[yTicker][xTicker] /= i;
    //         averageXIncrements[yTicker][xTicker] /= i;
    //         fprintf (fp, "#define MEAN_%d_Y_INCREMENT_%d_%d %lf\n", N, yTicker, xTicker, averageYIncrements[yTicker][xTicker]);
    //         fprintf (fp, "#define MEAN_%d_X_INCREMENT_%d_%d %lf\n", N, yTicker, xTicker, averageXIncrements[yTicker][xTicker]);
    //     }
    // }
    

    for (j = 1; read_pbm (argv[j], height, width, pixels) == 1; j ++) {
        get_bounding_box (height, width, pixels, &start_row, &start_column, &box_height, &box_width);
        int box_pixels[box_height][box_width];
        copy_pixels (height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);
        horizontalBalance = get_horizontal_balance (box_height, box_width, box_pixels);
        verticalBalance = get_vertical_balance (box_height, box_width, box_pixels);
        density = get_density (box_height, box_width, box_pixels);
        tallness = get_tallness (box_height, box_width);
        standardDeviationHorizontalBalance += pow (horizontalBalance - averageHorizontalBalance, 2);
        standardDeviationVerticalBalance += pow (verticalBalance - averageVerticalBalance, 2);
        standardDeviationDensity += pow (density - averageDensity, 2);
        standardDeviationTallness += pow (tallness - averageTallness, 2);
        // for (int yTicker = 0; yTicker < Y_INCREMENT_SEGMENTS; yTicker ++) {
        //     for (int xTicker = 0; xTicker < X_INCREMENT_SEGMENTS; xTicker ++) {
        //         standardDeviationYIncrements[yTicker][xTicker] += pow (yIncrements[j][yTicker][xTicker] - averageYIncrements[yTicker][xTicker], 2);
        //         standardDeviationXIncrements[yTicker][xTicker] += pow (xIncrements[j][yTicker][xTicker] - averageXIncrements[yTicker][xTicker], 2);
        //     }
        // }
        for (int yTicker = 0; yTicker < Y_DENSITY_SEGMENTS; yTicker ++) {
            for (int xTicker = 0; xTicker < X_DENSITY_SEGMENTS; xTicker ++) {
                standardDeviationSegmentDensity[yTicker][xTicker] += pow (segmentDensity[j][yTicker][xTicker] - averageSegmentDensity[yTicker][xTicker], 2);
            }
        }
    }

    standardDeviationHorizontalBalance = sqrt (standardDeviationHorizontalBalance / (i - 1));
    standardDeviationVerticalBalance = sqrt (standardDeviationVerticalBalance / (i - 1));
    standardDeviationDensity = sqrt (standardDeviationDensity / (i - 1));
    standardDeviationTallness = sqrt (standardDeviationTallness / (i - 1));
    
    fprintf (fp, "#define SD_%d_HORIZONTAL_BALANCE %lf\n", N, standardDeviationHorizontalBalance);
    fprintf (fp, "#define SD_%d_VERTICAL_BALANCE %lf\n", N, standardDeviationVerticalBalance);
    fprintf (fp, "#define SD_%d_DENSITY %lf\n", N, standardDeviationDensity);
    fprintf (fp, "#define SD_%d_TALLNESS %lf\n", N, standardDeviationTallness);
    

    for (int yTicker = 0; yTicker < Y_DENSITY_SEGMENTS; yTicker ++) {
        for (int xTicker = 0; xTicker < X_DENSITY_SEGMENTS; xTicker ++) {
            standardDeviationSegmentDensity[yTicker][xTicker] = sqrt (standardDeviationSegmentDensity[yTicker][xTicker] / (i - 1));
            fprintf (fp, "#define SD_%d_SEGMENT_DENSITY_%d_%d %lf\n", N, yTicker, xTicker, standardDeviationSegmentDensity[yTicker][xTicker]);
        }
    }
    // for (int yTicker = 0; yTicker < Y_INCREMENT_SEGMENTS; yTicker ++) {
    //     for (int xTicker = 0; xTicker < X_INCREMENT_SEGMENTS; xTicker ++) {
    //         standardDeviationYIncrements[yTicker][xTicker] = sqrt (standardDeviationYIncrements[yTicker][xTicker] / (i - 1));
    //         standardDeviationXIncrements[yTicker][xTicker] = sqrt (standardDeviationXIncrements[yTicker][xTicker] / (i - 1));

    //         fprintf (fp, "#define SD_%d_Y_INCREMENT_%d_%d %lf\n", N, yTicker, xTicker, standardDeviationYIncrements[yTicker][xTicker]);
    //         fprintf (fp, "#define SD_%d_X_INCREMENT_%d_%d %lf\n", N, yTicker, xTicker, standardDeviationXIncrements[yTicker][xTicker]);
    //     }
    // }


    fprintf (fp, "\n");
    fclose (fp);

    return EXIT_SUCCESS;
}