#include <stdio.h>

int main () {
    int a, b;
    printf("Inserisci il tuo primo numero a: ");
    scanf("%d", &a);
    printf("Inserisci in tuo secondo numero b: ");
    scanf("%d", &b);

    if (a < b) {
        printf("%d è maggiore di %d\n", a, b);
    } else if (a == b) {
        printf("%d è uguale a %d\n", a, b);
    } else {
        printf("%d è minore di %d\n", a, b);
    }

    int sum = a + b;
    int product = a * b;

    printf("La somma è uguale a %d\nIl prodotto è uguale a %d", sum, product);
    return 0;
}
