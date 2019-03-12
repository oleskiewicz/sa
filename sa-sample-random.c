#include <err.h>
#include <sysexits.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_rng.h>

#include "util.h"

gsl_matrix *
sa_sample_random(int d, int n) {
	gsl_matrix *A = gsl_matrix_alloc(n, d);
	double a;

	const gsl_rng_type *T;
	gsl_rng *random_generator;
	gsl_rng_env_setup();
	T = gsl_rng_default;
	random_generator = gsl_rng_alloc(T);

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < d; j++) {
			a = gsl_rng_uniform(random_generator);
			gsl_matrix_set(A, i, j, a);
		}
	}

	gsl_rng_free(random_generator);
	return A;
}

int
main(int argc, char **argv) {
	if(argc != 3)
		errx(EX_USAGE, "usage: %s N D\n", argv[0]);

	int n = atoi(argv[1]), d = atoi(argv[2]);
	gsl_matrix *A;

	A = sa_sample_random(d, n);
	gsl_matrix_print(A);

	gsl_matrix_free(A);
	return 0;
}
