// Project: COMP1511 Assignment 1
// Brief: C File with tools to help accurately make predictions from digit images
// Author: Da Jason Sun (z5059224) 
// Contact details: jason.sun@student.unsw.edu.au
// Date: 30/04/2017
// Notes:

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "captcha.h"

// ----- DIGIT TOOLS -----

// Function that prints the image
void print_image(int height, int width, int pixels[height][width]) {
	int x = 0, y = 0;

	// Loops through y and x values and replaces 1s and 0s with * and . respectively
	for (y = height - 1; y >= 0; y --) {
		for (x = 0; x < width; x ++) {
			if (pixels[y][x] == 0) {
				printf (".");
			} else if (pixels[y][x] == 1) {
				printf ("*");
			}
		}
		printf ("\n");
	}
}



// Function that ascertains minimum rectangle enclosing the black pixels of the image
void get_bounding_box(int height, int width, int pixels[height][width],
                  int *start_row, int *start_column, int *box_height, int *box_width) {
	int x = 0, y = 0, xCheck[MAX_CHARACTERS] = {0}, yCheck[MAX_CHARACTERS] = {0}, startRowTick = 0, heightTick = 0, startColumnTick = 0, widthTick = 0;

	// Checks whether a 1 pixel exists along a vertical/horizontal line in the array
	for (y = 0; y < height; y ++) {
		for (x = 0; x < width; x ++) {
			if (pixels[y][x] == 1) {
				xCheck[x] = 1;
				yCheck[y] = 1;
			}
		}
	}

	// Goes through y values to assign the respective y variables required for bounding box
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

	// Goes through x valeus to assign the respective x variables required for bounding box
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



// Function that copies the rectangle of pixel values specified by start_row, start_column, copy_height and copy_width from the array pixels into the array copy
void copy_pixels(int height, int width, int pixels[height][width],
                 int start_row, int start_column, int copy_height, int copy_width,
                 int copy[copy_height][copy_width]) {
	int x = 0, y = 0, copyX = 0, copyY = 0;

	// Copying pixel array over into new copy array within given conditions
	for (y = start_row; y < start_row + copy_height; y ++) {
		copyX = 0;
		for (x = start_column; x < start_column + copy_width; x ++){
			copy[copyY][copyX] = pixels[y][x];
			copyX ++;
		}
		copyY ++;
	}
}



// Function that determines where a bounding box can be centred in a 50x70 array
void centred_digit (int start_row, int start_column, int height, int width, int pixels[height][width], int centred_pixels[NN_HEIGHT][NN_WIDTH]) {
	int yGapTotal = 0, xGapTotal = 0, yGap[CENTRE_SIDES] = {0}, xGap[CENTRE_SIDES] = {0}, yGapPosition[CENTRE_SIDES] = {0}, xGapPosition[CENTRE_SIDES] = {0};
	int pixelX = 0, pixelY = 0;

	// Calculating required values to develop centred bounding box
	// int was specifically used to ensure only whole digits were calculated (rounding is taken into account with exhaustive allocation of remaining pixel space)
	yGapTotal = (NN_HEIGHT - height);
	xGapTotal = (NN_WIDTH - width);
	yGap[0] = yGapTotal / CENTRE_SIDES;
	yGap[1] = yGapTotal - yGap[0];
	xGap[0] = xGapTotal / CENTRE_SIDES;
	xGap[1] = xGapTotal - xGap[0];
	yGapPosition[0] = yGap[0];
	xGapPosition[0] = xGap[0];
	yGapPosition[1] = NN_HEIGHT - yGap[1];
	xGapPosition[1] = NN_WIDTH - xGap[1];

	// Copying pixels over from bounding box into the centre of new centred_pixels array
	// Exhaustive use of else condition to ensure the remaining pixels of centred_pixels are 0s
	for (int y = 0; y < NN_HEIGHT; y ++) {
		pixelX = 0;
		for (int x = 0; x < NN_WIDTH; x ++) {
			if (y >= yGapPosition[0] && y < yGapPosition[0] + height && x >= xGapPosition[0] && x < xGapPosition[0] + width) {
				centred_pixels[y][x] = pixels[pixelY][pixelX];
				pixelX ++;
			} else {
				centred_pixels[y][x] = 0;
			}
		}
		if (y >=  yGapPosition[0] && y < yGapPosition[0] + height) {
			pixelY ++;
		}
	}
}



// Function that centres the bounding box within a 50x70 array
void get_centred_digit (int height, int width, int pixels[height][width], int centred_pixels[NN_HEIGHT][NN_WIDTH]) {
	int startRow, startColumn, boxHeight, boxWidth;

	// Finds bounding box of digit within pixel array
	get_bounding_box(height, width, pixels, &startRow, &startColumn, &boxHeight, &boxWidth);
	int boxPixels[boxHeight][boxWidth];

	// Copies array pixels into new bounding box boxPixels array
	copy_pixels (height, width, pixels, startRow, startColumn, boxHeight, boxWidth, boxPixels);

	// Centres boxPixels within a 50x70 centred_pixels array
	centred_digit (startRow, startColumn, boxHeight, boxWidth, boxPixels, centred_pixels);
}