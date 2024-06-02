#include <stdio.h>

int main() {
  char a = 0x69;
  char b = 0x55;
  char c = a & b;
  printf("%x & %x = %x\n", a,b,c);
  return 0;
}
