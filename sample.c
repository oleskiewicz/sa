#include <err.h>
#include <sysexits.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_qrng.h>

#include "util.h"

int
main(int argc, char **argv) {
	int i, j, k, d, n;

	if(argc != 3)
		err(EX_USAGE, "usage: %s D N\n", argv[0]);

	d = atoi(argv[1]);
	n = atoi(argv[2]);
	double row[2 * d];

	gsl_vector *col = gsl_vector_alloc(d * n);
	gsl_vector *subcol = gsl_vector_alloc(n);
	gsl_matrix *A = gsl_matrix_alloc(n, d);
	gsl_matrix *B = gsl_matrix_alloc(n, d);
	gsl_matrix *AB = gsl_matrix_alloc(d * n, d);
	gsl_qrng *sobol_generator = gsl_qrng_alloc(gsl_qrng_sobol, 2 * d);

	for(i = 0; i < n; i++) {
		gsl_qrng_get(sobol_generator, row);
		for(j = 0; j < d; j++) {
			gsl_matrix_set(A, i, j, row[j]);
			gsl_matrix_set(B, i, j, row[d + j]);
		}
	}

	gsl_qrng_free(sobol_generator);

	for(k = 0; k < d; k++) {
		for(j = 0; j < d; j++) {
			if(j == k)
				gsl_matrix_get_col(subcol, B, k);
			else
				gsl_matrix_get_col(subcol, A, k);
			gsl_vector_view b = gsl_vector_subvector(col, j * n, n);
			gsl_vector_memcpy(&b.vector, subcol);
			gsl_matrix_set_col(AB, k, col);
		}
	}

	gsl_matrix_print(AB);

	gsl_matrix_free(A);
	gsl_matrix_free(B);
	gsl_matrix_free(AB);

	return 0;
}
