#include "../rplib.h"

int main(void)
{
    int a[2][2] = {
        {1, 2},
        {3, 4}
    };

    Out("Matrix:\n");
    PrintMat(a, 2, 2);

    Out("Trace = %d\n", Trace(a, 2));

    return 0;
}
