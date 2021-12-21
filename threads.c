#include "types.h"
#include "stat.h"
#include "user.h"
#include <stdbool.h>

int stack[4096] __attribute__ ((aligned (4096)));
int x = 0;

int main(int argc, char *argv[]) {
  int tid = threadCreate(stack);

  if (tid < 0) {
    printf(2, "error!\n");
  } else if (tid == 0) {
    // child
    while (true) {
      x++;
      sleep(100);
    }
  } else {
    // parent
    while (true) {
      printf(1, "x = %d\n", x);
      sleep(100);
    }
  }

  exit();
}
