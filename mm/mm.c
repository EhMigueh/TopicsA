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

static int main_dgemm(const int t, const int m, const int n, const int k, const int elements_type, const char *verbose);

int main(int argc, char **argv)
{
    fprintf(stdout, "dgemm: sample program for cblas_dgemm function.\n");
    fputc('\n', stdout);
    if (argc != 7)
    {
        fprintf(stdout, "Use: dgemm <m:int> <n:int> <k:int> <0|1|2> <on|off>.\n");
        return EXIT_FAILURE;
    }
    main_dgemm(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
    return EXIT_SUCCESS;
}

static int main_dgemm(const int t, const int m, const int n, const int k, const int elements_type, const char *verbose)
{
    double *A = NULL;
    double *B = NULL;
    double *C = NULL;
    double alpha = 1.0;
    double beta = 0.0;
    int lda = k;
    int ldb = n;
    int ldc = n;
    struct timeval start, finish;
    double runtime = 0.0; // seconds.
    int n_aux;
    int m_aux;
    int k_aux;
    assert(m > 0);
    assert(n > 0);
    assert(k > 0);
    assert(elements_type >= ZEROS && elements_type <= RAND);
    A = array_new(m, k, elements_type);
    assert(A != NULL);
    B = array_new(k, n, elements_type);
    assert(B != NULL);
    C = array_new(m, n, ZEROS);
    assert(C != NULL);

    omp_set_num_threads(t);
    n_aux = n / t;
    m_aux = m / t;
    k_aux = k / t;
    gettimeofday(&start, NULL);
#pragma omp parallel
    {
        int p = omp_get_thread_num();
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                    m_aux, n, k, alpha, A + m_aux * p * k, lda, B, ldb, beta, C + m_aux * p * n, ldc);
    }

    gettimeofday(&finish, NULL);
    if (strcmp(verbose, "on") == 0)
    {
        array_show(m, k, A, "A");
        array_show(k, n, B, "B");
    }
    array_show(m, n, C, "C");
    runtime = timeval_diff(&finish, &start);
    fprintf(stdout, "Data: %d %lf\n", m, runtime);
    // free(A);
    // free(B);
    // free(C);
    return EXIT_SUCCESS;
}
