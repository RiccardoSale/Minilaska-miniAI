#include "struct.h"
#include "vector.h"

/**
 * \file recursive.h
 * \brief Funzione ricorsiva che si occupa della valutazione del punteggio dei singoli rami.
 */

/**
 * \details       Trova il punteggio di ogni ramo generato dalla mossa passata alla funzione, salvandolo in un vettore.
 *
 * \param[in]     board          Campo di gioco
 * \param[in]     player        Giocatore
 * \param[in]     value          Valore iniziale della prima mossa passata -> diventa il punteggio del ramo.
 * \param[in]     depth          Profondità della mini-max custom
 * \param[in]     x                   coord x iniziale (mossa)
 * \param[in]     y                   coord y iniziale (mossa)
 * \param[in]     x1                 coord x1 finale  (mossa)
 * \param[in]     y1                 coord y1 finale  (mossa)
 * \param[in,out] vector         Puntatore del vettore in cui andiamo ad inserire il punteggio di ogni ramo trovato
 * \param[in,out] counter       Numero di rami trovati
 * \param[in,out] tp                  Tipo mossa da effettuare
 */
void f_ricorsiva(torre_t board[7][7],char player,int value,int depth ,int x ,int y,int x1,int y1,vector_t * vector,int * counter, int tp);

