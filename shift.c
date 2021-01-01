#include "shift.h"
#include "board.h"
#include "stdio.h"

void shift(torre_t board[7][7],int x, int y, int x1, int y1, int  tp) {
    char player = find_player(x, y, board);
    torre_t tmp;
    torre_t vuoto;
    int xmid;
    int ymid;
    if (tp== 1) { /*se tipo mossa == 1  devo effettuare un semplice scambio*/
        tmp = board[x1][y1]; /* salvo la torre nella posizione d'arrivo in tmp*/
        board[x1][y1] = board[x][y]; /*la destinazione prende i valori della torre di partenza*/
        board[x][y] = tmp; /* infine la posizione iniziale prende i valori della torre salvata in tmp*/
        if(x1==0 && player=='1' || x1==6  && player=='2'){ /* se arrivo agli estremi della scacchiera potenzio la pedina*/
            board[x1][y1].pa[find_t_height(x1,y1,board)].is_enhanced=1;
        }
    }
    if (tp == 2) {/* se tipo mossa == 2 devo valutare lo scambio in base all'altezza delle torri */
        if (find_t_height(x, y, board) == 0 || find_t_height(x, y, board) == 1) {/* caso per torre alta 1 o 2*/
            find_mid(&xmid, &ymid, x, y, x1, y1);/* troviamo il valore centrale tra le coord iniziali e finali*/
            vuoto.pa[0].symbol = '#'; /* creiamo una torre vuota che dovrà sostituire la torre presente nella posizione iniziale*/
            vuoto.pa[1].symbol = '#';
            vuoto.pa[2].symbol = '#';
            vuoto.pa[0].is_enhanced = 0;
            vuoto.pa[1].is_enhanced = 0;
            vuoto.pa[2].is_enhanced = 0;
            tmp = board[x][y]; /*salvo i valori della torre iniziale*/
            board[x][y] = vuoto; /*la torre iniziale "diventa" la torre vuota*/
            /*se torre alta 1 o 2,la nuova torre non sfora altezza 3,la pedina dell'avversio mangiata sarà sempre la prima pedina della nuova torre*/
            board[x1][y1].pa[0].symbol = board[xmid][ymid].pa[find_t_height(xmid, ymid, board)].symbol;/*prendo pedina + alta dell'avversario e la assegno*/
            board[x1][y1].pa[0].is_enhanced = board[xmid][ymid].pa[find_t_height(xmid, ymid, board)].is_enhanced;
            /*se torre alta 1 o 2 allora basta copiare le prime due pedine (anche eventuali pedine vuote) nelle posizioni 1 e 2 della torre finale*/
            board[x1][y1].pa[1].symbol = tmp.pa[0].symbol;
            board[x1][y1].pa[1].is_enhanced = tmp.pa[0].is_enhanced;
            board[x1][y1].pa[2].symbol = tmp.pa[1].symbol;
            board[x1][y1].pa[2].is_enhanced = tmp.pa[1].is_enhanced;
            /*reset dell'eventuale status della pedina mangiata -> pedina mangiata = possessore torre */
            board[xmid][ymid].pa[find_t_height(xmid, ymid, board)].is_enhanced = 0;
            /*il reset del simbolo viene invece fatto successivamente per non andare ad intaccare l'altezza della torre */
            /* Infatti se noi effettuiamo il reset del simbolo la dimensione della torre cambia e questo porterebbe a eventuali errori*/
            board[xmid][ymid].pa[find_t_height(xmid, ymid, board)].symbol = '#';

            if(x1==0 && player=='1' || x1==6  && player=='2'){ /* se arrivo agli estremi della scacchiera potenzio la pedina più alta*/
                board[x1][y1].pa[find_t_height(x1,y1,board)].is_enhanced=1;
            }
        } else { /* se la torre è alta 3 allora elimino la pedina mangiata*/
            find_mid(&xmid, &ymid, x, y, x1, y1);
            vuoto.pa[0].symbol = '#';
            vuoto.pa[1].symbol = '#';
            vuoto.pa[2].symbol = '#';
            vuoto.pa[0].is_enhanced = 0;
            vuoto.pa[1].is_enhanced = 0;
            vuoto.pa[2].is_enhanced = 0;
            tmp = board[x][y];
            board[x][y] = vuoto;/* la posizone di partenza diventerà una torre vuota -> perchè sto mangiando -> muovo tutta la torre*/
            /*reset della pedina più alta della torre mangiata*/
            board[xmid][ymid].pa[find_t_height(xmid, ymid, board)].is_enhanced = 0;
            board[xmid][ymid].pa[find_t_height(xmid, ymid, board)].symbol = '#';
            /*effettuo un semplice scambio perchè se torre alta 3 allora torre iniziale = torre finale*/
            board[x1][y1] = tmp;
            if(x1==0 && player=='1' || x1==6  && player=='2'){ /* se arrivo agli estremi della scacchiera potenzio la pedina più alta*/
                board[x1][y1].pa[2].is_enhanced=1;
            }
        }
    }
}

void shift_player (char* player){
    if(*player=='1') {
        *player = '2';
    }else if(*player=='2'){
        *player = '1';
    } else {
    }
}
