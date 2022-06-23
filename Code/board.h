#include "struct.h"
#include "find.h"
/**
 * \file board.h
 * \brief Funzioni che eseguono operazioni sul board di gioco\n
 */

/**
 * \details         Inizializza il board modificando quello dato in input.
 *
 * \param[in,out]   board  Campo di gioco
 *
 * \return          Restituisce il board inizializzato ai valori di base.(Scacchiera iniziale)
 *
 */
void fill_board(torre_t board[7][7]);

/**
 * \details     Esegue la stampa del board dato in input.
 * \param[in]   board    board di gioco
 */
void print_board(torre_t board[7][7]);

/**
 *  \details            Genera l'array di mosse disponibili dati in input; il board e il giocatore attuale.\n
 *  \details            Assegna al parametro *type_moves il tipo di mosse presenti nell'array.(spostamento singolo valore 1 - mangiata valore 2)\n
 *  \note               Se non è possibile effettuare nessuna mossa l'array non viene generato e a *typemoves viene assegnato -1.\n
 *  \note               Se *typemoves è stato assegnato a -1 ritorniamo quest'ultimo al posto del puntatore all'array.\n
 *  \note               La free del puntatore va effettuata quando a type_moves vengono assegnati i valori 1 o 2.
 *  \param[in]          board          Campo di gioco
 *  \param[in]          player        Giocatore per cui devo controllare le mosse disponibili
 *  \param[in,out]      size             Puntatore int a cui assegnamo la dimensione dell'array di mosse
 *  \param[in,out]      type_moves     Puntatore int a cui viene assegnato il tipo di mosse presenti nell'array
 *
 *  \return Puntatore all'array dinamico di tipo int che contiene le mosse trovate.\n
 *  \return Puntatore di typemoves in caso non sia disponibile alcuna mossa.
 */
int *moves(torre_t board[7][7], char player, int *size ,int *type_moves);

