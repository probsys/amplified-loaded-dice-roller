/*
  Name:     flip.c
  Purpose:  Generating a sequence of pseudo-random bits.
  Author:   CMU Probabilistic Computing Systems Lab
  Copyright (C) 2025 CMU Probabilistic Computing Systems Lab, All Rights Reserved.

  Released under Apache 2.0; refer to LICENSE.txt
*/

#include <stdlib.h>
#include <stdint.h>

#include "flip.h"

// assume RAND_MAX is a Mersenne number
uint32_t flip_k = 32 - __builtin_clz(RAND_MAX);
uint32_t flip_word = 0;
uint32_t flip_pos = 0;

void check_refill(void) {
    if (flip_pos == 0) {
        flip_word = rand();
        flip_pos = flip_k;
    }
}

uint32_t flip(void){
    check_refill();
    --flip_pos;
    return (flip_word >> flip_pos) & 1;
}
