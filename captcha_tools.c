// Project: COMP1511 Assignment 1
// Brief: C File with tools to help accurately make predictions from CAPTCHA images
// Author: Da Jason Sun (z5059224) 
// Contact details: jason.sun@student.unsw.edu.au
// Date: 30/04/2017
// Notes:



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "captcha.h"

// ----- CAPTCHA TOOLS -----

// Function that checks whether a 1 exists for each vertical line in an array
void get_x_check (int height, int width, int pixels[height][width], int xCheck[width]) {
	for (int x = 0; x < width; x ++) {
		for (int y = 0; y < height; y ++) {
			if (pixels[y][x] == 1) {
				xCheck[x] = 1;
			}
		}
	}
}



// Function that determines the starting column in order to spit a captcha into 4 digits
void get_split_start_column (int height, int width, int pixels[height][width], int digitSplitStartColumn[N_CAPTCHA_DIGITS]) {
	int xCheck[MAX_CHARACTERS] = {0}, emptyColumnSize[MAX_CHARACTERS] = {0}, emptyColumnStart[MAX_CHARACTERS] = {0};
	int nEmptyColumns = 0;

	// Checks for whether a 1 exists for each vertical line in an array
	get_x_check (height, width, pixels, xCheck);

	// Checks for the number of empty vertical columns, the size of the empty vertical columns and the start of these empty vertical columns
	for (int x = 0; x < width; x ++) {
		if (xCheck[x] == 0) {
			emptyColumnSize[nEmptyColumns] ++;
		}

		if (xCheck[x] == 0 && x == 0) {
			emptyColumnStart[nEmptyColumns] = x;
		} else if (xCheck[x] == 0 && xCheck[x - 1] == 1) {
			emptyColumnStart[nEmptyColumns] = x;
		}

		if (xCheck[x] == 1 && x == 0) {
			nEmptyColumns ++;
		} else if (xCheck[x] == 1 && xCheck[x - 1] == 0) {
			nEmptyColumns ++;
		}
	}

	// Determines starting column for a captcha to be split into 4 images as roughly the middle of a group of empty vertical columns
	// This is done through adding the start of an empty column with half the size of that empty column
	for (int emptyColumnTicker = 0; emptyColumnTicker < nEmptyColumns; emptyColumnTicker ++) {
		digitSplitStartColumn[emptyColumnTicker] = emptyColumnStart[emptyColumnTicker] + emptyColumnSize[emptyColumnTicker] / 2;
	}
}



// Function that determines the width of an array holding 1 of 4 split digits from a captcha 
void get_split_width (int height, int width, int pixels[height][width], int digitSplitWidth[N_CAPTCHA_DIGITS]) {
	int digitSplitStartColumn[N_CAPTCHA_DIGITS] = {0};

	// Gets starting columns for 4 digit captcha splits
	get_split_start_column (height, width, pixels, digitSplitStartColumn);

	// Finds 4 digit captcha split widths through the difference in distances between the start columns of each digit
	for (int digitTicker = 0; digitTicker < N_CAPTCHA_DIGITS; digitTicker ++) {
		if (digitTicker == N_CAPTCHA_DIGITS - 1) {
			digitSplitWidth[digitTicker] = width - digitSplitStartColumn[digitTicker];
		} else {
			digitSplitWidth[digitTicker] = digitSplitStartColumn[digitTicker + 1] - digitSplitStartColumn[digitTicker];
		}
	}
}



// Function that centres the bounding box of split captcha digits within 50x70 arrays
void get_centred_captcha_digits (int height, int width, int pixels[height][width], 
	int centred_captcha_digits[N_CAPTCHA_DIGITS][NN_HEIGHT][NN_WIDTH]) {
	int digitSplitStartColumn[N_CAPTCHA_DIGITS] = {0}, digitSplitWidth[N_CAPTCHA_DIGITS] = {0};

	// Gets split start column and width
	get_split_start_column (height, width, pixels, digitSplitStartColumn);
    get_split_width (height, width, pixels, digitSplitWidth);
    // Captcha split need to be declared separately (and not in 1 3D array) because of the difference in width size and thereby size of the array
    int captchaN0[height][digitSplitWidth[0]], captchaN1[height][digitSplitWidth[1]], captchaN2[height][digitSplitWidth[2]], captchaN3[height][digitSplitWidth[3]];

    // Using information on captcha splits to copy captcha digits into separate arrays 
    // Separate captcha split declarations means cannot be looped easily
    copy_pixels (height, width, pixels, 0, digitSplitStartColumn[0], height, digitSplitWidth[0], captchaN0);
    copy_pixels (height, width, pixels, 0, digitSplitStartColumn[1], height, digitSplitWidth[1], captchaN1);
    copy_pixels (height, width, pixels, 0, digitSplitStartColumn[2], height, digitSplitWidth[2], captchaN2);
    copy_pixels (height, width, pixels, 0, digitSplitStartColumn[3], height, digitSplitWidth[3], captchaN3);

    // Centres each captcha digit
    // Separate captcha split declarations means cannot be looped easily
    get_centred_digit (height, digitSplitWidth[0], captchaN0, centred_captcha_digits[0]);
    get_centred_digit (height, digitSplitWidth[1], captchaN1, centred_captcha_digits[1]);
    get_centred_digit (height, digitSplitWidth[2], captchaN2, centred_captcha_digits[2]);
    get_centred_digit (height, digitSplitWidth[3], captchaN3, centred_captcha_digits[3]);
}

