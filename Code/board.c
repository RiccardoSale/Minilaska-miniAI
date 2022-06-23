#include "board.h"
#include <stdio.h>
#include <stdlib.h>


#ifdef _WIN32
#include <windows.h>
#define black
#define ANSI_COLOR_RED
#define ANSI_COLOR_BLUE
#define ANSI_COLOR_YELLOW
#define ANSI_COLOR_RESET
#define WIN_COLOR_RED     SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
#define WIN_COLOR_BLUE    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
#define WIN_COLOR_YELLOW    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define WIN_COLOR_RESET  SetConsoleTextAttribute(hConsole, saved_attributes);
#define setup   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); \
                CONSOLE_SCREEN_BUFFER_INFO consoleInfo;           \
                WORD saved_attributes;GetConsoleScreenBufferInfo(hConsole, &consoleInfo); \
                saved_attributes = consoleInfo.wAttributes;
#endif

#if defined __APPLE__ || defined linux || defined unix
#define black "\033[48;2;0;0;0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define setup
#define WIN_COLOR_RED
#define WIN_COLOR_YELLOW
#define WIN_COLOR_BLUE
#define WIN_COLOR_RESET
#endif

#define pa_symbol board[x][y].pa[cuboc].symbol

void fill_board( torre_t board[7][7]) { /*Dispone le varie torri, con una sola pedina al loro interno andando a creare la scacchiera iniziale*/
    int x, y;
    for (x = 0; x < 7; x++) {
        for (y = 0; y < 7; y++) { /*inizializzazione pedina generica e is_enhanced sempre a 0(non vogliamo valori "sporchi")*/
            board[x][y].pa[0].is_enhanced = 0;
            board[x][y].pa[1].is_enhanced = 0;
            board[x][y].pa[2].is_enhanced = 0;
            board[x][y].pa[0].symbol = '#';
            board[x][y].pa[1].symbol = '#';
            board[x][y].pa[2].symbol = '#';
            if (x % 2 == 0) { /*se la riga è pari*/
                if (x > 3 &&
                    y % 2 == 0) { /* se sono nella parte bassa -> x>3 ,riga pari -> controllo se indice y pari*/
                    board[x][y].pa[0].symbol = '1'; /*in questo caso player 1*/
                } else if (x < 3 && y % 2 == 0) { /* altrimenti se x<3 (metà alta) e indice pari posiziono player 2*/
                    board[x][y].pa[0].symbol = '2';
                } else { /* se non è verificato nessuno dei due if allora pedina vuota*/
                    board[x][y].pa[0].symbol = ' ';
                    board[x][y].pa[1].symbol = ' ';
                    board[x][y].pa[2].symbol = ' ';
                }
            } else {
                if (x > 3 || x < 3) { /* stesso ragionamento ma controllo se indice colonna  dispari perchè mi trovo in riga dispari*/
                    if (x > 3 && y % 2 != 0) {
                        board[x][y].pa[0].symbol = '1';
                    } else if (x < 3 && y % 2 != 0) {
                        board[x][y].pa[0].symbol = '2';
                    } else {
                        board[x][y].pa[0].symbol = ' ';
                        board[x][y].pa[1].symbol = ' ';
                        board[x][y].pa[2].symbol = ' ';
                    }
                } else { /* se indice dispari posso avere x==3 in questo caso negli indici colonna pari inserisco la pedina vuota  (riga centrale scacchiera)*/
                    if (y % 2 == 0) {
                        board[x][y].pa[0].symbol = ' ';
                        board[x][y].pa[1].symbol = ' ';
                        board[x][y].pa[2].symbol = ' ';
                    }
                }
            }
        }
    }
}

