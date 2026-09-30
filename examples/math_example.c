#include "../rplib.h"

int main(void)
{
    int n = 28;

    Out("Number: %d\n", n);
    Out("Even: %d\n", IsEven(n));
    Out("Odd: %d\n", IsOdd(n));
    Out("Prime: %d\n", IsPrime(n));
    Out("Digits: %d\n", Digits(n));
    Out("GCD(28, 12): %d\n", GCD(28, 12));
    Out("LCM(28, 12): %d\n", LCM(28, 12));

    return 0;
}
