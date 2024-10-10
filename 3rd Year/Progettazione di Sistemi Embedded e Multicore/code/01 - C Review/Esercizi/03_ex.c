#include <stdio.h>

int main () {
    int a, i;
    printf("Inserisci il tuo numero a: ");
    scanf("%d", &a);
    i = 0;

    while (i <= a) {
        printf("%d\n", i);
        i++;
    }

    i = a;
    while (i >= 0) {
        printf("%d\n", i);
        i--;
    }

    return 0;
}
