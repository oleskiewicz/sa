#include <err.h>
#include <sysexits.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_qrng.h>

#include "util.h"

gsl_matrix *
sa_sample_halton(int d, int n) {
	double row[d];
	gsl_matrix *A = gsl_matrix_alloc(n, d);
	gsl_qrng *halton_generator = gsl_qrng_alloc(gsl_qrng_halton, d);

	for(int i = 0; i < n; i++) {
		gsl_qrng_get(halton_generator, row);
		for(int j = 0; j < d; j++) {
			gsl_matrix_set(A, i, j, row[j]);
		}
	}

	gsl_qrng_free(halton_generator);
	return A;
}

int
main(int argc, char **argv) {
	if(argc != 3)
		errx(EX_USAGE, "usage: %s N D\n", argv[0]);

	int n = atoi(argv[1]), d = atoi(argv[2]);
	gsl_matrix *A;

	A = sa_sample_halton(d, n);
	gsl_matrix_print(A);

	gsl_matrix_free(A);
	return 0;
}
