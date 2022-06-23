#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"

const size_t V_MIN_CAPACITY = 16;

 vector_t* v_create() {
     vector_t* v = (vector_t*) malloc (sizeof(vector_t)); /*Alloco quantità di memoria di dimensione vector_t*/
     v->size = 0; /*Dimensione iniziale 0*/
     v->capacity = V_MIN_CAPACITY; /* Capacità del vettore */
     v->data = (int*) malloc( v->capacity * sizeof(vdata_t) ); /*malloc in base alla capacità, quantità max di elementi*/
     if (!v->data) { /*Se errore in allocazione v->data, esco*/
         printf ("Error in memory allocation\n");
         exit(EXIT_FAILURE);
         }
     return v; /*Ritorno il vettore creato*/
 }

void _v_check_index(const vector_t* v, size_t index) {
    if( index >= v->size ){/*Controlla se l'indice è maggiore di size*/
        printf("Error: Index %lu out of bounds for vector of size %lu\n",
               index, v->size);
        exit(EXIT_FAILURE);
    }
}

 int v_get(const vector_t *v, size_t index){
     _v_check_index(v, index);/*Verifico che l'indice index sia < di v->size */
     return v->data[index]; 
 }

void _v_check_extend(vector_t *v) {
    if (v->size == v->capacity) { /*Verifico se size==capacity*/
        vdata_t *new_data = (vdata_t *) realloc(v->data, v->capacity * 2 * sizeof(vdata_t));/*eseguo riallocazione vettore, doppia capacity*/
        if (!new_data) { /*se realloc fallita, errore*/
            v_free(v);
            printf("Error: Failed memory allocation\n");
            exit(EXIT_FAILURE);
        }
        v->data = new_data; /*Assegno a data il nuovo puntatore*/
        v->capacity *= 2; /*Raddoppio capacity*/
    }
}

 void v_push_back(vector_t *v, vdata_t value){
     _v_check_extend(v);
     v->data[v->size++] = value;/*Inserimento in coda*/
 }    

 void v_free(vector_t *v){
     free(v->data);
     free(v);
 }
