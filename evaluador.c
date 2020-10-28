#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapeo.h"

void eliminarEntero(void * e) {
    free(e);
}

void eliminarString(void * e) {
    free(e);
}

int hashString(void * c) {
    int i;
    int hashCode = 0;
    char * string = (char *) c;
    int caracter;
    for (i=0; i<strlen(string); i++) {
        caracter = (int) *(string+i);
        if (caracter>=65 && caracter<=90) {
            caracter += 32; //Cambiamos de mayuscula a minuscula
        }
        hashCode += caracter * (i+1);
        //Valor ASCII del caracter, multiplicado por la posicion, considerando que la primerar posicion es el primer caracter
    }

    return hashCode;
}

//Compara dos strings
//Si son palabras, se transforman a minusculas para que, por ejemplo,
//la palabra "Hola" sea equivalente a "hola".
int comparatorString(void *c1, void *c2) {
    char * s1 = (char *) c1;
    char * s2 = (char *) c2;
    int letra1, letra2;
    int i = 0;
    int longitud = strlen(s1) > strlen(s2) ? strlen(s1) : strlen(s2);
    int resultado = 0;
    while (resultado == 0 && i<longitud) {
        letra1 = (int) *(s1+i);
        letra2 = (int) *(s2+i);
        if (letra1 < letra2) {
            resultado = -1;
        }
        else if (letra1 > letra2) {
            resultado = 1;
        }
        i++;
    }
    //printf("Comparar %s con %s: %d\n", s1, s2, resultado);
    return resultado;
}

int main(int argc, char *argv[]) {
    //Se crea el archivo de lectura
    FILE * file;
    tMapeo map;
    crear_mapeo(&map, 100, hashString, comparatorString);
    file = fopen("test.txt", "r");
    if (file==NULL) {
        printf("Error. El archivo no existe");
    }
    //printf("El archivo se tomo correctamente. \n"); //BORRAR
    //Se cargan las palabras del archivo a la tabla hash
    char str[20];
    tClave c;
    int * v;
    int * aux;
    tValor valor_viejo;
    while (fscanf(file, "%s", str)!=EOF) {
        //printf("Palabra leida: %s. \n", str); //BORRAR
        //printf("Longitud palabra preRecup: %i. \n", strlen(str)); //BORRAR
        aux = m_recuperar(map, str);
        //printf("Longitud palabra posRecu: %i. \n", strlen(str)); //BORRAR
        v = (int *) malloc(sizeof(int));
        if (aux == NULL) {
            c = malloc(sizeof(char) * strlen(str));
            *v = 1;
        }
        else {
            *v = (*aux) + 1;
        }
        c = str;
        valor_viejo = m_insertar(map, c, v);
        if (valor_viejo != NULL) {
            free(c);
            free(aux);
        }
    }

    //Menu del programa
    char * string = (char*) malloc(sizeof(char)*20);
    int * puntCuenat;
    int cuenta;
    char salir[6] = {'S', 'A', 'L', 'I', 'R', '\0'};
    while (1) {
        printf("Ingrese una palabra para saber las aparaciones de la misma\n");
        printf("En caso de querer salir del programa, escriba SALIR\n");
        scanf("%s", string);
        if (strcmp(string, salir) == 0) {
            //Terminar programa
            m_destruir(&map, eliminarString, eliminarEntero);
            free(string);
            exit(0);
        }
        else {
            //Muestra por consola cantidad de apariciones
            puntCuenat = (int *) m_recuperar(map, string);
            cuenta = puntCuenat == NULL ? 0 : *puntCuenat;
            printf("La palabra %s tiene %d apariciones\n", string, cuenta);
        }
    }

    return 0;
}
