#include "../rplib.h"
#include <stdio.h>

int main(void)
{
    int a[5] = {5, 2, 8, 1, 3};

    /* Basic smoke tests. Adjust expectations if your implementation
       intentionally uses different return conventions. */

    if (Sum(a, 5) != 19) {
        printf("FAIL: Sum\n");
        return 1;
    }

    if (MaxA(a, 5) != 8) {
        printf("FAIL: MaxA\n");
        return 1;
    }

    if (MinA(a, 5) != 1) {
        printf("FAIL: MinA\n");
        return 1;
    }

    if (!IsEven(10) || !IsOdd(11)) {
        printf("FAIL: parity helpers\n");
        return 1;
    }

    if (GCD(12, 8) != 4) {
        printf("FAIL: GCD\n");
        return 1;
    }

    printf("Basic rplib tests passed.\n");
    return 0;
}
