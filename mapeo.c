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
    int esta=0;

    tValor valor_reemplazado = null;

    int Codigo=hash_code(&c);
    tLista * lista_actual= (*m->tabla_hash+(Codigo));
    tEntrada entrada_actual=(tEntrada) (*(l_primera(lista_actual))->elemento);

    int i=0;
    while ((i<l_longitud(lista_actual)) && (!esta)){
        if (*m->comparador(entrada_actual->clave, c)==0){ //Si las claves son iguales, entonces copio el valor a rremplazar dentrod e la entrada
            esta=1;
            valor_reemplazado=entrada_actual->valor
            entrada_actual->valor=v;
        }
        i++;
    }
    if (!esta){ //Si no se encontro la entrada, se crea una nueva y se incerta en la lista.
        tEntrada nueva_entrada= (tEntrada) malloc(sizeof(tEntrada))
        if (*nueva_entrada == null){
            exit(MAP_ERROR_MEMORIA);
        }
        nueva_entrada->clave=c;
        nueva_entrada->valor=v;
        l_insertar(lista_actual, l_ultima(lista_actual), nueva_entrada);
        //--------------------
        //ToDo: Falta revisar el factor de carga y redimensionar en caso de que se supere.
        //-------------------
    }
    return valor_reemplazado;
}
