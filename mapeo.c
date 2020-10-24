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
    crear_lista((*m)->tabla_hash);
}

tValor m_insertar(tMapeo m, tClave c, tValor v){

    Codigo=hash_code(&c);
    *(tabla_hash+(Codigo-1))->
    /*
    *tEntrada = (tEntrada) malloc(sizeof(tEntrada));

    if (* == NULL) {
        exit(MAP_ERROR_MEMORIA);
    }
    */
}
