#include <stdio.h>
#include <stdlib.h>
#include "mapeo.h"
#include "lista.h"

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

tValor m_recuperar(tMapeo m, tClave c) {
    int indice = m->hash_code(c) % m->cantidad_elementos;
    tLista lista = *(m->tabla_hash + indice);

    tPosicion pos = l_primera(lista);
    int found = 0;
    tEntrada en;
    tValor val = NULL;
    while (pos != NULL && !found) {
        en = (tEntrada) l_recuperar(lista, pos);
        if (m->comparador(en->clave, c) == 0) {
            //clave de en == clave c, se encontro la entrada correcta
            val = en->valor;
            found = 1;
        }
    }

    return val;
}
