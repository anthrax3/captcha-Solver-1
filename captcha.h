// Project: COMP1511 Assignment 1
// Brief: Header file for the COMP1511 Assignment 1 (main functions exist in crack_digit.c and crack_captcha.c)
// Author: Da Jason Sun (z5059224) 
// Contact details: jason.sun@student.unsw.edu.au
// Date: 30/04/2017
// Notes:



#include <stdio.h>
#include <stdlib.h>
#include <math.h>



// ----- DEFINITIONS -----

#define MAX_CHARACTERS 4096
#define	N_SINGLE_DIGITS 10
#define N_SINGLE_DIGITS_SAMPLE_SIZE 100
#define LEARNING_RATE 0.475
#define NN_HEIGHT 70
#define NN_WIDTH 50
#define N_TRAINING_FILES 5000
#define N_TESTING_FILES 500
#define N_CAPTCHA_TESTING_FILES 1000
#define FILENAME_STRING_LENGTH 14
#define CAPTCHA_FILENAME_STRING_LENGTH 26
#define FILE_LABEL_STRING_LENGTH 1
#define N_CAPTCHA_DIGITS 4
#define N_CHALLENGE_CAPTCHAS 1000
#define CHALLENGE_HEIGHT 70
#define CHALLENGE_WIDTH 200
#define MINIMUM_HOLE_SIZE 20
#define X_DENSITY_SEGMENT_SIZE 4
#define CENTRE_SIDES 2
#define N_HOLES 50



// ----- STRUCT CREATION -----

// Neuron and synapses
typedef struct neuron neuron_t;
struct neuron {
	double output;
	double input[NN_HEIGHT][NN_WIDTH];
	double weight[NN_HEIGHT][NN_WIDTH];
};



// Layer of neural network (1 of 1)
typedef struct layer layer_t;
struct layer {
	neuron_t neuron[N_SINGLE_DIGITS];
};



// Output format to process predictions in neural network
typedef struct output_format output_format_t;
struct output_format {
	int outputValue[N_SINGLE_DIGITS];
};



// ----- SETUP FUNCTIONS -----

// Andrew Taylor's read image function
int read_pbm (char filename[], int height, int width, int pixels[height][width]);



// Andrew Taylor's get image dimensions function
int get_pbm_dimensions (char filename[], int *height, int *width);



// ----- NEURAL NETWORK -----

// Intialises layers by setting input, output and bias to 0 and assigning random 0 - 1 values for weights
void get_initialised_layer (layer_t *nNlayer);



// Updates the current layer's weights with the trained weights
void get_trained_weights (layer_t *nNlayer);



// Initialises input by equating elements with pixels array
void get_neuron_input (neuron_t *nNeuron, int height, int width, int pixels[height][width]);


// Calculates neuron output by summing weighted inputs for all pixels
void get_neuron_output (neuron_t *nNeuron);



// Returns number prediction for neuron with highest output
int get_prediction (layer_t *nNlayer);



// Converts predicted number into output format (assigning 1 for predicted number, 0 for other numbers)
output_format_t get_target_output (int targetIndex);



// ----- TRAINING FUNCTIONS -----

// Returns the difference between the target value and the neuron's output
double get_neuron_error (neuron_t *nNeuron, int targetValue);



// Updates neuron weights based upon error (supervised learning)
void update_neuron_weights (neuron_t *nNeuron, double neuronError);



// ----- DIGIT TOOLS -----

// Function that prints the image
void print_image (int height, int width, int pixels[height][width]);



// Function that ascertains minimum rectangle enclosing the black pixels of the image
void get_bounding_box (int height, int width, int pixels[height][width],
                  int *start_row, int *start_column, int *box_height, int *box_width);



// Function that copies the rectangle of pixel values specified by start_row, start_column, copy_height and copy_width from the array pixels into the array copy
void copy_pixels (int height, int width, int pixels[height][width],
                 int start_row, int start_column, int copy_height, int copy_width,
                 int copy[copy_height][copy_width]);



// Function that determines where a bounding box can be centred in a 50x70 array
void centred_digit (int start_row, int start_column, int height, int width, int pixels[height][width], int centred_pixels[NN_HEIGHT][NN_WIDTH]);



// Function that centres the bounding box within a 50x70 array
void get_centred_digit (int height, int width, int pixels[height][width], int centred_pixels[NN_HEIGHT][NN_WIDTH]);



// ----- CAPTCHA TOOLS -----

// Function that checks whether a 1 exists for each vertical line in an array
void get_x_check (int height, int width, int pixels[height][width], int xCheck[width]);



// Function that determines the starting column in order to spit a captcha into 4 digits
void get_split_start_column (int height, int width, int pixels[height][width], int digit_split_start_row[N_CAPTCHA_DIGITS]);



// Function that determines the width of an array holding 1 of 4 split digits from a captcha 
void get_split_width (int height, int width, int pixels[height][width], int digit_split_width[N_CAPTCHA_DIGITS]);



// Function that centres the bounding box of split captcha digits within 50x70 arrays
void get_centred_captcha_digits (int height, int width, int pixels[height][width], 
	int centred_captcha_digits[N_CAPTCHA_DIGITS][NN_HEIGHT][NN_WIDTH]);


	
// ----- CHALLENGE CAPTCHA TOOLS -----

// Function that performs flood fill algorithm whilst collecting data on size of hole and coordiantes of pixels within holes
// Flood fill alorgorithm determines the area connected to a given node in a multi-dimensional array
void flood_fill (int y, int x, int height, int width, int pixels[height][width], int output, int input, int nHole, 
	int holeSize[MAX_CHARACTERS], int holeXCoordinate[MAX_CHARACTERS][MAX_CHARACTERS], int holeYCoordinate[MAX_CHARACTERS][MAX_CHARACTERS]);



// Function the uses the flood fill algorithm to determine size of holes before filling holes smaller in size then MINIMUM_HOLE_SIZE
void remove_holes (int height, int width, int pixels[height][width], int removeHolesPixels[height][width], int output, int input);



// Function that determines 4 pixel width vertical density distribution within an array
// UNFINISHED
void get_x_density (int height, int width, int pixels[height][width], double xSegmentDensity[width / X_DENSITY_SEGMENT_SIZE]);