// Zach McLean
// File Handling

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char buffer[11]; // 10 characters + null terminator
    int index = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (isprint(ch)) {
            buffer[index] = ch;
        } else {
            buffer[index] = '.';
        }
        index++;

        if (index == 10) {
            buffer[index] = '\0'; // null-terminate the string
            printf("%s\n", buffer);
            index = 0; // reset index for next set of characters
        }
    }

    // Print any remaining characters in the buffer
    if (index > 0) {
        buffer[index] = '\0'; // null-terminate the string
        printf("%s\n", buffer);
    }

    fclose(file);
    return 0;
}


