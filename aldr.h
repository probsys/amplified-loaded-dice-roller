/*
  Name:     aldr.h
  Purpose:  Fast sampling of random integers.
  Author:   CMU Probabilistic Computing Systems Lab
  Copyright (C) 2025 CMU Probabilistic Computing Systems Lab, All Rights Reserved.

  Released under Apache 2.0; refer to LICENSE.txt
*/

#ifndef ALDR_H
#define ALDR_H

// flattened ALDR tree
struct aldr_s {
    int length_breadths;
    int length_leaves_flat;
    int *breadths;
    int *leaves_flat;
};

void aldr_free (struct aldr_s x);
struct aldr_s aldr_preprocess(int* a, int n);
int aldr_sample(struct aldr_s *x);

#endif
