#include <stdio.h>
#include <stdlib.h>

void myfunc (int* pointer);

int main () {
    // Allochiamo della memoria per un intero
    int* p = malloc(sizeof(int));

    // Se malloc non riesce ad allocare della memoria (ad esempio se lo spazio è finito)
    // allora essa ritornerà NULL. Possiamo controllare che sia andato tutto a buon fine
    // mettendo un if statement che controlla se la malloc ha veramente ritornato un
    // puntatore verso la memoria
    if (p == NULL) {
        printf("Non è stato possibile allocare spazio in memoria!");
        return 0;
    }

    // Cambiamo il valore che si trova all'indirizzo definito da p
    *p = 30;
    printf("1) Il puntatore indica il dato %d\n", *p);

    myfunc(p);
    printf("2) Il puntatore indica il dato %d\n", *p);

    return 0;
}

//
void myfunc(int* pointer) {
    *pointer = 13;
}
