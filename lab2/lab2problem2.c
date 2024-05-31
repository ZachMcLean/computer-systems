// Zach McLean
// CSCI 3240
// Loops & Functions
// Lab 2 | Problem 2

#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial(int num) {
    unsigned long long fact = 1;
    for (int i = 1; i <= num; i++) {
        fact *= i;
    }
    return fact;
}

// Function to calculate permutation P(n, r)
unsigned long long permutation(int n, int r) {
    return factorial(n) / factorial(n - r);
}

// Function to calculate combination C(n, r)
unsigned long long combination(int n, int r) {
    return permutation(n, r) / factorial(r);
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 3) {
        printf("Usage: %s <n> <r>\n", argv[0]);
        return 1; 
    }

    // Convert the command line arguments to integers
    int n = atoi(argv[1]);
    int r = atoi(argv[2]);

    // Check if n and r are within the valid range
    if (n < 1 || n > 20 || r < 1 || r > 20) {
        printf("Error: n and r must be between 1 and 20\n");
        return 1; // Return with error code if n or r are out of range
    }

    unsigned long long perm = permutation(n, r);
    unsigned long long comb = combination(n, r);

    printf("P(%d,%d) = %llu\n", n, r, perm);
    printf("C(%d,%d) = %llu\n", n, r, comb);

    return 0; 
}
