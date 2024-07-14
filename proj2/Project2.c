/* 
 * CSCI3240: Project 2
 * 
 * Zach McLean zmm2t
 *
 * Project2.c - Source file with your solutions to the Lab.
 *          This is the file you will submit in the D2L -> Project2 dropbox.
 *
 *   Make sure you have insightful comments in your code. 
 * 
 */


long MysteryFunction1(long n){

   //TODO
   //check assembly code for MysteryFunction1 in project2.s
   long result = 1; // 'movl $1, %eax'
   while (n > 0) {  // 'testl %esi, %esi' and 'jg .L3'
      result *= n; // 'imulq %rdi, %rax'
      n--;         // 'leal -1(%rsi), %edx'
   }
   return result;

unsigned int MysteryFunction2(unsigned int x)
{
   //TODO
   //check assembly code for MysteryFunction2 in project2.s
    unsigned int result = 0;  // 'movl $0, %edx'
    for (unsigned int i = 0; i < 32; i++) {  // Loop from 0 to 31
       if (x & (1 << i)) {  // 'testl %edi, %eax'
            result |= (1 << (31 - i));  // 'shrl %cl, %eax' and 'orl %eax, %edx'
       }
    }
    return result;
}

long MysteryFunction3(long *arr, int length){
   //TODO
   //check assembly code for MysteryFunction3 in project2.s
    long max_value = arr[0];  // Initialize max_value with the first element of the array
    for (int i = 1; i < length; i++) {  // Iterate over the array starting from the second element
        if (arr[i] > max_value) {  // Compare each element with the current max_value
            max_value = arr[i];  // Update max_value if the current element is greater
        }
    }
    return max_value;  // Return the maximum value found in the array
}

int MysteryFunction4(unsigned long x)
{
      //TODO
   //check assembly code for MysteryFunction4 in project2.s
    int count = 0;  // 'movl $0, %eax'
    while (x != 0) {  // 'testq %rdi, %rdi' and 'jne .L17'
        count += x & 1;  // 'andl $1, %edx' and 'addl %edx, %eax'
        x >>= 1;  // 'shrq %rdi'
    }
    return count;
}



unsigned int MysteryFunction5(unsigned int a, unsigned int b)
{
  //TODO
   //check assembly code for MysteryFunction5 in project2.s
    int x = a ^ b;  // 'xorl %esi, %edi'
    int count = 0;  // 'movl $0, %eax'
    while (x != 0) {  // 'testl %edi, %edi' and 'jne .L20'
        count += x & 1;  // 'andl $1, %edx' and 'addl %edx, %eax'
        x >>= 1;  // 'sarl %edi'
    }
    return count;
}

