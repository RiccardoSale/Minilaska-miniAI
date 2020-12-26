#ifndef MINILASKA_DIVISO_GAME_ENGINE_H
#define MINILASKA_DIVISO_GAME_ENGINE_H
#endif /*MINILASKA_DIVISO_GAME_ENGINE_H*/

#include "board.h"
#include "find.h"
/**
 * \file game_engine.h
 * \brief Funzioni relative al ciclo di gioco.\n
 * \brief  Giocatore vs Giocatore / Giocatore vs CPU .
 */


/**
 * \details Determina la modalità di gioco per la partita corrente.
 *
 * \param[in,out]    p1             Nome del player_1
 * \param[in,out]    p2             Nome del player_2
 * \param[in]        board[7][7]    Campo di gioco
 */
void game_setup(char *p1, char *p2, torre_t board[7][7]);

/**
 * \details    Lettura da tastiera delle coordinate relative alla mossa che si vuole effettuare.
 * \note       in= stringa di caratteri su cui effettuo la lettura da tastiera.\n
 * \note       xy= array di interi in cui inserisco le coordinate convertite prese da in.\n
 * \note       arr= array con le mosse ditponibili.\n
 * \note       dim= dimensione dell'array arr. \n
 *
 * \param[in,out]    in    Coordinate lette da tastiera
 * \param[in,out]    xy    Coordinate convertite
 * \param[in,out]    arr   Array con le mosse disponibili
 * \param[in,out]    dim   Dimensione arr
 *
 * \return  Ritorna un codice relativo alla correttezza dei dati inseriti da tastiera.
 *
 * \retval   -1 Errore nell'inserimento dati
 * \retval   0  Dati inseriti correttamente
 *
 */
int read_coord(char *in, int *xy, const int *arr, const int *dim);


/**
 * \details Stampa "user friendly" dell' array arr contenente le mosse disponibili per un certo giocatore.
 *
 * \param[in]        dim       Dimensione array arr
 * \param[in,out]    arr       Array con mosse disponibili
 * \param[in]        player    Giocatore che deve effettuare la mossa
 * \param[in,out]    p1        Nickname giocatore 1
 * \param[in,out]    p2        Nickname giocatore 2
 *
 */
void print_move(int dim,int *arr,char player, char* p1, char*p2);


/**
 * \details Si occupa del ciclo di gioco di una partita player contro CPU.
 *
 * \param[in]        board      Campo di gioco
 * \param[in,out]    p1         Nickname giocatore 1
 *
 */
void game_engine_cpu(torre_t board[7][7], char* p1);


/**
 * \details Si occupa del ciclo di gioco di una partita player contro player.
 *
 * \param[in]       board      Campo di gioco
 * \param[in,out]   p1         Nickname giocatore 1
 * \param[in,out]   p2         Nickname giocatore 2
 *
 */
void game_engine_pvp(torre_t board[7][7], char* p1, char* p2);
