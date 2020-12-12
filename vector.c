
#include <stdlib.h>
#include <stdio.h>
 #include <string.h>
 #include "vector.h"
#pragma once
/** * The Dynamic Vector data type
*/


 /**
20 * The minimum allocated memory upon creation.
21 */
 const size_t V_MIN_CAPACITY = 16;
 /**
25 * Extends allocated memory if entirely used by the stored elements.
26 * @param v The vector.
27 */
 void _v_check_extend(vector_t *v) {
     if (v->size == v->capacity) {
         vdata_t *new_data = (vdata_t *) realloc(v->data, v->capacity * 2 * sizeof(vdata_t));
         if (!new_data) {
             v_free(v);
             printf("Error: Failed memory allocation\n");
             exit(EXIT_FAILURE);
         }
         v->data = new_data;
         v->capacity *= 2;
     }
 }

 /**
63 * Fatal exit if the given index is beyond vector size.
64 * @param v The vector.
65 * @param index The index.
66 */
 void _v_check_index(const vector_t* v, size_t index) {
     if( index >= v->size ){
         printf("Error: Index %lu out of bounds for vector of size %lu\n",
                   index, v->size);
         exit(EXIT_FAILURE);
         }
     }
 /**
76 * Fatal exit if the given vector is empty.
77 * @param v The vector.
78 */

 vector_t* v_create() {
     printf("sono entrato in create figaaaaa");
     vector_t* v = (vector_t*) malloc (sizeof(vector_t));
     v->size = 0;
     v->capacity = V_MIN_CAPACITY; /* initial capacity */
     v->data = (int*) malloc( v->capacity * sizeof(vdata_t) );
     if (!v->data) {
         printf ("Error in memory allocation\n");
         exit(EXIT_FAILURE);
         }
     return v;
     }



 void v_free(vector_t *v){
     free(v->data);
     free(v);
     }

 void v_print(const vector_t *v) {
     size_t i;
     printf("[ ");
     for (i=0; i<v->size; i++)
         printf ("%d ", (int) v->data[i]);
     printf("]");
     }

 int v_is_empty(const vector_t *v){
     return v->size == 0;
     }

 size_t v_size(const vector_t *v){
     return v->size;
     }

 int v_get(const vector_t *v, size_t index){
     _v_check_index(v, index);
     return v->data[index];
     }

 void v_set(vector_t *v, size_t index, vdata_t value){
     _v_check_index(v, index);
     v->data[index] = value;
     }

 void v_push_back(vector_t *v, vdata_t value){
     _v_check_extend(v);
     v->data[v->size++] = value;
     }

 void v_push_front(vector_t *v, vdata_t value){
     size_t i;
     _v_check_extend(v);
     for (i=v->size; i>0; i--)
         v->data[i] = v->data[i-1];
     v->size++;
     v->data[0] = value;
     }



