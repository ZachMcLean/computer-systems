// Zach McLean
// Project 1
 

#include <stdio.h>
#include <stdlib.h>

// Function to print a single byte in hex
void print_hex_byte(unsigned char byte) {
    printf("%02x", byte);
}

// Function to print a single byte as a printable character or a dot
void print_printable_char(unsigned char byte) {
    if (byte >= 32 && byte <= 126) { // Check if the character is printable
        printf("%c", byte);
    } else {
        printf("."); // Print a dot for non-printable characters
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file in binary mode
    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    unsigned char buffer[16];
    size_t bytesRead;
    long offset = 0;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        // Print the offset
        printf("%08lx: ", offset);

        // Print hex values
        for (size_t i = 0; i < bytesRead; i++) {
            print_hex_byte(buffer[i]);
            if (i % 2 == 1) printf(" ");
        }

        // Add padding if necessary
        for (size_t i = bytesRead; i < sizeof(buffer); i++) {
            printf("  ");
            if (i % 2 == 1) printf(" ");
        }

        // Print printable characters
        for (size_t i = 0; i < bytesRead; i++) {
            print_printable_char(buffer[i]);
        }

        printf("\n");
        offset += sizeof(buffer);
    }

    fclose(file);
    return 0;
}
