#ifndef _DVECTOR_H_
#define _DVECTOR_H_
#include "stdio.h"

typedef int vdata_t;

typedef struct vector vector_t;

/**
 * \file vector.h
 * \brief Libreria che implementa un vettore nel linguaggio C.
*/

/**
 * \brief Struct vector.
 * \details Struct vector.
 * \note Quando si tenta di aggiungere un elemento ma la size è uguale a capacity allora\n
 * al vettore viene riservata un area di memoria maggiore e capacity viene incrementata.
 *
*/
struct vector {
    /** Indica il numero di elementi nel vettore. */
    size_t size;
    /** Indica la capacità "massima" di elementi dell'array */
    size_t capacity;
    /** Puntatore agli elementi del vettore */
    vdata_t *data;
};

/**
 * \details Crea un nuovo vettore.
 * \note    Se la malloc da errore, andiamo in exit failure.
 */
vector_t *v_create();

/**
 * \details Libera la memoria che era stata riservata al vettore.
 */
void v_free(vector_t *v);

/**
 * \details     Verifica che l'indice index sia minore di v-> size.
 * \param[in]   v Il vettore.
 * \param[in]   index L'indice desiderato.
 */
void _v_check_index(const vector_t* v, size_t index);


/**
 * \details Ritorna l'elemento nella posizione index.\n
 * \details Termina se l'indice è più grande di size.
 * \param[in] v Il vettore.
 * \param[in]index L'indice desiderato.
 * \return Restituisce il valore nella posizione index.
 */
vdata_t v_get(const vector_t *v, size_t index);

/**
* \details Controlla se la size è uguale alla capacity, in quel caso effettua una realloc andando ad aumentare la memoria disponibile,\n
* inoltre aggiorna il valore di capacity
* \param[in] v Il vettore.
*/
void _v_check_extend(vector_t *v);

/**
 * \details   Inserisce value in coda al vettore.
 * \param[in] v Il vettore.
 * \param[in] value Il valore da inserire.
 */
void v_push_back(vector_t *v, vdata_t value);

#endif
