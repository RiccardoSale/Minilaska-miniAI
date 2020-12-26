#include "find.h"
#include "stdlib.h"

char find_player(int x, int y, torre_t board[7][7]) {
    char player;
    int i;
    int flag = 0;
    /*scorro dall'alto verso il basso la torre e cerco il primo carattere diverso da '#' quest'ultimo sarà il player in possesso della torre*/
    for (i = 2; i >= 0; i--) {
        if (board[x][y].pa[i].symbol != '#') {
            player = board[x][y].pa[i].symbol;
            flag = 1;
            break;
        }
    }
    /*flag a 1 -> player trovato flag->0 player non trovato*/
    if (flag == 0) {
        player = '#';
    }
    return player;
}


int find_t_height(int x, int y, torre_t board[7][7]) { /*ricorda return error da pensare TODO*/
    int height = 0;
    int i ;
    /*scorro dall'alto verso il basso la torre e cerco il primo carattere diverso da '#' assegno quindi l altezza = all indice i*/
    for (i = 2; i >= 0; i--) {
        if (board[x][y].pa[i].symbol != '#') {
            height = i;
            break;
        }
    }
    return height;
}

int find_t_strenght(int x, int y, torre_t board[7][7]){
    char player = find_player(x,y,board); /*cerchiamo il player che possiede la torre*/
    int player1=0;
    int player2=0;
    int i;
    for(i=2;i>=0;i--){ /*scorro dall'alto al basso e trovo come è composta la torre*/
        if (board[x][y].pa[i].symbol == '1')
            player1++;
        else if(board[x][y].pa[i].symbol == '2')
            player2++;
    }
    if(player == '1'){ /*se possessore=='1' se 1>2 forte se 1<2 debole*/
        if(player1>player2)
            return 1;
        else
            return 0;
    }
    if(player == '2'){ /*se possesore=='2' se 2>1 forte se 2<1 debole*/
        if(player2 >player1)
            return 1;
        else
            return 0;
    }
    return -1;
}

void find_t_enemy_composition(int x, int y,int *amiche,int *nemiche ,torre_t board[7][7]){
    char player = find_player(x,y,board );
    int player1=0;
    int player2=0;
    int i;
    for(i=2;i>=0;i--){
        if (board[x][y].pa[i].symbol == '1')
            player1++;
        else if(board[x][y].pa[i].symbol == '2')
            player2++;
    }
    if(player == '1'){ /*nemiche=player trovato come possessore*/
        *nemiche=player1;
        *amiche=player2;
    }
    if(player == '2'){ /*nemiche=player trovato come possessore*/
        *nemiche=player2;
        *amiche=player1;
    }
}

void find_mid(int *xmid, int *ymid, int x, int y, int x1, int y1) {
    if (x < x1 ) { /*se x<x1 -> scende perchè alto -> indice 0 basso -> indice 6*/
        if (y < y1) { /* se y<y1 ->verso destra   perchè sinistra -> indice 0  destra-> indice 6   */
            *xmid = x + 1;
            *ymid = y + 1;
        } else { /*altrimenti verso sinistra (y>y1) */
            *xmid = x + 1;
            *ymid = y - 1;
        }
    }
    if (x > x1 ) { /*se x>x1 -> sale perchè alto -> indice 0 basso -> indice 6*/
        if (y < y1) {  /* se y<y1 ->verso destra   perchè sinistra -> indice 0  destra-> indice 6   */
            *xmid = x - 1;
            *ymid = y + 1;
        } else {  /*altrimenti verso sinistra (y>y1) */
            *xmid = x - 1;
            *ymid = y - 1;
        }
    }
}

int find_enhanced(int x, int y, torre_t board[7][7]) {
    int is_enhanced=0;
    int i;
    for (i = 2; i >= 0; i--) { /*scorro pedina dall'alto al basso trovo possessore e controllo is_enhanced*/
        if (board[x][y].pa[i].symbol != '#') {
            is_enhanced = board[x][y].pa[i].is_enhanced;
            break;
        }
    }
    return is_enhanced;
}

int find_score(torre_t board[7][7],int x, int y, int x1, int y1) {
    int score;
    int altezza_pedina;
    int debole_forte;/*se debole 0 se forte 1*/
    int xmid;
    int ymid;
    int componentinemiche; /* pedine avversarie in xmid ymid*/
    int componentiamiche;  /*pedine amiche in xmid y mezzo (sotto controllo del nemico )*/
    if (((abs(x - x1) == 1) && (abs(y - y1) == 1))){ /*valutazione mosse da 1*/
        /*se muoviamo uno dei due triangolo centriali punteggio 0 */
        if (x == 6 && y == 2 || x == 6 && y == 4 || x == 5 && y == 3 || x == 0 && y == 2 || x == 0 && y == 4 ||x == 1 && y == 3) {
            return score = 0;
        }
        if ((abs(3 - x) - abs(3 - x1)) < 0) { /*se la mossa si allontana dal centro valore 1 - se si allontana valore 0*/
            return score = 1;
        } else {
            return score = 2;
        }
    }else{
        /* ricavo una serie di informazioni necessarie per stabilire il punteggio grazie alla strategia*/
        altezza_pedina=find_t_height(x,y,board);
        debole_forte=find_t_strenght(x,y,board);/*trovo se la mia pedina è debole o forte*/
        find_mid(&xmid,&ymid,x,y,x1,y1);
        find_t_enemy_composition(xmid,ymid,&componentiamiche,&componentinemiche,board); /*trovo la composizione della pedina da mangiare*/
        /*se muoviamo uno dei due triangolo centriali punteggio 0 */
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



