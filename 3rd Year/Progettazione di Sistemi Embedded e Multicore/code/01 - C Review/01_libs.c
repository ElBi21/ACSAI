#include <stdio.h>
#include <string.h>

int main() {
    /*for (int i = 0; i < 10; i++) {


    }*/
    int areEqual = strcmp("testo", "testa");
    printf("Are the strings equal? %d\n", areEqual);

    // Puntatori
    int* pointer = &areEqual;
    int* increasedPointer = pointer++;
    printf(
        "The value %d is contained in address %p\nThis is what's next in %p: %d",
        areEqual, pointer, increasedPointer, *increasedPointer
    );

    return 0;
}
