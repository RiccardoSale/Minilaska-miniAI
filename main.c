#include "game_engine.h"
#include "stdio.h"

/**
* \file main.c
* \mainpage Descrizione generale del progetto
* \authors Riccardo Sale - Gabriele Nicoletti.\n
* \subsubsection Il Regolamento del gioco
*  Implementazione di un gioco chiamato MiniLaska  variante del gioco originale http://www.lasca.org/.\n
*  Rispetto al gioco originale miniLaska prevede le seguenti limitazioni:\n
* • si può mangiare/conquistare una sola volta per mossa.\n
* • le torri possono essere alte al massimo 3 pedine, superato questo limite,la pedina più in basso viene rimossa dalla scacchiera.\n
*/
int main() {
    char p1[20], p2[20];
    torre_t board[7][7];
    game_setup(&p1[0], &p2[0], board);
    return 0;
}
