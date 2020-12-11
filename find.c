//
// Created by rsh on 25/11/2020.
//

#include "find.h"
#include "stdlib.h"

char find_player(int x, int y, torre_t campo[7][7]) {
    char giocatore;
    int i;
    int flag = 0;
    for (i = 2; i >= 0; i--) {
        if (campo[x][y].pa[i].symbol != '#') {
            giocatore = campo[x][y].pa[i].symbol;
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        giocatore = '#';
    }
    return giocatore;
}


int find_t_height(int x, int y, torre_t campo[7][7]) {
    int altezza;
    int i ;
    int flag = 0;
    for (i = 2; i >= 0; i--) {
        if (campo[x][y].pa[i].symbol != '#') {
            altezza = i;
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        altezza = 2;
    }
    return altezza;
}

int find_t_strenght(int x, int y, torre_t campo[7][7]){
    char giocatore = find_player(x,y,campo );
    int player1=0;
    int player2=0;
    int i;
    for(i=2;i>=0;i--){
        if (campo[x][y].pa[i].symbol == '1')
            player1++;
        else if(campo[x][y].pa[i].symbol == '2')
            player2++;
    }
    if(giocatore == '1'){
        if(player1>player2)
            return 1;
        else
            return 0;
    }
    if(giocatore == '2'){
        if(player2 >player1)
            return 1;
        else
            return 0;
    }
}

void find_t_composition(int x, int y,int *amiche,int *nemiche ,torre_t campo[7][7]){
    char giocatore = find_player(x,y,campo );
    int player1=0;
    int player2=0;
    int i;
    for(i=2;i>=0;i--){
        if (campo[x][y].pa[i].symbol == '1')
            player1++;
        else if(campo[x][y].pa[i].symbol == '2')
            player2++;
    }
    if(giocatore == '1'){
        *nemiche=player1;
        *amiche=player2;
    }
    if(giocatore == '2'){ //nemiche = player trovato!!!!!!
        *nemiche=player2;
        *amiche=player1;
    }
}

void find_mid(int *xmezzo, int *ymezzo, int x, int y, int x1, int y1) {
    if (x < x1 ) { //sta andando giu
        if (y < y1) { // sta andando a destra
            *xmezzo = x + 1;
            *ymezzo = y + 1;
        } else { //sta andando a sinitra
            *xmezzo = x + 1;
            *ymezzo = y - 1;
        }
    }
    if (x > x1 ) { //sta andando su
        if (y < y1) {  //sta andando a destra
            *xmezzo = x - 1;
            *ymezzo = y + 1;
        } else {   //sta andando a sinistra
            *xmezzo = x - 1;
            *ymezzo = y - 1;
        }
    }
}


int find_status(int x, int y, torre_t campo[7][7]) {
    int status;
    int i;
    for (i = 2; i >= 0; i--) {
        if (campo[x][y].pa[i].symbol != '#') {
            status = campo[x][y].pa[i].status;
            break;
        }
    }
    return status;
}

int find_score(torre_t campo[7][7],int x,int x1,int y,int y1) {
    int score;
    int altezza_pedina;
    int debole_forte; //se debole 0 se forte 1
    int xmezzo;
    int ymezzo;
    int componentinemiche; // pedine avversarie in xmezzo ymezzo
    int componentiamiche;  //pedine amiche in xmezzo y mezzo (sotto controllo del nemico )
    if (((abs(x - x1) == 1) && (abs(y - y1) == 1))){
        if (x == 6 && y == 2 || x == 6 && y == 4 || x == 5 && y == 3 || x == 0 && y == 2 || x == 0 && y == 4 ||x == 1 && y == 3) {
            return score = 0;
        }
        if ((abs(3 - x) - abs(3 - x1)) < 0) {
            return score = 1;
        } else {
            return score = 2;
        }
    }else{
        altezza_pedina=find_t_height(x,y,campo);
        debole_forte=find_t_strenght(x,y,campo);
        find_mid(&xmezzo,&ymezzo,x,y,x1,y1);
        find_t_composition(xmezzo,ymezzo,&componentiamiche,&componentinemiche,campo); //t composition per pedina da mangiare
        if (x == 6 && y == 2 || x == 6 && y == 4 || x == 5 && y == 3 || x == 0 && y == 2 || x == 0 && y == 4 ||x == 1 && y == 3) {
            return score = 0;
        }
        if(altezza_pedina==0){
            if(componentinemiche == 1){
                if(componentiamiche ==0) return 14;
                if (componentiamiche==1) return 19;
                if(componentiamiche == 2) return 24;
            }
            if(componentinemiche==2){
                if(componentiamiche==0) return 9;
                if(componentiamiche==1) return 4;
            }
        }
        if(altezza_pedina==1){
            if(debole_forte){
                if(componentinemiche == 1){
                    if(componentiamiche ==0) return 16;
                    if (componentiamiche==1) return 21;
                    if(componentiamiche == 2) return 26;
                }
                if(componentinemiche==2){
                    if(componentiamiche==0) return 11;
                    if(componentiamiche==1) return 6;
                }
            }else{
                if(componentinemiche == 1){
                    if(componentiamiche ==0) return 15;
                    if (componentiamiche==1) return 20;
                    if(componentiamiche == 2) return 25;
                }
                if(componentinemiche==2){
                    if(componentiamiche==0) return 10;
                    if(componentiamiche==1) return 5;
                }
            }
        }
        if(altezza_pedina==2){
            if(debole_forte){
                if(componentinemiche == 1){
                    if(componentiamiche ==0) return 18;
                    if (componentiamiche==1) return 23;
                    if(componentiamiche == 2) return 28;
                }
                if(componentinemiche==2){
                    if(componentiamiche==0) return 13;
                    if(componentiamiche==1) return 8;
                }
            }else{
                if(componentinemiche == 1){
                    if(componentiamiche ==0) return 17;
                    if (componentiamiche==1) return 22;
                    if(componentiamiche == 2) return 27;
                }
                if(componentinemiche==2){
                    if(componentiamiche==0) return 12;
                    if(componentiamiche==1) return 7;
                }
            }
        }
    }
}



