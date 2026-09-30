#include "../rplib.h"

int main(void)
{
    int a[6] = {10, 20, 10, 40, 30, 20};

    Out("Array:\n");
    Print(a, 6);

    Out("Sum = %d\n", Sum(a, 6));
    Out("Average = %.2f\n", Avg(a, 6));
    Out("Maximum = %d\n", MaxA(a, 6));
    Out("Minimum = %d\n", MinA(a, 6));
    Out("Count of 20 = %d\n", Count(a, 6, 20));

    return 0;
}
