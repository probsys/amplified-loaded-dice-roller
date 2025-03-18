/*
  Name:     sample.c
  Purpose:  Command line interface for aldr.
  Author:   CMU Probabilistic Computing Systems Lab
  Copyright (C) 2025 CMU Probabilistic Computing Systems Lab, All Rights Reserved.

  Released under Apache 2.0; refer to LICENSE.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "aldr.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("usage: %s <n> <dist>\n", argv[0]);
        exit(0);
    }
    srand(time(NULL));
    int num_samples = atoi(argv[1]);

    // Parse the distribution.
    int n = argc - 2;
    int *a = calloc(n, sizeof(*a));
    for (int i = 0; i < n; ++i) {
        a[i] = atoi(argv[i + 2]);
    }

    // Obtain the samples.
    int sample;
    struct aldr_s x = aldr_preprocess(a, n);
    for (int i = 0; i < num_samples; ++i) {
        printf("%d ", aldr_sample(&x));
    }
    printf("\n");

    // Free the heap.
    free(a);
    aldr_free(x);

    return 0;
}
