/*
  Name:     example.c
  Purpose:  Example of running ALDR.
  Author:   CMU Probabilistic Computing Systems Lab
  Copyright (C) 2025 CMU Probabilistic Computing Systems Lab, All Rights Reserved.

  Released under Apache 2.0; refer to LICENSE.txt
*/

#include <stdlib.h>
#include <stdio.h>

#include "aldr.h"

int main(int argc, char **argv) {
    uint32_t num_samples = 90;
    uint32_t *samples = calloc(num_samples, sizeof(*samples));

    uint32_t distribution[5] = { 1, 1, 2, 3, 2 };
    struct aldr_s x = aldr_preprocess(distribution, 5);
    for (uint32_t i = 0; i < num_samples; ++i) {
        samples[i] = aldr_sample(&x);
        printf("%d ", samples[i]);
    }
    printf("\n");

    free(samples);
    aldr_free(x);
}
