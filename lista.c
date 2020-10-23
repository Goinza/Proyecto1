#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void crear_lista(tLista * l) {
    *l = (tLista)  malloc(sizeof(tLista));
    if (*l == NULL) {
        exit(LST_ERROR_MEMORIA);
    }
    (*l)->elemento = NULL;
    (*l)->siguiente = NULL;
}

void l_insertar(tLista l, tPosicion p, tElemento e) {
    tPosicion nuevaPos = (tPosicion) malloc(sizeof(tPosicion));
    if (nuevaPos == NULL) {
        exit(LST_ERROR_MEMORIA);
    }
    nuevaPos->elemento = e;
    nuevaPos->siguiente = p->siguiente;
    p->siguiente = nuevaPos;
}

tElemento l_recuperar(tLista l, tPosicion p) {
    if (p->siguiente == NULL) {
        exit(LST_POSICION_INVALIDA);
    }

    return p->siguiente->elemento;
}

tPosicion l_primera(tLista l) {
    return (tPosicion) l;
}

tPosicion l_siguiente(tLista l, tPosicion p) {
    if (p->siguiente == NULL) {
        exit(LST_NO_EXISTE_SIGUIENTE);
    }

    return p->siguiente;
}

tPosicion l_anterior(tLista l, tPosicion p) {
    if (l == p) {
        exit(LST_NO_EXISTE_ANTERIOR);
    }
    tPosicion aux = l;
    int found = 0;
    while (!found || aux!=NULL) {
        aux = aux->siguiente;
        if (aux->siguiente == p) {
            found = 1;
        }
    }

    return aux;
}

tPosicion l_ultima(tLista l) {
    tPosicion aux = l;
    if (l->siguiente != NULL) {
        while (aux->siguiente->siguiente != NULL) {
            aux = aux->siguiente;
        }
    }


    return aux;
}

tPosicion l_fin(tLista l) {
    tPosicion aux = l;
    if (l->siguiente != NULL) {
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
    }

    return aux;
}

int l_longitud(tLista l) {
    tPosicion aux = l->siguiente;
    int longitud = 0;
    while (aux != NULL) {
        longitud++;
        aux = aux->siguiente;
    }

    return longitud;
}

void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)) {
    if (p->siguiente == NULL) {
        exit(LST_POSICION_INVALIDA);
    }
    tPosicion pEliminar = p->siguiente;
    p->siguiente = pEliminar->siguiente;
    free(pEliminar);
    fEliminar(pEliminar->elemento);
}

void l_destruir(tLista * l, void (*fEliminar)(tElemento)) {
    tPosicion pos = (tPosicion) l;
    tPosicion aux;
    while (pos != NULL) {
        aux = pos;
        pos = pos->siguiente;
        fEliminar(aux->elemento);
        free(aux);
    }
}

