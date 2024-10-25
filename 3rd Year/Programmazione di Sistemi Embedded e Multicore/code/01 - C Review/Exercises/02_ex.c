#include <stdio.h>

int main () {
    int a;
    printf("Inserisci il tuo numero a: ");
    scanf("%d", &a);

    for (int i = 0; i <= a; i++) {
        printf("%d\n", i);
    }

    for (int i = a; i <= 0; a--) {
        printf("%d\n", a);
    }

    return 0;
}
