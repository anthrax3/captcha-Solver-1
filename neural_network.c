// Project: COMP1511 Assignment 1
// Brief: C File with the functions that compose the 1 layer neural network used for digit predictions of a given input image
// Author: Da Jason Sun (z5059224) 
// Contact details: jason.sun@student.unsw.edu.au
// Date: 30/04/2017
// Notes: Theory and understanding of neural networks from: http://neuralnetworksanddeeplearning.com/chap1.html
		// and https://mmlind.github.io/Simple_3-Layer_Neural_Network_for_MNIST_Handwriting_Recognition/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "captcha.h"

// ----- NEURAL NETWORK -----

// Intialises layers by setting input, output and bias to 0 and assigning random 0 - 1 values for weights
void get_initialised_layer (layer_t *nNLayer) {

	// Loop through all neurons, all y values and all x values
	for (int neuronTicker = 0; neuronTicker < N_SINGLE_DIGITS; neuronTicker ++) {
		for (int y = 0; y < NN_HEIGHT; y ++) {
			for (int x = 0; x < NN_WIDTH; x ++) {
				nNLayer->neuron[neuronTicker].input[y][x] = 0;
				nNLayer->neuron[neuronTicker].weight[y][x] = (double) rand() / (double) RAND_MAX;
			}
		}
		nNLayer->neuron[neuronTicker].output = 0;
	}
}



// Updates the current layer's weights with the trained weights
void get_trained_weights (layer_t *nNLayer) {
	FILE *trainedWeights = fopen ("trained_weights.txt", "r");
	for (int neuronTicker = 0; neuronTicker < N_SINGLE_DIGITS; neuronTicker ++) {
        for (int y = 0; y < NN_HEIGHT; y ++) {
            for (int x = 0; x < NN_WIDTH; x ++) {
                fscanf (trainedWeights, "%lf", &nNLayer->neuron[neuronTicker].weight[y][x]);
            }
        }
    }
    fclose (trainedWeights);
}



// Initialises input by equating elements with pixels array
void get_neuron_input (neuron_t *nNeuron, int height, int width, int pixels[NN_HEIGHT][NN_WIDTH]) {
	for (int y = 0; y < NN_HEIGHT; y ++) {
		for (int x = 0; x < NN_WIDTH; x ++) {
			nNeuron->input[y][x] = pixels[y][x];
		}
	}
}



// Calculates neuron output by summing weighted inputs for all pixels and normalises it between 0 and 1
void get_neuron_output (neuron_t *nNeuron) {
	for (int y = 0; y < NN_HEIGHT; y ++) {
		for (int x = 0; x < NN_WIDTH; x ++) {
			nNeuron->output += nNeuron->input[y][x] * nNeuron->weight[y][x];
		}
 	} 	
 	nNeuron->output /= (NN_HEIGHT * NN_WIDTH);
}



// Returns number prediction for neuron with highest output
int get_prediction (layer_t *nNLayer) {
 	int prediction = 0;
 	double highestOutput = 0;
 	for (int neuronTicker = 0; neuronTicker < N_SINGLE_DIGITS; neuronTicker ++) {
 		if (nNLayer->neuron[neuronTicker].output > highestOutput) {
 			highestOutput = nNLayer->neuron[neuronTicker].output;
 			prediction = neuronTicker;
 		}
 		nNLayer->neuron[neuronTicker].output = 0;
 	} 	

 	return prediction;
 }
 


// Converts predicted number into output format (assigning 1 for predicted number, 0 for other numbers)
output_format_t get_target_output (int targetIndex) {
	output_format_t targetOutput;
	for (int neuronTicker = 0; neuronTicker < N_SINGLE_DIGITS; neuronTicker ++) {
		if (neuronTicker == targetIndex) {
			targetOutput.outputValue[neuronTicker] = 1;
		} else {
			targetOutput.outputValue[neuronTicker] = 0;
		}
	}

	return targetOutput;
}



// ----- TRAINING FUNCTIONS -----

// Returns the difference between the target value and the neuron's output 
double get_neuron_error (neuron_t *nNeuron, int targetValue) {
	double neuronError = 0;
	neuronError = targetValue - nNeuron->output;

	return neuronError;
}



// Updates neuron weights based upon error (supervised learning)
void update_neuron_weights (neuron_t *nNeuron, double neuronError) {
	for (int y = 0; y < NN_HEIGHT; y ++) {
		for (int x = 0; x < NN_WIDTH; x ++) {
			nNeuron->weight[y][x] += LEARNING_RATE * neuronError * nNeuron->input[y][x];
		}
	}
}
