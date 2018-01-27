// Project: COMP1511 Assignment 1
// Brief: C File with tools to help accurately make predictions from Challenge CAPTCHA images
// Author: Da Jason Sun (z5059224) 
// Contact details: jason.sun@student.unsw.edu.au
// Date: 30/04/2017
// Notes:



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "captcha.h"

// ----- CHALLENGE CAPTCHA TOOLS -----

// Function that performs flood fill algorithm whilst collecting data on size of hole and coordiantes of pixels within holes
// Flood fill alorgorithm determines the area connected to a given node in a multi-dimensional array
void flood_fill (int y, int x, int height, int width, int pixels[height][width], int output, int input, int nHole, 
	int holeSize[MAX_CHARACTERS], int holeXCoordinate[MAX_CHARACTERS][MAX_CHARACTERS], int holeYCoordinate[MAX_CHARACTERS][MAX_CHARACTERS]) {

	// Constraints so recursive function does not seg fault + conditions for recursion of input
	if (x >= 0 && x < width && y >= 0 && y < height && pixels[y][x] == input) {

		// Converting input to output
		pixels[y][x] = output;

		// Collecting data on hole size and coordinates of hole pixels
		holeXCoordinate[nHole][holeSize[nHole]] = x;
		holeYCoordinate[nHole][holeSize[nHole]] = y;
		holeSize[nHole] ++;

		// 4 direction recursive flood fill algorithm
		// Inspired by logic from http://lodev.org/cgtutor/floodfill.html
		flood_fill (y + 1, x, height, width, pixels, output, input, nHole, holeSize, holeXCoordinate, holeYCoordinate);
		flood_fill (y, x + 1, height, width, pixels, output, input, nHole, holeSize, holeXCoordinate, holeYCoordinate);
		flood_fill (y - 1, x, height, width, pixels, output, input, nHole, holeSize, holeXCoordinate, holeYCoordinate);
		flood_fill (y, x - 1, height, width, pixels, output, input, nHole, holeSize, holeXCoordinate, holeYCoordinate);
	} 
}



// Function the uses the flood fill algorithim to determine size of holes before filling holes smaller in size then MINIMUM_HOLE_SIZE
void remove_holes (int height, int width, int pixels[height][width], int removeHolesPixels[height][width], int output, int input) {
	int nHole = 0, holeSize[MAX_CHARACTERS] = {0};
	int holeSizePixels[height][width];
	int holeXCoordinate[N_HOLES][MAX_CHARACTERS] = {{0}}, holeYCoordinate[N_HOLES][MAX_CHARACTERS] = {{0}};

	// Replicating original array for working out
	copy_pixels (height, width, pixels, 0, 0, height, width, removeHolesPixels);
	copy_pixels (height, width, pixels, 0, 0, height, width, holeSizePixels);

	// Determining number of holes and size of each hole using flood fill algorithm
	for (int y = 0; y < height; y ++) {
		for (int x = 0; x < width; x ++) {
			if (holeSizePixels[y][x] == input) {
				flood_fill (y, x, height, width, holeSizePixels, output, input, nHole, holeSize, holeXCoordinate, holeYCoordinate);
				nHole ++;
			}	
		}
	}

	// Filling in holes based upon whether hole size < MINIMUM_HOLE_SIZE
	for (int holeTicker = 0; holeTicker < nHole; holeTicker ++) {
		for (int holeConstituent = 0; holeConstituent < MINIMUM_HOLE_SIZE; holeConstituent ++) {
			if (holeSize[holeTicker] < MINIMUM_HOLE_SIZE) {
				removeHolesPixels[holeYCoordinate[holeTicker][holeConstituent]][holeXCoordinate[holeTicker][holeConstituent]] = output; 
			}
		}
	}
}



// Function that determines 4 pixel width vertical density distribution within an array
void get_x_density (int height, int width, int pixels[height][width], double xSegmentDensity[width / X_DENSITY_SEGMENT_SIZE]) {
	double xDensity[CHALLENGE_WIDTH] = {0};
	int nXSegments = 0;

	FILE *fp = fopen ("xdensity.doc", "a");

	// Counting number of 1s in each vertical length of array
	for (int x = 0; x < width; x ++) {
		for (int y = 0; y < height; y ++) {
			if (pixels[y][x] == 1) {
				xDensity[x] ++;
			}
		}
	}

	// Combining number of 1s in each vertical length of array into groups of 4 pixel width
	for (int x = 0; x < width; x ++) {
		xSegmentDensity[nXSegments] += xDensity[x];
		if (x % X_DENSITY_SEGMENT_SIZE == 0) {
			nXSegments ++;
		}
	}

	// Dividing number of 1s in each group of 4 pixel width vertical groups in order to determine 4 pixel width vertical density
	for (int segmentTicker = 0; segmentTicker < width / X_DENSITY_SEGMENT_SIZE; segmentTicker ++) {
		xSegmentDensity[segmentTicker] /= (X_DENSITY_SEGMENT_SIZE * height);
		fprintf (fp, "%d %lf\n", segmentTicker, xSegmentDensity[segmentTicker]);
	}

	fclose (fp);
}
