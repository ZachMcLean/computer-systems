#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 50
#define MAX_WORD_LENGTH 20

// Function to check if a character is a vowel
int isVowel(char ch) {
    ch = tolower(ch);
    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
}

// Function to capitalize a word
void capitalizeWord(char* word) {
    word[0] = toupper(word[0]);
}

// Function to compare two strings (used for sorting)
int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {
    char input[1024];
    char* words[MAX_WORDS];
    int wordCount = 0;

    printf("Enter a line of text: ");
    fgets(input, sizeof(input), stdin);

    // Tokenize the input string into words
    char* token = strtok(input, " \n");
    while (token != NULL) {
        words[wordCount] = token;
        wordCount++;
        token = strtok(NULL, " \n");
    }

    // Array to hold words that start with a vowel
    char* vowelWords[MAX_WORDS];
    int vowelWordCount = 0;

    // Process each word
    for (int i = 0; i < wordCount; i++) {
        if (isVowel(words[i][0])) {
            capitalizeWord(words[i]);
            vowelWords[vowelWordCount] = words[i];
            vowelWordCount++;
        }
    }

    // // Sort the vowel words in ascending order
    // qsort(vowelWords, vowelWordCount, sizeof(char*), compareStrings);

    // Print the vowel words
    printf("Words starting with a vowel (capitalized and sorted):\n");
    for (int i = 0; i < vowelWordCount; i++) {
        printf("%s\n", vowelWords[i]);
    }

    return 0;
}

