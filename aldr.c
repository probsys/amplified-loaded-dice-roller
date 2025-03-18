/*
  Name:     aldr.c
  Purpose:  Fast sampling of random integers.
  Author:   CMU Probabilistic Computing Systems Lab
  Copyright (C) 2025 CMU Probabilistic Computing Systems Lab, All Rights Reserved.

  Released under Apache 2.0; refer to LICENSE.txt
*/

#include <stdlib.h>

#include "flip.h"
#include "aldr.h"

void aldr_free (struct aldr_s x) {
    free(x.breadths);
    free(x.leaves_flat);
}

struct aldr_s aldr_preprocess(int* a, int n) {
    // assume k <= 31
    int m = 0;
    for (int i = 0; i < n; ++i) {
        m += a[i];
    }
    int k = 32 - __builtin_clz(m) - (1 == __builtin_popcount(m));
    int K = k << 1;                         // depth
    long long c = (1ll << K) / m;           // amplification factor
    long long r = (1ll << K) % m;           // reject weight

    int num_leaves = __builtin_popcountll(r);
    for (int i = 0; i < n; ++i) {
        num_leaves += __builtin_popcountll(c * a[i]);
    }

    int *breadths = calloc(K + 1, sizeof(int));
    int *leaves_flat = calloc(num_leaves, sizeof(int));

    int location = 0;
    for(int j = 0; j <= K; j++) {
        long long bit = (1ll << (K - j));
        if (r & bit) {
            leaves_flat[location] = 0;
            ++breadths[j];
            ++location;
        }
        for (int i = 0; i < n; ++i) {
            long long Qi = c*a[i];
            if (Qi & bit) {
                leaves_flat[location] = i + 1;
                ++breadths[j];
                ++location;
            }
        }
    }

    return (struct aldr_s){
            .length_breadths = K+1,
            .length_leaves_flat = num_leaves,
            .breadths = breadths,
            .leaves_flat = leaves_flat
        };
}

int aldr_sample(struct aldr_s* f) {
    for (;;) {
        int depth = 0;
        int location = 0;
        int val = 0;
        for (;;) {
            if (val < f->breadths[depth]) {
                int ans = f->leaves_flat[location + val];
                if (ans) return ans - 1;
                else break;
            }
            location += f->breadths[depth];
            val = ((val - f->breadths[depth]) << 1) | flip();
            ++depth;
        }
    }
}
