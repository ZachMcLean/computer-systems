#include <stdio.h>

// int main() {
//     int **ptr;
//     int num = 25;
//     *ptr = &num;
//     printf("%d", **ptr);
//     return 0;
// }
int main() {
    char *names[] = {"Alice", "Bob", "Charlie"};
    printf("%c", names[1][0]);
    return 0;
}


// int main(){
  // float a = 17.5;
  // float b = 43.5;
  // float *ptr = &a;
  // (*ptr)++;
  // *ptr =b;
  // printf("%.02f %.02f %.02f\n", *ptr, a, b);
  
// int *ptr = 30;
// int a = 10;
// *ptr = a;
// printf("%d\n",*ptr); 
// }
