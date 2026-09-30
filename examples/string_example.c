#include "../rplib.h"

int main(void)
{
    char text[] = "rplib";

    Out("String: %s\n", text);
    Out("Length: %d\n", Len(text));

    RevStr(text);
    Out("Reversed: %s\n", text);

    return 0;
}
