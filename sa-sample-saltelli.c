#include <err.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_qrng.h>
#include <sysexits.h>

#include "util.h"

gsl_matrix *
sa_sample_saltelli(int d, int n)
{
	double row[2 * d];
	gsl_vector *col = gsl_vector_alloc(d * n);
	gsl_vector *subcol = gsl_vector_alloc(n);
	gsl_matrix *A = gsl_matrix_alloc(n, d);
	gsl_matrix *B = gsl_matrix_alloc(n, d);
	gsl_matrix *AB = gsl_matrix_alloc(d * n, d);
	gsl_qrng *sobol_generator = gsl_qrng_alloc(gsl_qrng_sobol, 2 * d);

	// A, B matrices
	for (int i = 0; i < n; i++) {
		gsl_qrng_get(sobol_generator, row);
		for (int j = 0; j < d; j++) {
			gsl_matrix_set(A, i, j, row[j]);
			gsl_matrix_set(B, i, j, row[d + j]);
		}
	}
	gsl_qrng_free(sobol_generator);

	// AB matrix
	for (int k = 0; k < d; k++) {
		for (int j = 0; j < d; j++) {
			if (j == k)
				gsl_matrix_get_col(subcol, B, k);
			else
				gsl_matrix_get_col(subcol, A, k);
			gsl_vector_view b = gsl_vector_subvector(col, j * n, n);
			gsl_vector_memcpy(&b.vector, subcol);
			gsl_matrix_set_col(AB, k, col);
		}
	}

	// A, B, AB: concatenate vertically
	gsl_matrix *ABAB = gsl_matrix_alloc((d + 2) * n, d);
	gsl_matrix_view a = gsl_matrix_submatrix(ABAB, 0, 0, n, d);
	gsl_matrix_view b = gsl_matrix_submatrix(ABAB, n, 0, n, d);
	gsl_matrix_view ab = gsl_matrix_submatrix(ABAB, 2 * n, 0, n * d, d);
	gsl_matrix_memcpy(&a.matrix, A);
	gsl_matrix_memcpy(&b.matrix, B);
	gsl_matrix_memcpy(&ab.matrix, AB);

	gsl_matrix_free(A);
	gsl_matrix_free(B);
	gsl_matrix_free(AB);

	return ABAB;
}

int
main(int argc, char **argv)
{
	if (argc != 3)
		errx(EX_USAGE, "usage: %s N D\n", argv[0]);

	int n = atoi(argv[1]), d = atoi(argv[2]);
	gsl_matrix *AB;

	AB = sa_sample_saltelli(d, n);
	gsl_matrix_print(AB);

	gsl_matrix_free(AB);

	return 0;
}
