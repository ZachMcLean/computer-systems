#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
#define MAX_LENGTH 25

typedef struct {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char zipCode[MAX_LENGTH];
    char department[MAX_LENGTH];
    int salary;
} Struct_Employee_Info;

char* searchByName(Struct_Employee_Info employees[], int count, const char *firstName, const char *lastName) {
    char *result = malloc(MAX_SIZE * sizeof(char));
    bzero(result, MAX_SIZE);

    for (int i = 0; i < count; i++) {
        if (strcmp(employees[i].firstName, firstName) == 0 && strcmp(employees[i].lastName, lastName) == 0) {
            char record[MAX_SIZE];
            snprintf(record, MAX_SIZE, "Name: %s %s, ZipCode: %s, Department: %s, Salary: %d\n",
                     employees[i].firstName, employees[i].lastName, employees[i].zipCode, employees[i].department, employees[i].salary);
            strcat(result, record);
        }
    }

    return result;
}

char* searchByZipCode(Struct_Employee_Info employees[], int count, const char *zipCode) {
    char *result = malloc(MAX_SIZE * sizeof(char));
    bzero(result, MAX_SIZE);

    for (int i = 0; i < count; i++) {
        if (strcmp(employees[i].zipCode, zipCode) == 0) {
            char record[MAX_SIZE];
            snprintf(record, MAX_SIZE, "Name: %s %s, ZipCode: %s, Department: %s, Salary: %d\n",
                     employees[i].firstName, employees[i].lastName, employees[i].zipCode, employees[i].department, employees[i].salary);
            strcat(result, record);
        }
    }

    return result;
}

char* searchBySalary(Struct_Employee_Info employees[], int count, int salary, const char *comparisonOperator) {
    char *result = malloc(MAX_SIZE * sizeof(char));
    bzero(result, MAX_SIZE);

    for (int i = 0; i < count; i++) {
        int match = 0;

        if (strcmp(comparisonOperator, ">") == 0 && employees[i].salary > salary) match = 1;
        else if (strcmp(comparisonOperator, "<") == 0 && employees[i].salary < salary) match = 1;
        else if (strcmp(comparisonOperator, ">=") == 0 && employees[i].salary >= salary) match = 1;
        else if (strcmp(comparisonOperator, "<=") == 0 && employees[i].salary <= salary) match = 1;
        else if (strcmp(comparisonOperator, "==") == 0 && employees[i].salary == salary) match = 1;

        if (match) {
            char record[MAX_SIZE];
            snprintf(record, MAX_SIZE, "Name: %s %s, ZipCode: %s, Department: %s, Salary: %d\n",
                     employees[i].firstName, employees[i].lastName, employees[i].zipCode, employees[i].department, employees[i].salary);
            strcat(result, record);
        }
    }

    return result;
}

int main() {
    FILE *file;
    Struct_Employee_Info employees[MAX_SIZE];
    char line[MAX_SIZE];
    int count = 0;

    file = fopen("records.csv", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",
               employees[count].firstName, employees[count].lastName,
               employees[count].zipCode, employees[count].department, &employees[count].salary);
        count++;
    }

    fclose(file);

    char *searchResult1 = searchByName(employees, count, "Jack", "Sparrow");
    printf("\nSearch Results by Name: %s %s\n", "Jack", "Sparrow");
    printf("%s", searchResult1);
    free(searchResult1);

    char *searchResult2 = searchByZipCode(employees, count, "37128");
    printf("\nSearch Results by Zip Code: %s\n", "37128");
    printf("%s", searchResult2);
    free(searchResult2);

    char *searchResult3 = searchBySalary(employees, count, 45000, ">=");
    printf("\nSearch Results by Salary: %s %d\n", ">=", 45000);
    printf("%s", searchResult3);
    free(searchResult3);

    char *searchResult4 = searchBySalary(employees, count, 500000, "==");
    printf("\nSearch Results by Salary: %s %d\n", "==", 500000);
    printf("%s", searchResult4);
    free(searchResult4);

    return 0;
}

