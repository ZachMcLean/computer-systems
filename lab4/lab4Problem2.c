// Zach McLean

#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int main() {
    char inputUsername[MAX_USERNAME_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    FILE *file = fopen("userdata.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int matchFound = 0;

    while (fgets(line, sizeof(line), file)) {
        char storedUsername[MAX_USERNAME_LENGTH];
        char storedPassword[MAX_PASSWORD_LENGTH];
        int associatedData;

        // Parse the line to get the stored username, password, and associated data
        if (sscanf(line, "%s %s %d", storedUsername, storedPassword, &associatedData) == 3) {
            // Compare the input username and password with the stored ones
            if (strcmp(inputUsername, storedUsername) == 0 && strcmp(inputPassword, storedPassword) == 0) {
                printf("Associated data: %d\n", associatedData);
                matchFound = 1;
                break;
            }
        }
    }

    if (!matchFound) {
        printf("username/password mismatch!!!\n");
    }

    fclose(file);
    return 0;
}
