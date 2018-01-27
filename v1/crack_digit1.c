#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "captcha.h"

int main (int argc, char *argv[]) {
    int height, width, start_row, start_column, box_width, box_height, i, j;
    double horizontalBalance, averageHorizontalBalance = 0, standardDeviationHorizontalBalance = 0;
    double verticalBalance, averageVerticalBalance = 0, standardDeviationVerticalBalance = 0;
    double tallness, averageTallness = 0, standardDeviationTallness = 0;
    double density, averageDensity = 0, standardDeviationDensity = 0;
    double yIncrements[DIGIT_SAMPLE_SIZE][MAX_CHARACTERS] = {0}, averageYIncrements[MAX_CHARACTERS] = {0}, standardDeviationYIncrements[MAX_CHARACTERS] = {0};
    double xIncrements[DIGIT_SAMPLE_SIZE][MAX_CHARACTERS] = {0}, averageXIncrements[MAX_CHARACTERS] = {0}, standardDeviationXIncrements[MAX_CHARACTERS] = {0};

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

        horizontalBalance = get_horizontal_balance (box_height, box_width, box_pixels);
        verticalBalance = get_vertical_balance (box_height, box_width, box_pixels);
        density = get_density (box_height, box_width, box_pixels);
        tallness = get_tallness (box_height, box_width);
        //print_image (box_height, box_width, box_pixels);
        printf ("\n");
        averageHorizontalBalance += horizontalBalance;
        averageVerticalBalance += verticalBalance;
        averageDensity += density;
        averageTallness += tallness;
        for (int k = 0; k < 10; k ++) {
            yIncrements[i][k] = get_y_increments (height, width, pixels, &k);
            xIncrements[i][k] = get_x_increments (height, width, pixels, &k);

            averageYIncrements[k] += get_y_increments (height, width, pixels, &k);
            averageXIncrements[k] += get_x_increments (height, width, pixels, &k);
        }
    }

    i --;
    printf ("i = %d\n", i);
    averageHorizontalBalance = averageHorizontalBalance / i;
    averageVerticalBalance = averageVerticalBalance / i;
    averageDensity = averageDensity / i;
    averageTallness = averageTallness / i;
    for (int k = 0; averageYIncrements[k] != 0; k ++) {
        averageYIncrements[k] /= i;
        printf ("averageYIncrements[%d] = %lf\n", k, averageYIncrements[k]);
    }
    printf ("\n");
    for (int k = 0; averageXIncrements[k] != 0; k ++) {
        averageXIncrements[k] /= i;
        printf ("averageXIncrements[%d] = %lf\n", k, averageXIncrements[k]);
    }
    printf ("averageHorizontalBalance = %lf\n", averageHorizontalBalance);
    printf ("averageVerticalBalance = %lf\n", averageVerticalBalance);
    printf ("averageDensity = %lf\n", averageDensity);
    printf ("averageTallness = %lf\n", averageTallness);

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
        for (int k = 0; yIncrements[j][k] != 0; k ++) {
            standardDeviationYIncrements[k] += pow (yIncrements[j][k] - averageYIncrements[k], 2);
        }
        for (int k = 0; xIncrements[j][k] != 0; k ++) {
            standardDeviationXIncrements[k] += pow (xIncrements[j][k] - averageXIncrements[k], 2);
        }
    }

    standardDeviationHorizontalBalance = sqrt (standardDeviationHorizontalBalance / (i - 1));
    standardDeviationVerticalBalance = sqrt (standardDeviationVerticalBalance / (i - 1));
    standardDeviationDensity = sqrt (standardDeviationDensity / (i - 1));
    standardDeviationTallness = sqrt (standardDeviationTallness / (i - 1));
    for (int k = 0; standardDeviationYIncrements[k] != 0; k ++) {
        standardDeviationYIncrements[k] = sqrt (standardDeviationYIncrements[k] / (i - 1));
        printf ("standardDeviationYIncrements[%d] = %lf\n", k, standardDeviationYIncrements[k]);
    }
    printf ("\n");
    for (int k = 0; standardDeviationXIncrements[k] != 0; k ++) {
        standardDeviationXIncrements[k] = sqrt (standardDeviationXIncrements[k] / (i - 1));
        printf ("standardDeviationXIncrements[%d] = %lf\n", k, standardDeviationXIncrements[k]);
    }

    printf ("standardDeviationHorizontalBalance = %lf\n", standardDeviationHorizontalBalance);
    printf ("standardDeviationVerticalBalance = %lf\n", standardDeviationVerticalBalance);
    printf ("standardDeviationDensity = %lf\n", standardDeviationDensity);
    printf ("standardDeviationTallness = %lf\n", standardDeviationTallness);

   


    return EXIT_SUCCESS;
}