#include "../rplib.h"

int main(void)
{
    int a[5] = {5, 2, 8, 1, 3};

    Out("Original array:\n");
    Print(a, 5);

    Sort(a, 5);

    Out("\nSorted array:\n");
    Print(a, 5);

    Out("\nSum = %d\n", Sum(a, 5));
    Out("Maximum = %d\n", MaxA(a, 5));
    Out("Minimum = %d\n", MinA(a, 5));

    return 0;
}
