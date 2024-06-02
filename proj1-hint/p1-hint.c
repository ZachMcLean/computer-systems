#include <stdio.h>

int main() {
  int i = 0;
  for (int i=0; i<1024; i+=16) {
    printf("%07x:\n", i);
  }
  return 0;
}
