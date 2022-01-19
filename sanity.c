#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
	if (argc!=2)
		    printf(1, "should get number(n) as parameter!\n");
	else
		    printf(1, "got num %x\n", argv[1]);
  // int i;

  // for(i = 1; i < argc; i++)
  //   printf(1, "%s%s", argv[i], i+1 < argc ? " " : "\n");
  exit();
}
