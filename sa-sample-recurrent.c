#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <sysexits.h>
#include <math.h>


static inline double
phi(double d, int precision) {
	double x = 2.0;
	for(int i = 0; i < precision; i++)
		x = pow(1.0+x, 1.0/(d+1.0));
	return x;
}

static inline double
recurrence(int n, double s, double alpha) {
	double r_whole, r_frac;
	r_frac = modf(s + n*alpha, &r_whole);
	return r_frac;
}


int
main(int argc, char **argv) {
	if(argc != 3)
		errx(EX_USAGE, "usage: %s N D\n", argv[0]);

	int n = atoi(argv[1]), d = atoi(argv[2]);

	int precision = 10;
	double seed = 0.5;

	double alpha[d];
	for(int j = 0; j < d; j++) {
		alpha[j] = pow(1.0/phi(d, precision), 1.0+j);
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < d; j++) {
			printf("%.5f ", recurrence(i+1, seed, alpha[j]));
		}
		printf("\n");
	}

	return 0;
}
