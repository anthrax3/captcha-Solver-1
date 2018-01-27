#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "captcha.h"

int main (int argc, char *argv[]) {
    int height, width, start_row, start_column, box_width, box_height;
    int digitSplitStartColumn[N_CAPTCHA_DIGITS] = {0}, digitSplitWidth[N_CAPTCHA_DIGITS] = {0};
    int prediction = 0;
    layer layer1;
    // train_neural_network (&layer1);
    // test_neural_network (&layer1);
    get_initialised_layer (&layer1);
    get_trained_weights (&layer1);
    
    

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }

    if (get_pbm_dimensions (argv[1], &height, &width) != 1) {
        return 1;
    }
    int pixels[height][width];
    

    if (read_pbm(argv[1], height, width, pixels) == 1) {
        print_image (height, width, pixels);
        get_split_start_column (height, width, pixels, digitSplitStartColumn);
        get_split_width (height, width, pixels, digitSplitWidth);
        int captchaN0[height][digitSplitWidth[0]], captchaN1[height][digitSplitWidth[1]], captchaN2[height][digitSplitWidth[2]], captchaN3[height][digitSplitWidth[3]];
        copy_pixels (height, width, pixels, 0, digitSplitStartColumn[0], height, digitSplitWidth[0], captchaN0);
        copy_pixels (height, width, pixels, 0, digitSplitStartColumn[1], height, digitSplitWidth[1], captchaN1);
        copy_pixels (height, width, pixels, 0, digitSplitStartColumn[2], height, digitSplitWidth[2], captchaN2);
        copy_pixels (height, width, pixels, 0, digitSplitStartColumn[3], height, digitSplitWidth[3], captchaN3);
        print_image (height, digitSplitWidth[0], captchaN0);
        printf ("\n");		
        print_image (height, digitSplitWidth[1], captchaN1);
        printf ("\n");
		print_image (height, digitSplitWidth[2], captchaN2);
		printf ("\n");
		print_image (height, digitSplitWidth[3], captchaN3);
        for (int j = 0; j < N_SINGLE_DIGITS; j ++) {
            get_neuron_input (&layer1.neuron[j], height, digitSplitWidth[0], captchaN0);
            get_neuron_output (&layer1.neuron[j]);
        }
        prediction = get_prediction (&layer1);
        printf ("%d", prediction);

        for (int j = 0; j < N_SINGLE_DIGITS; j ++) {
            get_neuron_input (&layer1.neuron[j], height, digitSplitWidth[1], captchaN1);
            get_neuron_output (&layer1.neuron[j]);
        }
        prediction = get_prediction (&layer1);
        printf ("%d", prediction);

        for (int j = 0; j < N_SINGLE_DIGITS; j ++) {
            get_neuron_input (&layer1.neuron[j], height, digitSplitWidth[2], captchaN2);
            get_neuron_output (&layer1.neuron[j]);
        }
        prediction = get_prediction (&layer1);
        printf ("%d", prediction);

        for (int j = 0; j < N_SINGLE_DIGITS; j ++) {
            get_neuron_input (&layer1.neuron[j], height, digitSplitWidth[3], captchaN3);
            get_neuron_output (&layer1.neuron[j]);
        }
        prediction = get_prediction (&layer1);
        printf ("%d\n", prediction);
    }

    return EXIT_SUCCESS;
}