#include <stdio.h>
#include <stdlib.h>

#define NUMBER 1

int main (int argc, char *argv[]) {

	FILE *fileNames = fopen ("digits_file_names.c", "a");
	FILE *fileLabels = fopen ("digits_file_labels.c", "a");

	for (int i = 0; i <= 501; i ++) {
		fprintf (fileLabels, "0\n");
		if (i < 10) {
			fprintf (fileNames, "digits/0_0%d.pbm\n", i);
		} else {
			fprintf (fileNames, "digits/0_%d.pbm\n", i);
		}
	}
	for (int i = 0; i <= 503; i ++) {
		fprintf (fileLabels, "1\n");
		if (i < 10) {
			fprintf (fileNames, "digits/1_0%d.pbm\n", i);
		} else {
			fprintf (fileNames, "digits/1_%d.pbm\n", i);
		}
	}
	for (int i = 0; i <= 490; i ++) {
		fprintf (fileLabels, "2\n");
		if (i < 10) {
			fprintf (fileNames, "digits/2_0%d.pbm\n", i);
		} else {
			fprintf (fileNames, "digits/2_%d.pbm\n", i);
		}
	}
	for (int i = 0; i <= 519; i ++) {
		fprintf (fileLabels, "3\n");
		if (i < 10) {
			fprintf (fileNames, "digits/3_0%d.pbm\n", i);
		} else {
			fprintf (fileNames, "digits/3_%d.pbm\n", i);
		}
	}
	for (int i = 0; i <= 479; i ++) {
		fprintf (fileLabels, "4\n");
		if (i < 10) {
			fprintf (fileNames, "digits/4_0%d.pbm\n", i);
		} else {
			fprintf (fileNames, "digits/4_%d.pbm\n", i);
		}
	}
	for (int i = 0; i <= 493; i ++) {
		fprintf (fileLabels, "5\n");
		if (i < 10) {
			fprintf (fileNames, "digits/5_0%d.pbm\n", i);
		} else {
			fprintf (fileNames, "digits/5_%d.pbm\n", i);
		}
	}
	for (int i = 0; i <= 492; i ++) {
		fprintf (fileLabels, "6\n");
		if (i < 10) {
			fprintf (fileNames, "digits/6_0%d.pbm\n", i);
		} else {
			fprintf (fileNames, "digits/6_%d.pbm\n", i);
		}
	}
	for (int i = 0; i <= 528; i ++) {
		fprintf (fileLabels, "7\n");
		if (i < 10) {
			fprintf (fileNames, "digits/7_0%d.pbm\n", i);
		} else {
			fprintf (fileNames, "digits/7_%d.pbm\n", i);
		}
	}
	for (int i = 0; i <= 503; i ++) {
		fprintf (fileLabels, "8\n");
		if (i < 10) {
			fprintf (fileNames, "digits/8_0%d.pbm\n", i);
		} else {
			fprintf (fileNames, "digits/8_%d.pbm\n", i);
		}
	}
	for (int i = 0; i <= 482; i ++) {
		fprintf (fileLabels, "9\n");
		if (i < 10) {
			fprintf (fileNames, "digits/9_0%d.pbm\n", i);
		} else {
			fprintf (fileNames, "digits/9_%d.pbm\n", i);
		}
	}


	return EXIT_SUCCESS;
}