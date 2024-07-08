#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *numbers;
    int count;
    double result;
} AverageData;

typedef struct {
    int *numbers;
    int count;
    int result;
} MinMaxData;

void *calculate_average(void *arg) {
    AverageData *data = (AverageData *)arg;
    int sum = 0;
    for (int i = 0; i < data->count; i++) {
        sum += data->numbers[i];
    }
    data->result = (double)sum / data->count;
    pthread_exit(0);
}

void *calculate_maximum(void *arg) {
    MinMaxData *data = (MinMaxData *)arg;
    int max = data->numbers[0];
    for (int i = 1; i < data->count; i++) {
        if (data->numbers[i] > max) {
            max = data->numbers[i];
        }
    }
    data->result = max;
    pthread_exit(0);
}

void *calculate_minimum(void *arg) {
    MinMaxData *data = (MinMaxData *)arg;
    int min = data->numbers[0];
    for (int i = 1; i < data->count; i++) {
        if (data->numbers[i] < min) {
            min = data->numbers[i];
        }
    }
    data->result = min;
    pthread_exit(0);
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

    pthread_t threads[3];
    AverageData avg_data = {numbers, count, 0.0};
    MinMaxData max_data = {numbers, count, 0};
    MinMaxData min_data = {numbers, count, 0};

    pthread_create(&threads[0], NULL, calculate_average, &avg_data);
    pthread_create(&threads[1], NULL, calculate_maximum, &max_data);
    pthread_create(&threads[2], NULL, calculate_minimum, &min_data);

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("The average value is %.2f\n", avg_data.result);
    printf("The minimum value is %d\n", min_data.result);
    printf("The maximum value is %d\n", max_data.result);

    free(numbers);
    return 0;
}