void print_board(torre_t board[7][7]) {
    int x, y, cuboc;
    int coord = 7;
    setup; /*inizializza colori windows*/
    for (x = 0; x < 7; x++) {
        printf(black"+-----------------------------------------+-+\n"); /*stampa divisore colore nero*/
        for (cuboc = 2;cuboc >= 0; cuboc--) { /*ciclo per stampare le 3 righe che "formano le torri "*/
            printf("|");/*contorno iniziale */
            for (y = 0; y < 7; y++) {
                if (pa_symbol != ' ') {/* se simbolo pedina non è vuoto entro altrimenti stampo pedina vuota nera*/
                    if (board[x][y].pa[cuboc].is_enhanced == 1) { /* se is_enhanced =1 stampo pedina potenziata*/
                            if (pa_symbol == '2') { /* se symbol della pedina ='2' stampo pedina con colore rossa*/
                                WIN_COLOR_RED;
                                printf( ANSI_COLOR_RED "X%c%c%cX" ANSI_COLOR_RESET, pa_symbol, pa_symbol,pa_symbol);
                                WIN_COLOR_RESET;
                                printf(black"|");

                            }
                            if (pa_symbol == '1') { /* se symbol della pedina ='1' stampo pedina con colore blu*/
                                WIN_COLOR_BLUE;
                                printf( ANSI_COLOR_BLUE "X%c%c%cX" ANSI_COLOR_RESET,pa_symbol,pa_symbol, pa_symbol);
                                WIN_COLOR_RESET;
                                printf(black"|");
                            }
                    } else {/*se pedina non potenziata stampo le pedine con la stessa logica di prima ma senza contorno*/
                            if (pa_symbol == '2') {
                                WIN_COLOR_RED;
                                printf(ANSI_COLOR_RED "#%c%c%c#" ANSI_COLOR_RESET,pa_symbol, pa_symbol,pa_symbol);
                                WIN_COLOR_RESET;
                                printf(black"|");

                            }else if (pa_symbol == '1') {
                                WIN_COLOR_BLUE;
                                printf(ANSI_COLOR_BLUE "#%c%c%c#" ANSI_COLOR_RESET,pa_symbol, pa_symbol,pa_symbol);
                                WIN_COLOR_RESET;
                                printf(black"|");
                            }
                            else { /* se pedina ha is_enhanced = 0 e symbol != '1' && !='2' allora sarà una pedina vuota bianca*/
                            printf("#%c%c%c#|",pa_symbol, pa_symbol,pa_symbol);
                        }
                    }
                } else /* stampo pedina vuota nera*/
                    printf("     |");
            }
            if (cuboc == 1) { /* se riga centrale stampo coordinata */
                WIN_COLOR_YELLOW;
                printf(ANSI_COLOR_YELLOW "%d" ANSI_COLOR_RESET black, coord);
                WIN_COLOR_RESET;
                printf("|\n");
                coord--;
            } else {/* altrimenti creo solamente il bordo*/
                printf(" |\n");
            }
        }
    }
    printf("+-----------------------------------------+-+\n");
    for(x=1;x<8;x++){
        printf("|--");
        WIN_COLOR_YELLOW;
        printf(ANSI_COLOR_YELLOW"%c"ANSI_COLOR_RESET black,x+96);
        WIN_COLOR_RESET;
        printf("--");
    }
    printf("|\n");
    printf("+-----------------------------------------+\n");
}

