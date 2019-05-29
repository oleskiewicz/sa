#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <math.h>
#include <gsl/gsl_blas.h>

#include "util.h"

void
sa_analyse_saltelli(gsl_vector * Y, int n, int d) {
	for(int i = 0; i < d; i++) {
		double s = 0.0, st = 0.0;
		for(int j = 0; j < n; j++) {
			double a = gsl_vector_get(Y, j),
				b = gsl_vector_get(Y, j + n),
				ab = gsl_vector_get(Y, j + n + (n * (i + 1)));

			s += b * (ab - a);
			st += pow(a - ab, 2.0);
		}

		s /= (double)n;
		st /= 2.0 * (double)n;

		printf("%f\t%f\n", s, st);
	}
}

int
main(int argc, char **argv) {
	if(argc != 3) {
		fprintf(stderr, "usage: %s n d\n", argv[0]);
		return EX_USAGE;
	}
	int n = atoi(argv[1]), d = atoi(argv[2]);
	gsl_vector *Y = gsl_vector_alloc(n * (2 + d));
	if(gsl_vector_fscanf(stdin, Y) != 0) {
		fprintf(stderr, "error: not read correctly\n");
		return 1;
	}

	sa_analyse_saltelli(Y, n, d);

	return 0;
}
