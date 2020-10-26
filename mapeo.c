#include <stdio.h>
#include <stdlib.h>
#include "mapeo.h"
#include "lista.h"

void eliminarEntrada(void * en) {
    free(en);
}

void crear_mapeo(tMapeo * m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void*)) {
    *m = (tMapeo) malloc(sizeof(tMapeo));

    if (*m == NULL) {
        exit(MAP_ERROR_MEMORIA);
    }

    (*m)->longitud_tabla = ci;
    (*m)->cantidad_elementos = 0;
    (*m)->hash_code = fHash;
    (*m)->comparador = fComparacion;

    (*m)->tabla_hash = malloc(sizeof(tLista) * ci);
    int i;
    for (i=0; i<ci; i++) {
        crear_lista((*m)->tabla_hash + i);
    }
}

void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)) {
    int indice = m->hash_code(c) % m->cantidad_elementos;
    tLista lista = *(m->tabla_hash + indice);

    tPosicion pos = l_primera(lista);
    int found = 0;
    tEntrada en;
    while (pos != l_fin(lista) && !found) {
        en = (tEntrada) l_recuperar(lista, pos);
        if (m->comparador(en->clave, c) == 0) {
            found = 1;
            fEliminarC(en->clave);
            fEliminarV(en->valor);
            l_eliminar(lista, pos, eliminarEntrada);
        }
        pos = l_siguiente(lista, pos);
    }

}

void m_destruir(tMapeo * m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)) {
    tMapeo map = *m;
    int count = map->longitud_tabla;
    int i;
    tLista lista;
    tPosicion pos;
    tEntrada en;
    for (i=0; i<count; i++) {
        lista = *(map->tabla_hash + i);
        pos = l_primera(lista);
        while (pos != l_fin(lista)) {
            en = (tEntrada) l_recuperar(lista, pos);
            fEliminarC(en->clave);
            fEliminarV(en->valor);
            pos = l_siguiente(lista, pos);
        }
        l_destruir(map->tabla_hash + i, eliminarEntrada);
    }
    free(m);
}

tValor m_recuperar(tMapeo m, tClave c) {
    int indice = m->hash_code(c) % m->cantidad_elementos;
    tLista lista = *(m->tabla_hash + indice);

    tPosicion pos = l_primera(lista);
    int found = 0;
    tEntrada en;
    tValor val = NULL;
    while (pos != l_fin(lista) && !found) {
        en = (tEntrada) l_recuperar(lista, pos);
        if (m->comparador(en->clave, c) == 0) {
            //clave de en == clave c, se encontro la entrada correcta
            val = en->valor;
            found = 1;
        }
        pos = l_siguiente(lista, pos);
    }

    return val;
}
