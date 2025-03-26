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

struct aldr_s aldr_preprocess(uint32_t* a, uint32_t n) {
    // this algorithm requires that
    // 0 < n < (1 << 32) - 1
    // 0 < sum(a) < (1 << 31) - 1
    uint32_t m = 0;
    for (uint32_t i = 0; i < n; ++i) {
        m += a[i];
    }
    uint8_t k = 32 - __builtin_clz(m-1);
    uint8_t K = k << 1;              // depth
    uint64_t c = (1ll << K) / m;           // amplification factor
    uint64_t r = (1ll << K) % m;           // reject weight

    uint32_t num_leaves = __builtin_popcountll(r);
    for (uint32_t i = 0; i < n; ++i) {
        num_leaves += __builtin_popcountll(c * a[i]);
    }

    uint32_t *breadths = calloc(K + 1, sizeof(*breadths));
    uint32_t *leaves_flat = calloc(num_leaves, sizeof(*leaves_flat));

    uint32_t location = 0;
    for(uint8_t j = 0; j <= K; j++) {
        uint64_t bit = (1ll << (K - j));
        if (r & bit) {
            leaves_flat[location] = 0;
            ++breadths[j];
            ++location;
        }
        for (uint32_t i = 0; i < n; ++i) {
            uint64_t Qi = c*a[i];
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

uint32_t aldr_sample(struct aldr_s* f) {
    for (;;) {
        uint32_t depth = 0;
        uint32_t location = 0;
        uint32_t val = 0;
        for (;;) {
            if (val < f->breadths[depth]) {
                uint32_t ans = f->leaves_flat[location + val];
                if (ans) return ans - 1;
                else break;
            }
            location += f->breadths[depth];
            val = ((val - f->breadths[depth]) << 1) | flip();
            ++depth;
        }
    }
}
