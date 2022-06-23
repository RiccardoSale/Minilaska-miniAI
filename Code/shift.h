#include "struct.h"

/**
 * \file shift.h
 * \brief Funzioni che operano uno scambio.
 */

/**
 * \details Modifica il campo in base alle mosse date in input.\n
 * \details Se mossa tipo 1 -> spostamento della pedina in una diagonale adiacente.\n
 * \details Se mossa tipo 2 -> Mangiata.
 *
 * \param[in,out]   board      Campo di gioco
 * \param[in]       x          coord x iniziale
 * \param[in]       y          coord y iniziale
 * \param[in]       x1         coord x1 finale
 * \param[in]       y1         coord y1 finaòe
 * \param[in]       tp  valore 1 o 2 in base al tipo di mossa
 */
void shift(torre_t campo[7][7],int x, int y, int x1, int y1,int tp);

/**
 * \details  Scambia il giocatore attuale con quello "inattivo".
 *
 * \param[in,out]  player   Giocatore attuale / char pointer
 *
 */
void shift_player (char * player);

