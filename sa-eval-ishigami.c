#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <math.h>

double
ishigami(double *x, double a, double b) {
	return sin(x[0]) + a * pow(sin(x[1]), 2.0) + b * pow(x[2], 4.0) * sin(x[0]);
}

int
main(int argc, char **argv) {
	if(argc != 3) {
		fprintf(stderr,
			"usage: %s a b\n"
			"\ty = sin(x[0]) + a * x[1]**2 + b * x[2]**4 * sin(x[0])\n",
			argv[0]);
		return EX_USAGE;
	}
	double a = atof(argv[1]), b = atof(argv[2]);
	double x[3];

	while(scanf("%lf %lf %lf", &x[0], &x[1], &x[2]) == 3) {
		printf("%lf\n", ishigami(x, a, b));
	}

	return 0;
}
