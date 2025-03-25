/*
  Name:     aldr.h
  Purpose:  Fast sampling of random integers.
  Author:   CMU Probabilistic Computing Systems Lab
  Copyright (C) 2025 CMU Probabilistic Computing Systems Lab, All Rights Reserved.

  Released under Apache 2.0; refer to LICENSE.txt
*/

#ifndef ALDR_H
#define ALDR_H

#include <stdint.h>

// flattened ALDR tree
struct aldr_s {
    uint32_t length_breadths;
    uint32_t length_leaves_flat;
    uint32_t *breadths;
    uint32_t *leaves_flat;
};

void aldr_free (struct aldr_s x);
struct aldr_s aldr_preprocess(uint32_t* a, uint32_t n);
uint32_t aldr_sample(struct aldr_s *x);

#endif
