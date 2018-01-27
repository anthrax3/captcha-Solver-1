#include "captcha.h"

double get_tallness (int height, int width) {
	double tallness;

	tallness = height / (double) width;

	return tallness;
}