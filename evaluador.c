#include <stdio.h>
#include <stdlib.h>
#include "mapeo.h"

int hashString(void *c) {
    return 0;
}

int comparatorString(void *c1, void *c2) {
    return 0;
}

int main(int argc, char *argv[])
{
    FILE *file;
    tMapeo map;
    crear_mapeo(&map, 10, hashString, comparatorString);
    file = fopen("test.txt", "r");
    if (file==NULL) {
        printf("Error. El archivo no existe");
    }

    char str[20];
    tClave c;
    int * v;
    while (fscanf(file, "%s", str)!=EOF) {
        c = str;
        v = m_recuperar(map, c);
        if (v == NULL) {
            v = malloc(sizeof(int));
            *v = 0;

        }
        else {
            *v = (*v) + 1;
        }
        m_insertar(map, c, v);

    }

    return 0;
}
