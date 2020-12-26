#include "struct.h"
/**
 * \file find.h
 * \brief Funzioni inerenti alla ricerca di particolari informazioni.\n
 * \brief Funzioni inerenti alla ricerca di particolari informazioni, le informazioni sono legate a una singola torre.
 */

/**
 * \details Trova il giocatore che possiede la torre di pedine nella posizione del campo indicata dai parametri x e y.
 *
 * \param[in]    x          Coordinata x
 * \param[in]    y          Coordinata y
 * \param[in]    board      Campo di gioco
 *
 * \return       Giocatore trovato
 *
 * \retval       '1'    Giocatore 1
 * \retval       '2'    Giocatore 2
 * \retval       'cancelletto'    Casella vuota
 */
char find_player(int x, int y, torre_t board[7][7]);


/**
 * \details Trova l'altezza della torre.
 *
 * \param[in]    x          Coordinata x
 * \param[in]    y          Coordinata y
 * \param[in]    board      Campo di gioco
 *
 * \return       Altezza torre
 *
 * \retval       '0'    Altezza 1
 * \retval       '1'    Altezza 2
 * \retval       '2'    Altezza 3
 */
int find_t_height(int x, int y, torre_t board[7][7]);


/**
 * \details Trova se la torre è debole o forte.(concetto di gioco di laska -> http://www.lasca.org/)
 *
 * \param[in]    x          Coordinata x
 * \param[in]    y          Coordinata y
 * \param[in]    board      Campo di gioco
 *
 * \return        Valore integer che identifica se la torre è forte o debole.
 *
 * \retval        '0'    Torre debole
 * \retval        '1'    Torre forte
 * \reterr        '-1'   Eventuale errore (non possibile)
 */
int find_t_strenght(int x, int y, torre_t board[7][7]);


/**
 * \details Trova da quante pedine la torre del nemico è formata.(dividendo in pedine nemiche ed amiche)
 *          \note nemiche=pedine del possessore della torre.\n
 *          \note amiche=pedine non appartenenti al possessore della torre.\n
 *
 * \param[in]        x              Coordinata x
 * \param[in]        y              Coordinata y
 * \param[in,out]    amiche         Numero di pedine amiche trovate
 * \param[in,out]    nemiche        Numero di pedine nemiche trovate
 * \param[in]        board          Campo di gioco / torre_t
 *
 */
void find_t_enemy_composition(int x, int y,int *amiche,int *nemiche ,torre_t board[7][7]);


/**
 * \details Date le coordinate di due pedine che corrispondono agli estremi della diagonale genera le coordinate della pedina centrale.
 *
 * \param[in,out]    xmid              Coord x della pedina centrale trovata
 * \param[in,out]    ymid              Coord y della pedina centrale trovata
 * \param[in]        x                 Coord x della pedina 1 data in input
 * \param[in]        y                 Coord y della pedina 1 data in input
 * \param[in]        x1                Coord x della pedina 2 data in input
 * \param[in]        y1                Coord y della pedina 2 data in input
 *
 */
void find_mid(int *xmid, int *ymid, int x, int y, int x1, int y1);


/**
 * \details Trova se la pedina è un soldato o un ufficiale.http://www.lasca.org/
 *
 * \param[in]    x          Coordinata x
 * \param[in]    y          Coordinata y
 * \param[in]    board      Campo di gioco
 *
 * \return      Restituisce se la pedina è potenziata o meno un valore di tipo int.
 * \retval      0 Soldato
 * \retval      1 Ufficiale
 */
int find_enhanced(int x, int y, torre_t board[7][7]);


/**
 * \details Determina il punteggio di una mossa.
 * \note Il punteggio della mossa è calcolato in base alla strategia implementata.
 *
 * \param[in]  board   Campo di gioco
 * \param[in]  x       Coord x   inziale
 * \param[in]  y       Coord y   iniziale
 * \param[in]  x1      Coord x1  finale
 * \param[in]  y1      Coord y1  finale
 *
 * \return    Restituisce il punteggio calcolato.
 * \return    Sono possibili 29 differenti punteggi.
 */
int find_score(torre_t board[7][7],int x, int y, int x1, int y1);
