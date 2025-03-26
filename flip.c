/*
  Name:     flip.c
  Purpose:  Generating a sequence of pseudo-random bits.
  Author:   CMU Probabilistic Computing Systems Lab
  Copyright (C) 2025 CMU Probabilistic Computing Systems Lab, All Rights Reserved.

  Released under Apache 2.0; refer to LICENSE.txt
*/

#include <stdlib.h>
#include <sys/random.h>

#include "flip.h"

uint64_t flip_k = 64;
uint64_t flip_word = 0;
uint64_t flip_pos = 0;

void check_refill(void) {
    if (flip_pos == 0) {
        getrandom(&flip_word, sizeof(flip_word), 0);
        flip_pos = flip_k;
    }
}

uint8_t flip(void){
    check_refill();
    --flip_pos;
    return (flip_word >> flip_pos) & 1;
}
