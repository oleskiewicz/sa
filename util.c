#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_qrng.h>

void
gsl_vector_print(gsl_vector * V)
{
	for (size_t i = 0; i < V->size; i++) {
		printf("%.5f ", gsl_vector_get(V, i));
	}
	printf("\n");
}

void
gsl_matrix_print(gsl_matrix * M)
{
	for (size_t i = 0; i < M->size1; i++) {
		for (size_t j = 0; j < M->size2; j++) {
			printf("%.5f ", gsl_matrix_get(M, i, j));
		}
		printf("\n");
	}
}
