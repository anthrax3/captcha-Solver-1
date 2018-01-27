#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CHARACTERS 4096
#define DIGIT_SAMPLE_SIZE 100
#define Y_INCREMENT_SEGMENTS 3
#define X_INCREMENT_SEGMENTS 3
#define Y_DENSITY_SEGMENTS 5
#define X_DENSITY_SEGMENTS 3
#define N_SD 3
#define	N_NUMBERS 10

int read_pbm (char filename[], int height, int width, int pixels[height][width]);
int get_pbm_dimensions (char filename[], int *height, int *width);
void print_image (int height, int width, int pixels[height][width]);
void get_bounding_box (int height, int width, int pixels[height][width],
                  int *start_row, int *start_column, int *box_height, int *box_width);
void copy_pixels (int height, int width, int pixels[height][width],
                 int start_row, int start_column, int copy_height, int copy_width,
                 int copy[copy_height][copy_width]);
double get_horizontal_balance (int height, int width, int pixels[height][width]);
double get_vertical_balance (int height, int width, int pixels[height][width]);
double get_density (int height, int width, int pixels[height][width]);
double get_tallness (int height, int width);
double get_y_increments (int height, int width, int pixels[height][width], int *yTicker, int *xTicker);
double get_x_increments (int height, int width, int pixels[height][width], int *yTicker, int *xTicker);
double get_segment_density (int height, int width, int pixels[height][width], int *yTicker, int *xTicker);
int get_holes (int height, int width, int pixels[height][width]);