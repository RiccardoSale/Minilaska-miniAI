//
// Created by rsh on 25/11/2020.
//

#include "campo.h"
#include "stdio.h"
#include "stdlib.h"

#define black "\033[48;2;0;0;0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

torre_t fill_board(torre_t campo[7][7]) {  //crezione delle vari torri con una sola pedina al loro interno nelle posizioni corrette e creazione degli spazi neri /bianchi
    int x, y, stato;
    for (x = 0; x < 7; x++) {
        if (x == 0) {
            stato = 0;
        } else {
            if (x % 2 == 0) {
                stato = 0;
            } else
                stato = 1;
        }
        for (y = 0; y < 7; y++) {
            if (stato == 0) {
                if ((x > 3 && y % 2 == 0) || (x < 3 && y % 2 ==0)) { // in base alla parte superiore o inferiore del campo inserisco le rispettive pedine(torri) tenendo anche conto della riga
                    if (x > 3 && y % 2 == 0) {
                        campo[x][y].pa[0].symbol = '1';
                        campo[x][y].pa[1].symbol = '#';
                        campo[x][y].pa[2].symbol = '#';
                        campo[x][y].pa[0].status = 0;
                        campo[x][y].pa[1].status = 0;
                        campo[x][y].pa[2].status = 0;

                    }
                    if (x < 3 && y % 2 == 0) {
                        campo[x][y].pa[0].symbol = '2';
                        campo[x][y].pa[1].symbol = '#';
                        campo[x][y].pa[2].symbol = '#';
                        campo[x][y].pa[0].status = 0;
                        campo[x][y].pa[1].status = 0;
                        campo[x][y].pa[2].status = 0;
                    }
                } else {
                    campo[x][y].pa[0].symbol = ' ';
                    campo[x][y].pa[1].symbol = ' ';
                    campo[x][y].pa[2].symbol = ' ';
                    campo[x][y].pa[0].status = 0;
                    campo[x][y].pa[1].status = 0;
                    campo[x][y].pa[2].status = 0;
                }

            } else {
                if ((x > 3 && y % 2 != 0) || (x < 3 && y % 2 != 0)) {
                    if (x > 3 && y % 2 != 0) {
                        campo[x][y].pa[0].symbol = '1';
                        campo[x][y].pa[1].symbol = '#';
                        campo[x][y].pa[2].symbol = '#';
                        campo[x][y].pa[0].status = 0;
                        campo[x][y].pa[1].status = 0;
                        campo[x][y].pa[2].status = 0;
                    }
                    if (x < 3 && y % 2 != 0) {
                        campo[x][y].pa[0].symbol = '2';
                        campo[x][y].pa[1].symbol = '#';
                        campo[x][y].pa[2].symbol = '#';
                        campo[x][y].pa[0].status = 0;
                        campo[x][y].pa[1].status = 0;
                        campo[x][y].pa[2].status = 0;
                    }
                } else {
                    if (x == 3) {
                        if (y % 2 != 0) {
                            campo[x][y].pa[0].symbol = '#';
                            campo[x][y].pa[1].symbol = '#';
                            campo[x][y].pa[2].symbol = '#';
                            campo[x][y].pa[0].status = 0;
                            campo[x][y].pa[1].status = 0;
                            campo[x][y].pa[2].status = 0;
                        } else {
                            campo[x][y].pa[0].symbol = ' ';
                            campo[x][y].pa[1].symbol = ' ';
                            campo[x][y].pa[2].symbol = ' ';
                            campo[x][y].pa[0].status = 0;
                            campo[x][y].pa[1].status = 0;
                            campo[x][y].pa[2].status = 0;
                        }
                    } else {
                        campo[x][y].pa[0].symbol = ' ';
                        campo[x][y].pa[1].symbol = ' ';
                        campo[x][y].pa[2].symbol = ' ';
                        campo[x][y].pa[0].status = 0;
                        campo[x][y].pa[1].status = 0;
                        campo[x][y].pa[2].status = 0;
                    }
                }
            }
        }
    }
    return campo[6][6];
}

