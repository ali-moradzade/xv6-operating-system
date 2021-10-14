#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    printf(1, "value returned by getProcCount: %d\n", getProcCount());
    printf(1, "\ngetProcCount --> successful\n\n");
    exit();
}