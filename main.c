#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
    tLista lista;
    crear_lista(&lista);

    tPosicion pos = l_primera(lista);
    tElemento e = malloc(sizeof(int));
    *(int*)e = 5;
    l_insertar(lista, pos, e);

    int numero = *(int*)(l_recuperar(lista, pos));
    printf("Value of element: %d\n", numero);
    return 0;
}
