# The Amplified Loaded Dice Roller

This repository contains a reference implementation in C of the Amplified
Loaded Dice Roller (ALDR), a fast algorithm for generating rolls of an
$n$-sided die with rational probabilities.
The method is described in the following [article](https://arxiv.org/abs/2504.04267)

_Efficient Rejection Sampling in the Entropy-Optimal Range_.
Thomas L. Draper, Feras A. Saad.
arXiv:2504.04267 [cs.DS], 2025.
https://doi.org/10.48550/arXiv.2504.04267

## Installation

The library can be built by running

```sh
make all
```

This command creates the following artifacts in the `build/` directory:

| Path                  | Description                                     |
| --------              | -------                                         |
| `build/bin/aldr`      | Executable for command line interface to ALDR   |
| `build/include`       | Header files for C programs that use ALDR       |
| `build/lib/libaldr.a` | Static library for C programs that use ALDR     |


## Usage

The following code from [examples/example.c](examples/example.c)
shows how to use ALDR to sample from a distribution
defined by a list of nonnegative integer weights.

```c
#include <stdlib.h>
#include <stdio.h>
#include "aldr.h"

int main(int argc, char **argv) {
    int num_samples = 90;
    int *samples = calloc(num_samples, sizeof(*samples));

    int distribution[5] = { 1, 1, 2, 3, 2 };
    struct aldr_s x = aldr_preprocess(distribution, 5);
    for (int i = 0; i < num_samples; ++i) {
        samples[i] = aldr_sample(&x);
        printf("%d ", samples[i]);
    }
    printf("\n");

    free(samples);
    aldr_free(x);
}
```

## Usage (Command Line Interface)

The executable in `build/bin/aldr` has the following command line interface:

```
usage: ./build/bin/aldr <num_samples> <distribution>
```

where `<num_samples>` is an integer denoting the number of samples to draw,
satisfying `0 <= num_samples <= 2147483647`;
and `<distribution>` is a space-separated list of positive integer weights
for the desired discrete distribution,
with the total number of elements bounded as `0 < n <= 2147483647`,
and the sum bounded as `0 < m <= 2147483647`.

For example, to generate 90 samples from { 1, 1, 2, 3, 2 }, run the following:

```sh
./build/bin/aldr 90 1 1 2 3 2
```

To generate 9000 samples from { 1, 1, 2, 3, 2 }
and count them as a histogram, run the following:

```sh
./build/bin/aldr 9000 1 1 2 3 2 | tr -d '\n' | tr ' ' '\n' | sort | uniq -c
```

## Experiments

Implementations of the experiments from the paper can be found at
https://github.com/probsys/amplified-loaded-dice-roller-experiments.

## Related Repositories

For a more space-efficient but less entropy-efficient rejection sampler, see
https://github.com/probsys/fast-loaded-dice-roller.
