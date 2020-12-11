//
// Created by rsh on 27/11/2020.
//

#include "swap.h"
#include "campo.h"

void swap(int x, int y, int x1, int y1, torre_t campo[7][7], int  tipomossa) {
    char giocatore = find_player(x, y, campo);
    torre_t tmp;
    torre_t vuoto;
    int xmezzo;
    int ymezzo;
   // printf(" adsa dasda da swapppp s %d\n",tipomossa);
    if (tipomossa== 1) {
        tmp = campo[x1][y1];
        campo[x1][y1] = campo[x][y];
        campo[x][y] = tmp;
        if(x1==0 && giocatore=='1' || x1==6  && giocatore=='2'){
            campo[x1][y1].pa[find_t_height(x1,y1,campo)].status=1;
        }
    }                               //pedina da uno che mangia pedina da 1 ( si forma la torre)   pedina o anche una torre che mangia una torre andro a togliere una pedina dell avversario che diventa mia (perche liberiamo solo se la torre è alta due e ce un nostro giocatore)
    if (tipomossa == 2) {
        if (find_t_height(x, y, campo) == 0 || find_t_height(x, y, campo) == 1) {
            find_mid(&xmezzo, &ymezzo, x, y, x1, y1);    // se passiamo sopra ad un altra di un altro player e questo succede sempre
            vuoto.pa[0].symbol = '#';
            vuoto.pa[1].symbol = '#';
            vuoto.pa[2].symbol = '#';
            vuoto.pa[0].status = 0;
            vuoto.pa[1].status = 0;
            vuoto.pa[2].status = 0;                            // libero la pedina solamente se la torre dell'avversario e alta due ed e ovviamente composta da una mia pedina sotto e una sua pedina sopra
            tmp = campo[x][y];                                 // se la torre e invece alta 3 ne prendo uno ma non libero la mia pedina che e sotto
            campo[x][y] = vuoto;
            campo[x1][y1].pa[0].symbol = campo[xmezzo][ymezzo].pa[find_t_height(xmezzo, ymezzo, campo)].symbol;
            campo[x1][y1].pa[0].status = campo[xmezzo][ymezzo].pa[find_t_height(xmezzo, ymezzo, campo)].status; // guardiamo tipo della pedina in mezzo e la mettiamo nella destinazione sotto
            campo[x1][y1].pa[1].symbol = tmp.pa[0].symbol;
            campo[x1][y1].pa[1].status = tmp.pa[0].status;
            campo[x1][y1].pa[2].symbol = tmp.pa[1].symbol;
            campo[x1][y1].pa[2].status = tmp.pa[1].status;
            campo[xmezzo][ymezzo].pa[find_t_height(xmezzo, ymezzo, campo)].status = 0;  //manteniamo lo status facendolo prima del reset del simbolo per evitare un cambio d'altezza
            campo[xmezzo][ymezzo].pa[find_t_height(xmezzo, ymezzo, campo)].symbol = '#';

            if(x1==0 && giocatore=='1' || x1==6  && giocatore=='2'){
                campo[x1][y1].pa[find_t_height(x1,y1,campo)].status=1;
            }

        } else {
            find_mid(&xmezzo, &ymezzo, x, y, x1, y1);
            vuoto.pa[0].symbol = '#';
            vuoto.pa[1].symbol = '#';
            vuoto.pa[2].symbol = '#';
            vuoto.pa[0].status = 0;
            vuoto.pa[1].status = 0;
            vuoto.pa[2].status = 0;
            tmp = campo[x][y];    //va spianato solo i
            campo[x][y] = vuoto;
            campo[xmezzo][ymezzo].pa[find_t_height(xmezzo, ymezzo, campo)].status = 0;
            campo[xmezzo][ymezzo].pa[find_t_height(xmezzo, ymezzo, campo)].symbol = '#';
            campo[x1][y1] = tmp;

            if(x1==0 && giocatore=='1' || x1==6  && giocatore=='2'){
                campo[x1][y1].pa[2].status=1;
            }
        }
        // questo perche se l avversario ha una torre da 2
    }
}

void swap_player (char * giocatore){
    if(*giocatore=='1'){
        *giocatore='2';
    }else{
        *giocatore='1';
    }
}