int *moves(torre_t board[7][7], char player, int *size, int *type_moves) {
    int i;
    int j;
    int dim = 0;
    int is_enhanced;
    int *p_obbligo;
    /*controllo se sono presenti delle mangiate andando inoltre a contare la grandezza dell' eventuale array di mosse*/
    for (i = 0; i <7; i++) {
        for (j = 0; j < 7; j++) {
            if (find_player(i, j, board) == player) {/* controllo se la torre in cui mi trovo corrisponde al player per cui devo cercare le mosse*/
                is_enhanced = find_enhanced(i, j, board); /* controllo se la pedina del possessore della torre è potenziata*/
                if (player == '2' || is_enhanced == 1) {/* se player è == 2 o is_enhanced pedina == 1 */
                    if ((i + 1 < 7 && j - 1 >= 0) && find_player(i + 1, j - 1, board) != player &&
                        find_player(i + 1, j - 1, board) != '#') {/*diagonale basso sinistra (controllo pedina adiacente alle coordinate i-> riga,j->colonna)*/
                        if ((i + 2 < 7 && j - 2 >= 0) && find_player(i + 2, j - 2, board) == '#')/*diagonale sinistra 2*/
                            dim += 4;/*se trovo mossa aumento dimensione di 4 (partenza,arrivo )*/
                    }
                    if ((i + 1 < 7 && j + 1 < 7) && find_player(i + 1, j + 1, board) != player &&
                        find_player(i + 1, j + 1, board) != '#') { /* stesso ragionamento ma diagonale in basso a destra*/
                        if ((j + 2 < 7 && i + 2 < 7) && find_player(i + 2, j + 2, board) == '#')
                            dim += 4;
                    }
                }
                if (player == '1' || is_enhanced == 1) {/* se player è uguale a 1 allora le due digonali saranno verso l'alto ->i diminuisce*/
                    if ((i - 1 >= 0 && j - 1 >= 0) && find_player(i - 1, j - 1, board) != player &&
                        find_player(i - 1, j - 1, board) != '#') {
                        if ((i - 2 >= 0 && j - 2 >= 0) && find_player(i - 2, j - 2, board) == '#')
                            dim += 4;
                    }
                    if ((i - 1 >= 0 && j + 1 < 7) && find_player(i - 1, j + 1, board) != player &&
                        find_player(i - 1, j + 1, board) != '#') {
                        if ((i - 2 >= 0 && j + 2 < 7) && find_player(i - 2, j + 2, board) == '#')
                            dim += 4;
                    }
                }
            }
        }
    }
    /*se la dimensione è a 0 controllo mosse da 1*/
    if (dim == 0) {
        for (i = 0; i <7; i++) { 
            for (j = 0; j < 7; j++) {
                if (find_player(i, j, board) == player) {
                    is_enhanced = find_enhanced(i, j, board); 
                    if (player == '2' || is_enhanced == 1) {/*controllo spostamenti di 1 -> mossa disponibile se le diagonali adiacenti sono una torre vuota*/
                        if ((i + 1 < 7 && j - 1 >= 0)  && find_player(i + 1, j - 1, board) == '#') {
                            dim += 4;
                        }
                        if (( i + 1 < 7  && j + 1 < 7) && find_player(i + 1, j + 1, board) == '#') {
                            dim += 4;
                        }
                    }
                    if (player == '1' || is_enhanced == 1) {/*diagonale player 1 verso l'alto*/
                        if ((i - 1 >= 0 && j - 1 >= 0) && find_player(i - 1, j - 1, board) == '#') {
                            dim += 4;
                        }
                        if ((i - 1 >= 0 && j + 1 < 7) && find_player(i - 1, j + 1, board) == '#') {
                            dim += 4;
                        }
                    }
                }
            }
        }
        /*se la dimensione è ancora == 0 allora non ci sono mosse disponibili*/
        if (dim == 0) {
            *type_moves = -1; /* quindi effettuo la return di type_moves senza andare a creare un nuovo array*/
            return type_moves;
        }

        p_obbligo = malloc(dim * sizeof(int));/*creo array dinamicamente in base allla dimensione trovata*/
        *size = dim;
        dim=0;
        *type_moves = 1; /*tipo mosse 1*/

        for (i = 0; i < 7; i++) {/* stesso ragionamento ma andiamo ora a salvare le coordinate quando troviamo una mossa*/
            for (j = 0; j < 7; j++) {
                if (find_player(i, j, board) == player) { 
                    is_enhanced = find_enhanced(i, j,board); 
                    if (player == '2' ||is_enhanced == 1) { 
                        if ((j - 1 >= 0 && i + 1 < 7) && find_player(i + 1, j - 1, board) =='#') { 
                            p_obbligo[dim] = i;/* assegno coordinate e aumento dim*/
                            dim++;
                            p_obbligo[dim] = j;
                            dim++;
                            p_obbligo[dim] = i + 1;
                            dim++;
                            p_obbligo[dim] = j - 1;
                            dim++;
                        }
                        if ((j + 1 < 7 && i + 1 < 7) && find_player(i + 1, j + 1, board) =='#') {
                            p_obbligo[dim] = i;
                            dim++;
                            p_obbligo[dim] = j;
                            dim++;
                            p_obbligo[dim] = i + 1;
                            dim++;
                            p_obbligo[dim] = j + 1;
                            dim++;
                        }
                    }
                    if (player == '1' ||is_enhanced == 1) {
                        if ((i - 1 >= 0 && j - 1 >= 0) && find_player(i - 1, j - 1, board) =='#') {
                            p_obbligo[dim] = i;
                            dim++;
                            p_obbligo[dim] = j;
                            dim++;
                            p_obbligo[dim] = i - 1;
                            dim++;
                            p_obbligo[dim] = j - 1;
                            dim++;
                        }
                        if ((i - 1 >= 0 && j + 1 < 7) && find_player(i - 1, j + 1, board) =='#') {
                            p_obbligo[dim] = i;
                            dim++;
                            p_obbligo[dim] = j;
                            dim++;
                            p_obbligo[dim] = i - 1;
                            dim++;
                            p_obbligo[dim] = j + 1;
                            dim++;
                        }
                    }
                }
            }
        }
        return p_obbligo; /*restituisco puntatore all'array di mosse*/
    }else {/* se la dimensione del primo controllo non è uguale a 0 allora ho mosse di tipo 2*/
        p_obbligo = malloc(dim * sizeof(int));
        *size = dim;
        dim=0;
        *type_moves = 2;

        for (i = 0; i < 7; i++) {/* salvo le coordinate delle mosse di tipo 2*/
            for (j = 0; j < 7; j++) {
                if (find_player(i, j, board) == player) { 
                    is_enhanced = find_enhanced(i, j,
                                           board); 
                    if (player == '2' ||
                        is_enhanced == 1) { 
                        if ((j - 1 >= 0 && i + 1 < 7) && find_player(i + 1, j - 1, board) != player &&
                            find_player(i + 1, j - 1, board) !=
                            '#') { 
                            if ((j - 2 >= 0 && i + 2 < 7) && find_player(i + 2, j - 2, board) == '#') {
                                p_obbligo[dim] = i;
                                dim++;
                                p_obbligo[dim] = j;
                                dim++;
                                p_obbligo[dim] = i + 2;
                                dim++;
                                p_obbligo[dim] = j - 2;
                                dim++;

                            }
                        }
                        if ((j + 1 < 7 && i + 1 < 7) && find_player(i + 1, j + 1, board) != player &&
                            find_player(i + 1, j + 1, board) !=
                            '#') { 
                            if ((j + 2 < 7 && i + 2 < 7) && find_player(i + 2, j + 2, board) == '#') {
                                p_obbligo[dim] = i;
                                dim++;
                                p_obbligo[dim] = j;
                                dim++;
                                p_obbligo[dim] = i + 2;
                                dim++;
                                p_obbligo[dim] = j + 2;
                                dim++;
                            }
                        }
                    }
                    if (player == '1' ||
                        is_enhanced == 1) { 
                        if ((i - 1 >= 0 && j - 1 >= 0) && find_player(i - 1, j - 1, board) != player &&
                            find_player(i - 1, j - 1, board) !=
                            '#') { 
                            if ((i - 2 >= 0 && j - 2 >= 0) && find_player(i - 2, j - 2, board) == '#') {
                                p_obbligo[dim] = i;
                                dim++;
                                p_obbligo[dim] = j;
                                dim++;
                                p_obbligo[dim] = i - 2;
                                dim++;
                                p_obbligo[dim] = j - 2;
                                dim++;
                            }
                        }
                        if ((i - 1 >= 0 && j + 1 < 7) && find_player(i - 1, j + 1, board) != player &&
                            find_player(i - 1, j + 1, board) !=
                            '#') { 
                            if ((i - 2 >= 0 && j + 2 < 7) && find_player(i - 2, j + 2, board) == '#') {
                                p_obbligo[dim] = i;
                                dim++;
                                p_obbligo[dim] = j;
                                dim++;
                                p_obbligo[dim] = i - 2;
                                dim++;
                                p_obbligo[dim] = j + 2;
                                dim++;
                            }
                        }
                    }
                }
            }
        }
        return p_obbligo;
    }
}



