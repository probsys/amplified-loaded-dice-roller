/*
  Name:     sample.c
  Purpose:  Command line interface for aldr.
  Author:   CMU Probabilistic Computing Systems Lab
  Copyright (C) 2025 CMU Probabilistic Computing Systems Lab, All Rights Reserved.

  Released under Apache 2.0; refer to LICENSE.txt
*/

#include <stdio.h>
#include <stdlib.h>

#include "aldr.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("usage: %s <num_samples> <distribution>\n", argv[0]);
        exit(0);
    }
    uint32_t num_samples = strtoul(argv[1], NULL, 10);

    // Parse the distribution.
    uint32_t n = argc - 2;
    uint32_t *a = calloc(n, sizeof(*a));
    for (uint32_t i = 0; i < n; ++i) {
        a[i] = strtoul(argv[i + 2], NULL, 10);
    }

    // Obtain the samples.
    uint32_t sample;
    struct aldr_s x = aldr_preprocess(a, n);
    for (uint32_t i = 0; i < num_samples; ++i) {
        printf("%d ", aldr_sample(&x));
    }
    printf("\n");

    // Free the heap.
    free(a);
    aldr_free(x);

    return 0;
}
