// Zach McLean
// CSCI 3240
// Loops & Functions
// Lab 2 | Problem 1

#include <stdio.h>
#include <stdlib.h>

void printPattern(int n) {
    int size = 2 * n - 1; // Calculate the size of the pattern matrix

    // Iterate through each row
    for (int i = 0; i < size; i++) {
        // Iterate through each column
        for (int j = 0; j < size; j++) {
            // Find the minimum distance to the edges
            int min = i < j ? i : j;
            min = min < size - i - 1 ? min : size - i - 1;
            min = min < size - j - 1 ? min : size - j - 1;

            printf("%d ", n - min);
        }
        printf("\n"); 
    }
}

int main(int argc, char *argv[]) {
    // Check for the correct number of arguments
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1; // Return with error code if arguments are incorrect
    }

    // Convert the command line argument to an integer
    int n = atoi(argv[1]);

    // Check if n is within the valid range
    if (n < 1 || n > 9) {
        printf("Error: n must be between 1 and 9\n");
        return 1; // Return with error code if n is out of range
    }

    printPattern(n);

    return 0; 
}
