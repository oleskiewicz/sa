#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#define PREC 1000

static inline double
phi(double d)
{
	double x = 2.0;
	for (int i = 0; i < PREC; i++)
		x = pow(1.0 + x, 1.0 / (d + 1.0));
	return x;
}

static inline double
recurrence(int n, double s, double alpha)
{
	double r_whole, r_frac;
	r_frac = modf(s + n * alpha, &r_whole);
	return r_frac;
}

int
main(int argc, char **argv)
{
	if (argc < 3)
		errx(EX_USAGE, "usage: %s N D [seed]\n", argv[0]);

	int n = atoi(argv[1]), d = atoi(argv[2]);
	double p = phi(d);
	double alpha[d];

	double seed;
	if (argc == 4)
		seed = atof(argv[3]);
	else
		seed = 0.5;

	for (int j = 0; j < d; j++)
		alpha[j] = pow(1.0 / p, 1.0 + j);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < d; j++) {
			printf("%.5f ", recurrence(i + 1, seed, alpha[j]));
		}
		printf("\n");
	}

	return 0;
}