void print_board(torre_t campo[7][7]) { //aumentare numero di linee
    int x, y, cuboc;
    int coord=7;
    for (x = 0; x < 7; x++) {  //riga
        printf(black"+-----------------------------------------+-+\n");
        for (cuboc = 4;cuboc >= 0; cuboc--) {//creo le 4 righe delle caselle presenti nella prima righa...seconda...terza
            printf("|");
            for (y = 0; y < 7; y++) { //colonna
                if (cuboc == 0 || cuboc == 4) {  //se la riga della casella e la prima o l'ultima stampo il contorno
                    if (campo[x][y].pa[0].symbol != ' ') {
                        printf("#####|");
                    }
                    else
                        printf("     |");
                }
                if (cuboc == 1 || cuboc == 2 || cuboc ==3) { // se la riga corrisponde al centro della casella stampo il simbolo contenuto all'interno di quella posizione (pedina non pedina)
                    if (campo[x][y].pa[cuboc - 1].symbol != ' ') {
                        if(campo[x][y].pa[cuboc-1].status==1){
                            if(campo[x][y].pa[cuboc-1].symbol=='2' ||campo[x][y].pa[cuboc-1].symbol=='1' ) {
                                if (campo[x][y].pa[cuboc - 1].symbol == '2') {
                                    printf(black ANSI_COLOR_RED "X%c%c%cX" ANSI_COLOR_RESET,
                                           campo[x][y].pa[cuboc - 1].symbol,
                                           campo[x][y].pa[cuboc - 1].symbol, campo[x][y].pa[cuboc - 1].symbol);
                                    printf(black"|");
                                }
                                if(campo[x][y].pa[cuboc - 1].symbol == '1') {
                                    printf(black ANSI_COLOR_BLUE "X%c%c%cX" ANSI_COLOR_RESET,
                                           campo[x][y].pa[cuboc - 1].symbol,
                                           campo[x][y].pa[cuboc - 1].symbol, campo[x][y].pa[cuboc - 1].symbol);
                                    printf(black"|");
                                }
                            }
                            }else {
                            if(campo[x][y].pa[cuboc-1].symbol=='2' ||campo[x][y].pa[cuboc-1].symbol=='1' ) {
                                if (campo[x][y].pa[cuboc - 1].symbol == '2') {
                                    printf(black ANSI_COLOR_RED "#%c%c%c#" ANSI_COLOR_RESET,
                                           campo[x][y].pa[cuboc - 1].symbol, campo[x][y].pa[cuboc - 1].symbol,
                                           campo[x][y].pa[cuboc - 1].symbol);
                                    printf(black"|");
                                }
                                if (campo[x][y].pa[cuboc - 1].symbol == '1') {
                                    printf(black ANSI_COLOR_BLUE "#%c%c%c#" ANSI_COLOR_RESET,
                                           campo[x][y].pa[cuboc - 1].symbol, campo[x][y].pa[cuboc - 1].symbol,
                                           campo[x][y].pa[cuboc - 1].symbol);
                                    printf(black"|");
                                }
                            }else{
                                printf(black"#%c%c%c#|" ,
                                       campo[x][y].pa[cuboc - 1].symbol, campo[x][y].pa[cuboc - 1].symbol,
                                       campo[x][y].pa[cuboc - 1].symbol);
                            }
                        }
                    } else
                        printf(black"%c%c%c%c%c|", campo[x][y].pa[cuboc - 1].symbol, campo[x][y].pa[cuboc - 1].symbol,campo[x][y].pa[cuboc - 1].symbol,campo[x][y].pa[cuboc - 1].symbol, campo[x][y].pa[cuboc - 1].symbol);
                }
            }
            if(cuboc==2) {
                printf(black"%d|\n", coord);
                coord--;
            }else {
                printf(black" |\n");
            }
        }
    }
    printf(black"+-----------------------------------------+-+\n");
    //printf("|--a--|--b--|--c--|--d--|--e--|--f--|--g--|\n");
    for(x=1;x<8;x++){
        printf(black"|--%c--",x+96);
    }
    printf("|\n");
    printf("+-----------------------------------------+\n");
}

