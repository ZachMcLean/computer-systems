// Zach McLean
// Lab 10 Problem 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void calculate_average(int *numbers, int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    double average = (double)sum / count;
    printf("The average value is %.2f\n", average);
}

void calculate_maximum(int *numbers, int count) {
    int max = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    printf("The maximum value is %d\n", max);
}

void calculate_minimum(int *numbers, int count) {
    int min = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }
    printf("The minimum value is %d\n", min);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    int count = argc - 1;
    int *numbers = (int *)malloc(count * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    pid_t pid1, pid2, pid3;

    pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "Fork failed\n");
        free(numbers);
        return 1;
    } else if (pid1 == 0) {
        // First child process to calculate average
        calculate_average(numbers, count);
        free(numbers);
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "Fork failed\n");
        free(numbers);
        return 1;
    } else if (pid2 == 0) {
        // Second child process to calculate maximum
        calculate_maximum(numbers, count);
        free(numbers);
        exit(0);
    }

    pid3 = fork();
    if (pid3 < 0) {
        fprintf(stderr, "Fork failed\n");
        free(numbers);
        return 1;
    } else if (pid3 == 0) {
        // Third child process to calculate minimum
        calculate_minimum(numbers, count);
        free(numbers);
        exit(0);
    }

    // Parent process waits for all children to complete
    wait(NULL);
    wait(NULL);
    wait(NULL);

    free(numbers);
    return 0;
}
