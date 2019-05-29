#include <gsl/gsl_blas.h>

void
gsl_vector_print(gsl_vector * V) {
	gsl_vector_fprintf(stdout, V, "%f");
}

void
gsl_matrix_print(gsl_matrix * M) {
	for(size_t i = 0; i < M->size1; i++)
		for(size_t j = 0; j < M->size2; j++)
			printf("%.5f%s", gsl_matrix_get(M, i, j), j == M->size2 - 1 ? "\n" : " ");
}
