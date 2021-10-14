#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    printf(1, "value returned by getReadCount: %d\n", getReadCount());
    printf(1, "\ngetReadCount --> successful\n\n");
    exit();
}