int *moves(torre_t campo[7][7], char giocatore, int *size ,int * type_moves) {
    int i;
    int j;
    int dim = 0;
    int status = 0;
    int counter = 0;
    int *p_obbligo;
    //controllo prima le mosse obbligatorie salti da 2
    for (i = 0; i <7; i++) { //verifico una prima volta quante mosse obbligatorie ho per poter stabilire la dimensione giusta della malloc
        for (j = 0; j < 7; j++) {
            if (find_player(i, j, campo) == giocatore) {
                status = find_status(i, j, campo); // se speciale
                if (giocatore == '2' || status == 1) {
                    if ((j - 1 >= 0 && i + 1 < 7) && find_player(i + 1, j - 1, campo) != giocatore &&
                        find_player(i + 1, j - 1, campo) != '#') {
                        if ((j - 2 >= 0 && i + 2 < 7) && find_player(i + 2, j - 2, campo) == '#')
                            dim += 4;
                    }
                    if ((j + 1 < 7 && i + 1 < 7) && find_player(i + 1, j + 1, campo) != giocatore &&
                        find_player(i + 1, j + 1, campo) != '#') {
                        if ((j + 2 < 7 && i + 2 < 7) && find_player(i + 2, j + 2, campo) == '#')
                            dim += 4;
                    }
                }
                if (giocatore == '1' || status == 1) {
                    if ((i - 1 >= 0 && j - 1 >= 0) && find_player(i - 1, j - 1, campo) != giocatore &&
                        find_player(i - 1, j - 1, campo) != '#') {
                        if ((i - 2 >= 0 && j - 2 >= 0) && find_player(i - 2, j - 2, campo) == '#')
                            dim += 4;
                    }
                    if ((i - 1 >= 0 && j + 1 < 7) && find_player(i - 1, j + 1, campo) != giocatore &&
                        find_player(i - 1, j + 1, campo) != '#') {
                        if ((i - 2 >= 0 && j + 2 < 7) && find_player(i - 2, j + 2, campo) == '#')
                            dim += 4;
                    }
                }
            }
        }
    }
    //se la dimensione è a 0 controllo mosse da 1
    if (dim == 0) {
        //printf("SONO ENTRATO IN MOSSE DA 1");

        for (i = 0; i <
                    7; i++) { //verifico una prima volta quante mosse obbligatorie ho per poter stabilire la dimensione giusta della malloc
            for (j = 0; j < 7; j++) {
                if (find_player(i, j, campo) == giocatore) {
                    status = find_status(i, j, campo); // se speciale
                    if (giocatore == '2' || status == 1) {
                        if ((j - 1 >= 0 && i + 1 < 7) && find_player(i + 1, j - 1, campo) == '#') {
                            dim += 4;
                        }
                        if ((j + 1 < 7 && i + 1 < 7) && find_player(i + 1, j + 1, campo) == '#') {
                            dim += 4;
                        }
                    }
                    if (giocatore == '1' || status == 1) {
                        if ((i - 1 >= 0 && j - 1 >= 0) && find_player(i - 1, j - 1, campo) == '#') {
                            dim += 4;
                        }
                        if ((i - 1 >= 0 && j + 1 < 7) && find_player(i - 1, j + 1, campo) == '#') {
                            dim += 4;
                        }
                    }
                }
            }
        }

        if(dim==0){
            *type_moves=-1;
            return type_moves;
        }

        p_obbligo = malloc(dim * sizeof(int));//creo array dinamicamente
        *size = dim;
        *type_moves = 1;

        for (i = 0; i < 7; i++) {
            for (j = 0; j < 7; j++) {
                if (find_player(i, j, campo) == giocatore) { //sto cercando il giocatore possessore della torre in i/j
                    status = find_status(i, j,
                                         campo); //quando trovo una torre che corrisponde al giocatore attuale cerco lo status della pedina che controlla la torre
                    if (giocatore == '2' ||
                        status == 1) { //se il giocatore ? il due/uno potenziato controllo la mossa in base a questo
                        if ((j - 1 >= 0 && i + 1 < 7) && find_player(i + 1, j - 1, campo) ==
                                                         '#') { //sinistra giu   // sto cercando se la diagonale spostata di 1 ? effettivamente dell' altro giocatore
                            p_obbligo[counter] = i;
                            counter++;
                            p_obbligo[counter] = j;
                            counter++;
                            p_obbligo[counter] = i + 1;
                            counter++;
                            p_obbligo[counter] = j - 1;
                            counter++;
                        }
                        if ((j + 1 < 7 && i + 1 < 7) && find_player(i + 1, j + 1, campo) ==
                                                        '#') { //destra giu   // sto cercando se la diagonale spostata di 1 ? effettivamente dell' altro giocatore
                            p_obbligo[counter] = i;
                            counter++;
                            p_obbligo[counter] = j;
                            counter++;
                            p_obbligo[counter] = i + 1;
                            counter++;
                            p_obbligo[counter] = j + 1;
                            counter++;
                        }
                    }
                    if (giocatore == '1' ||
                        status == 1) { // se giocatore 1/2 potenziato controllo la mossa differentemente
                        if ((i - 1 >= 0 && j - 1 >= 0) && find_player(i - 1, j - 1, campo) ==
                                                          '#') { //sinistra su   // sto cercando se la diagonale spostata di 1 ? effettivamente dell' altro giocatore
                            p_obbligo[counter] = i;
                            counter++;
                            p_obbligo[counter] = j;
                            counter++;
                            p_obbligo[counter] = i - 1;
                            counter++;
                            p_obbligo[counter] = j - 1;
                            counter++;
                        }
                        if ((i - 1 >= 0 && j + 1 < 7) && find_player(i - 1, j + 1, campo) ==
                                                         '#') { //destra su   // sto cercando se la diagonale spostata di 1 ? effettivamente dell' altro giocatore
                            p_obbligo[counter] = i;
                            counter++;
                            p_obbligo[counter] = j;
                            counter++;
                            p_obbligo[counter] = i - 1;
                            counter++;
                            p_obbligo[counter] = j + 1;
                            counter++;
                        }
                    }
                }
            }
        }

        return p_obbligo;

    } else {

        p_obbligo = malloc(dim * sizeof(int));//creo array dinamicamente
        *size = dim;
        *type_moves = 2;

        for (i = 0; i < 7; i++) {
            for (j = 0; j < 7; j++) {
                if (find_player(i, j, campo) == giocatore) { //sto cercando il giocatore possessore della torre in i/j
                    status = find_status(i, j,
                                         campo); //quando trovo una torre che corrisponde al giocatore attuale cerco lo status della pedina che controlla la torre
                    if (giocatore == '2' ||
                        status == 1) { //se il giocatore ? il due/uno potenziato controllo la mossa in base a questo
                        if ((j - 1 >= 0 && i + 1 < 7) && find_player(i + 1, j - 1, campo) != giocatore &&
                            find_player(i + 1, j - 1, campo) !=
                            '#') { //sinistra giu   // sto cercando se la diagonale spostata di 1 ? effettivamente dell' altro giocatore
                            if ((j - 2 >= 0 && i + 2 < 7) && find_player(i + 2, j - 2, campo) == '#') {
                                p_obbligo[counter] = i;
                                counter++;
                                p_obbligo[counter] = j;
                                counter++;
                                p_obbligo[counter] = i + 2;
                                counter++;
                                p_obbligo[counter] = j - 2;
                                counter++;

                            }
                        }
                        if ((j + 1 < 7 && i + 1 < 7) && find_player(i + 1, j + 1, campo) != giocatore &&
                            find_player(i + 1, j + 1, campo) !=
                            '#') { //destra giu   // sto cercando se la diagonale spostata di 1 ? effettivamente dell' altro giocatore
                            if ((j + 2 < 7 && i + 2 < 7) && find_player(i + 2, j + 2, campo) == '#') {
                                p_obbligo[counter] = i;
                                counter++;
                                p_obbligo[counter] = j;
                                counter++;
                                p_obbligo[counter] = i + 2;
                                counter++;
                                p_obbligo[counter] = j + 2;
                                counter++;
                            }
                        }
                    }
                    if (giocatore == '1' ||
                        status == 1) { // se giocatore 1/2 potenziato controllo la mossa differentemente
                        if ((i - 1 >= 0 && j - 1 >= 0) && find_player(i - 1, j - 1, campo) != giocatore &&
                            find_player(i - 1, j - 1, campo) !=
                            '#') { //sinistra su   // sto cercando se la diagonale spostata di 1 ? effettivamente dell' altro giocatore
                            if ((i - 2 >= 0 && j - 2 >= 0) && find_player(i - 2, j - 2, campo) == '#') {
                                p_obbligo[counter] = i;
                                counter++;
                                p_obbligo[counter] = j;
                                counter++;
                                p_obbligo[counter] = i - 2;
                                counter++;
                                p_obbligo[counter] = j - 2;
                                counter++;
                            }
                        }
                        if ((i - 1 >= 0 && j + 1 < 7) && find_player(i - 1, j + 1, campo) != giocatore &&
                            find_player(i - 1, j + 1, campo) != '#') { //destra su   // sto cercando se la diagonale spostata di 1 ? effettivamente dell' altro giocatore
                            if ((i - 2 >= 0 && j + 2 < 7) && find_player(i - 2, j + 2, campo) == '#') {
                                p_obbligo[counter] = i;
                                counter++;
                                p_obbligo[counter] = j;
                                counter++;
                                p_obbligo[counter] = i - 2;
                                counter++;
                                p_obbligo[counter] = j + 2;
                                counter++;
                            }
                        }
                    }
                }
            }
        }
        return p_obbligo;
    }
}



