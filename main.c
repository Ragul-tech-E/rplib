#include "rplib.h"

int main(void)
{
    int a[5] = {5, 2, 8, 1, 3};

    Out("rplib.h demonstration\n");
    Out("----------------------\n");

    Out("Original:\n");
    Print(a, 5);

    Sort(a, 5);

    Out("Sorted:\n");
    Print(a, 5);

    Out("Sum = %d\n", Sum(a, 5));
    Out("Max = %d\n", MaxA(a, 5));
    Out("Min = %d\n", MinA(a, 5));

    return 0;
}
