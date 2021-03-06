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

void no_eliminar_entrada(tElemento entrada){
    //Funcion DUMMIE para el l_destruir() de lista.
}

void redimensionar(tMapeo m){
    tLista * tabla_hash_vieja;
    tLista lista_actual_vieja, lista_actual_nueva;
    tEntrada entrada_actual;
    tPosicion pos_actual;
    int i, t;
    unsigned int long_vieja = m->longitud_tabla;
    //Creo la nueva tabla hash
    tLista * tabla_nueva = malloc(sizeof(tLista) * (m->longitud_tabla+10));
    for (i=0; i<(m->longitud_tabla+10); i++) {
        crear_lista(tabla_nueva + i);
    }

    m->longitud_tabla+=10;
    for (i=0; i<long_vieja; i++){  //recorro tabla_hash vieja
        lista_actual_vieja = *(m->tabla_hash+i);
        if (l_longitud(lista_actual_vieja)>0){ //recorro la lista de la tabla vieja si tiene elementos
            pos_actual = l_primera(lista_actual_vieja);
            for (t=0; t<l_longitud(lista_actual_vieja); t++){
                entrada_actual = (tEntrada) l_recuperar(lista_actual_vieja, pos_actual);
                lista_actual_nueva = *(tabla_nueva + m->hash_code(entrada_actual->clave) % m->longitud_tabla);
                l_insertar(lista_actual_nueva, l_primera(lista_actual_nueva), entrada_actual);
                pos_actual = l_siguiente(lista_actual_vieja, pos_actual);
            }
        }
    }
    tabla_hash_vieja = m->tabla_hash;
    m->tabla_hash = tabla_nueva;
    for (i=0; i<long_vieja; i++){
        l_destruir((tabla_hash_vieja+i), no_eliminar_entrada);
    }
}

tValor m_insertar(tMapeo m, tClave c, tValor v){
    int esta=0;
    int codigo=m->hash_code(c) % m->longitud_tabla;
    tValor valor_reemplazado = NULL;
    tLista lista_actual= *(m->tabla_hash+codigo);
    tPosicion pos_actual = l_primera(lista_actual);
    tEntrada entrada_actual;
    int i=0;
    while ((i<l_longitud(lista_actual)) && (!esta)){
        entrada_actual = l_recuperar(lista_actual, pos_actual);
        if (m->comparador(entrada_actual->clave, c)==0){ //Si las claves son iguales, entonces copio el valor a remplazar dentro de la entrada
            esta=1;
            valor_reemplazado=entrada_actual->valor;
            entrada_actual->valor=v;
        }
        pos_actual = l_siguiente(lista_actual, pos_actual);
        i++;
    }
    if (!esta){ //Si no se encontro la entrada, se crea una nueva y se incerta en la lista.
        tEntrada nueva_entrada= (tEntrada) malloc(sizeof(tEntrada));
        if (nueva_entrada == NULL){
            exit(MAP_ERROR_MEMORIA);
        }
        nueva_entrada->clave=c;
        nueva_entrada->valor=v;
        l_insertar(lista_actual, l_primera(lista_actual), nueva_entrada);
        m->cantidad_elementos++;
        if (((float)m->cantidad_elementos)/m->longitud_tabla>=0.75){ //Si se supera el factor de carga, se redimenciona la tabla hash
            redimensionar(m);
        }
    }
    return valor_reemplazado;
}

void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)) {
    int indice = m->hash_code(c) % m->longitud_tabla;
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
            m->cantidad_elementos--;
        }
        pos = l_siguiente(lista, pos);
    }

}

void m_destruir(tMapeo * m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)) {
    tMapeo map = *m;
    int count = map->longitud_tabla;
    int i;
    for (i=0; i<count; i++) {
        l_destruir(map->tabla_hash + i, eliminarEntrada);
    }
    free(m);
}

tValor m_recuperar(tMapeo m, tClave c) {
    int indice = m->hash_code(c) % m->longitud_tabla;
    tLista lista = *(m->tabla_hash + indice);
    tPosicion pos = l_primera(lista);
    int found = 0;
    tEntrada en;
    tValor val = NULL;
    while (pos != l_fin(lista) && !found) {
        en = (tEntrada) l_recuperar(lista, pos);
        if (m->comparador((en->clave), c) == 0) {
            //clave de en == clave c, se encontro la entrada correcta
            val = en->valor;
            found = 1;
        }
        pos = l_siguiente(lista, pos);
    }
    return val;
}
