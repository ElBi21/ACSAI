#include <stdio.h>
#include <string.h>

int main() {
    char strArray[10];

    printf("Insert your string: ");
    scanf("%s", strArray);

    printf("%s", strArray);

    char* arrayPointer = &strArray[0];
    while (*arrayPointer != '\0') {
        if ((*arrayPointer >= '0') && (*arrayPointer <= '9'))
            *arrayPointer = '*';
        arrayPointer++;
    }

    printf("Here is the result: %s", strArray);
    return 0;
}
