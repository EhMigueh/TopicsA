
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef ARRAY_H
#include "array.h"
#endif
#include <cblas.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>

static int main_dgemv(const int t, const int m, const int n, const int elements_type, const char *verbose);

int main(int argc, char **argv)
{
    fprintf(stdout, "dgemv: sample program for cblas_dgemv function.\n");
    fputc('\n', stdout);
    if (argc != 6)
    {
        fprintf(stdout, "Use: dgemv <m:int> <n:int> <0|1|2> <on|off>.\n");
        return EXIT_FAILURE;
    }
    main_dgemv(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
    return EXIT_SUCCESS;
}

static int main_dgemv(
    const int t,
    const int m,
    const int n,
    const int elements_type,
    const char *verbose)
{
    double *A = NULL;
    double *x = NULL;
    double *y = NULL;
    double alpha = 1.0;
    double beta = 0.0;
    int lda = n;
    int incx = 1;
    int incy = 1;
    int p, m_aux = 0;
    struct timeval start, finish;
    double runtime = 0.0; // seconds.
    assert(m > 0);
    assert(n > 0);
    assert(elements_type >= ZEROS && elements_type <= RAND);
    A = array_new(m, n, elements_type);
    assert(A != NULL);
    x = array_new(n, 1, elements_type);
    assert(x != NULL);
    y = array_new(m, 1, ZEROS);
    assert(y != NULL);
    omp_set_num_threads(t);
    m_aux = m / t;
    gettimeofday(&start, NULL);

#pragma omp parallel
    {
        p = omp_get_thread_num();
        cblas_dgemv(CblasRowMajor, CblasNoTrans, m_aux, n, alpha, A + m_aux * p * n, lda, x, incx, beta, y + m_aux * p, incy); // o A + m_aux *n
    }
    gettimeofday(&finish, NULL);
    if (strcmp(verbose, "on") == 0)
    {
        array_show(m, n, A, "A");
        array_show(n, 1, x, "x");
    }
    array_show(m, 1, y, "y");
    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", m, runtime);
    free(A);
    free(x);
    free(y);
    return EXIT_SUCCESS;
}
