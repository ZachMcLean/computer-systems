#include <stdio.h>
#include <ctype.h>

void convertTemperature(char from, char to, double value) {
    double convertedValue;

    if (from == 'F') {
        if (to == 'C') {
            convertedValue = (value - 32) * 5.0 / 9;
        } else if (to == 'K') {
            convertedValue = (value - 32) * 5.0 / 9 + 273.15;
        } else {
            printf("Invalid target scale.\n");
            return;
        }
    } else if (from == 'C') {
        if (to == 'F') {
            convertedValue = (value * 9.0 / 5) + 32;
        } else if (to == 'K') {
            convertedValue = value + 273.15;
        } else {
            printf("Invalid target scale.\n");
            return;
        }
    } else if (from == 'K') {
        if (to == 'C') {
            convertedValue = value - 273.15;
        } else if (to == 'F') {
            convertedValue = (value - 273.15) * 9.0 / 5 + 32;
        } else {
            printf("Invalid target scale.\n");
            return;
        }
    } else {
        printf("Invalid starting scale.\n");
        return;
    }

    printf("Converted value: %.2f %c\n", convertedValue, to);
}

int main() {
    char fromScale, toScale;
    double temperature;

    printf("Enter the starting temperature scale (F, C, or K): ");
    scanf(" %c", &fromScale);
    fromScale = toupper(fromScale);

    printf("Enter the target temperature scale (F, C, or K): ");
    scanf(" %c", &toScale);
    toScale = toupper(toScale);

    printf("Enter the temperature value to be converted: ");
    scanf("%lf", &temperature);

    convertTemperature(fromScale, toScale, temperature);

    return 0;
}

// int main (){
//
//   char start;
//   char target;
//   int tempInput;
//   int tempOutput;
//
//   printf("Enter starting temperature scale (F/C/K): ");
//   scanf("%d", &start);
//   printf("\nEnter target temperature scale (F/C/K): ");
//   scanf("%d", &target);
//
//   printf("\nEnter temperature value: ");
//   scanf("%d", &tempInput);
//
//   if (start == 'F' && target == 'C'&start){
//     tempOutput = (start - 32) * (5/9);
//   }
//   else if (start == 'C' && target == 'F') {
//     tempOutput = (start * (9.0/5.0) + 32);
//   }
//   else if (start == 'C' && targer == 'K') {
//     tempOutput = (start + 273.15);
//   }
//   else if (start == 'K' && target == 'C') {
//     tempOutput = (start - 273.15);
//   }
//   else if (start == 'F' && target == 'K') {
//     tempOutput = ((start - 32) * (5.0/9.0) +273.15);
//   }
//   else if (start == 'K' && target == 'F') {
//     tempOutput = ((start - 273.15) * ( 9.0/5.0) + 32);
//   }
//
//
//   printf("%d %f is equivalent to %d %f", &start);
//
//   return 0;
// }
