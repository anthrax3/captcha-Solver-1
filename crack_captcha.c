// Project: COMP1511 Assignment 1
// Brief: C Program that outputs a prediction of 4 digits for the command line argument input of a captcha image filename
// Author: Da Jason Sun (z5059224) 
// Contact details: jason.sun@student.unsw.edu.au
// Date: 30/04/2017
// Notes: This file also contains training and testing functions for captcha predictions



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "captcha.h"

void test_crack_captcha (layer_t *nNlayer);

int main (int argc, char *argv[]) {
    int height = 0, width = 0;
    char prediction[N_CAPTCHA_DIGITS] = {0};
    int centredCaptchaDigits[N_CAPTCHA_DIGITS][NN_HEIGHT][NN_WIDTH] = {{{0}}};
    layer_t nNLayer;

    // Test function to determine weights and test accuracy of predictions
    // test_crack_captcha (&nNLayer);

    // Initialises neural network layer and initialises weights to previously trained values
    get_initialised_layer (&nNLayer);
    get_trained_weights (&nNLayer);
    
    
    // Produce error message if no image is called on command line
    // Taken from the testing files from lab exercise 7
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }

    // Exits program if unable to get pbm dimensions from image
    // Taken from the testing files from lab exercise 7
    if (get_pbm_dimensions (argv[1], &height, &width) != 1) {
        return 1;
    }

    // Initialises arrays after height and width are known for array size
    int pixels[height][width];
    // int removeHolesPixels0[height][width];
    // int removeHolesPixels1[height][width];
    
    // Reads input and determines prediction through removing distortions, splitting captcha into digits,
    // centring bounding box and determining the highest neuron output
    // Reads input
    if (read_pbm(argv[1], height, width, pixels) == 1) {
        // Removes specs/fills holes through flood fill algorithm
     //    remove_holes (height, width, pixels, removeHolesPixels0, 0, 1);
     //    remove_holes (height, width, removeHolesPixels0, removeHolesPixels1, 1, 0);
     //    double xSegmentDensity[width / X_DENSITY_SEGMENT_SIZE];
     //    get_x_density (height, width, pixels, xSegmentDensity);    	
    	// print_image (height, width, pixels);
    	// printf ("\n");
     //    print_image (height, width, removeHolesPixels1);

        // Splits captcha into 4 digits, bounding boxes them and centres them
        // Does not work with Challenge CAPTCHAs yet
        get_centred_captcha_digits (height, width, pixels, centredCaptchaDigits);

        // For each digit, loops through all 10 neurons for input and then output
        for (int digitTicker = 0; digitTicker < N_CAPTCHA_DIGITS; digitTicker ++) {
            for (int neuronTicker = 0; neuronTicker < N_SINGLE_DIGITS; neuronTicker ++) {
                get_neuron_input (&nNLayer.neuron[neuronTicker], NN_HEIGHT, NN_WIDTH, centredCaptchaDigits[digitTicker]);
                get_neuron_output (&nNLayer.neuron[neuronTicker]);
            }
            // Determines prediction from highest value output out of all 10 neurons
            prediction[digitTicker] = '0' + get_prediction (&nNLayer);
            
        }
        for (int digitTicker = 0; digitTicker < N_CAPTCHA_DIGITS; digitTicker ++) {
        	printf ("%c", prediction[digitTicker]);
        }
        printf ("\n");
    }

    return EXIT_SUCCESS;
}



// Tests neural network on 4 digit captcha images to test accuracy of predictions
void test_crack_captcha (layer_t *nNlayer) {
    char fileName[CAPTCHA_FILENAME_STRING_LENGTH] = {0};
    char fileLabel[N_CAPTCHA_DIGITS] = {0};
    double neuronError = 0;
    int height = 0, width = 0;
    char prediction[N_CAPTCHA_DIGITS] = {0};
    int nSuccess = 0, captchaSuccess = 0;
    int centredCaptchaDigits[N_CAPTCHA_DIGITS][NN_HEIGHT][NN_WIDTH] = {{{0}}};
    output_format_t targetOutput;
    double xSegmentDensity[CHALLENGE_WIDTH / X_DENSITY_SEGMENT_SIZE] = {0};
        

    // Opening file with training file names and file labels
    FILE *captchaFileNames = fopen ("test_captcha_file_names.c", "r");
    FILE *captchaFileLabels = fopen ("test_captcha_file_labels.c", "r");

    // Initialising the weights to the already trained values
    get_initialised_layer (nNlayer);
    get_trained_weights (nNlayer);

    // Running through testing files
    for (int nFiles = 0; nFiles < N_CAPTCHA_TESTING_FILES; nFiles ++) {
        // Reading file names and file labels
        fscanf (captchaFileNames, "%s", fileName);
        fscanf (captchaFileLabels, "%s", fileLabel);

        // Resetting captchaSuccess check with each loop
        captchaSuccess = 0;

        // Determines pbm dimensions before declaring arrays for the known height and width array size
        get_pbm_dimensions (fileName, &height, &width);
        int pixels[height][width];
        // int removeHolesPixels0[height][width];
        // int removeHolesPixels1[height][width];

        // Reads input
        read_pbm (fileName, height, width, pixels);

        // Removes specs/fills holes through flood fill algorithm
        // remove_holes (height, width, pixels, removeHolesPixels0, 0, 1);
        // remove_holes (height, width, removeHolesPixels0, removeHolesPixels1, 1, 0);
        // get_x_density (height, width, removeHolesPixels1, xSegmentDensity);

        // Splits captcha into 4 digits, bounding boxes them and centres them
        // Does not work with Challenge CAPTCHAs yet
        get_centred_captcha_digits (height, width, pixels, centredCaptchaDigits);
            // **** get_centred_captcha_digtis creates segfault because it doesnt work wtih challenge captchas
            // **** must remove noise before centred captcha digits will work

        // Tests predictions for each digit by looping through all 10 neurons for input and then output
        for (int digitTicker = 0; digitTicker < N_CAPTCHA_DIGITS; digitTicker ++) {
            targetOutput = get_target_output (fileLabel[digitTicker] - '0');
            for (int neuronTicker = 0; neuronTicker < N_SINGLE_DIGITS; neuronTicker ++) {
                get_neuron_input (&nNlayer->neuron[neuronTicker], NN_HEIGHT, NN_WIDTH, centredCaptchaDigits[digitTicker]);
                get_neuron_output (&nNlayer->neuron[neuronTicker]);
            }
            // Determines prediction from highest value output out of all 10 neurons
            prediction[digitTicker] = '0' + get_prediction (nNlayer);
        }
        printf ("%s\n", prediction);

        // Calculating and displaying aggregate results through multiples tests
        for (int digitTicker = 0; digitTicker < N_CAPTCHA_DIGITS; digitTicker ++) {
            if (prediction[digitTicker] == fileLabel[digitTicker]) {
                captchaSuccess = 1;
            } else {
                captchaSuccess = 0;
                break;
            }
            if (prediction[digitTicker] == fileLabel[digitTicker] && digitTicker == N_CAPTCHA_DIGITS - 1 && captchaSuccess == 1) {
                nSuccess ++;
            }
        }
        printf ("%s\n", fileName);
        printf ("prediction = %s, fileLabel = %s\n", prediction, fileLabel);
        printf ("Success rate = %lf\n\n", nSuccess / (double) (nFiles + 1));
    }

    // Closing opened files
    fclose (captchaFileNames);
    fclose (captchaFileLabels);
}