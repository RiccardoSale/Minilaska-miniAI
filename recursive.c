#include "recursive.h"
#include "board.h"
#include "shift.h"
#include "stdio.h"
#include "vector.h"
#include "stdlib.h"

void f_ricorsiva(torre_t board[7][7],char player,int value,int depth ,int x ,int y,int x1,int y1,vector_t * vector,int * counter, int tp) {
    int *arr=NULL; /*Puntatore all'array delle mosse, da liberare (array dinamico)*/
    int arr_size=0; /*Dimensione dell'array arr*/
    int i;
    int j;
    torre_t tmp[7][7];
    if(depth==0) {
        v_push_back(vector,value);
        (*counter)++;
        return;
    }/*qui aggiungo somma del ramo all array*/
    shift(board,x,y,x1,y1,tp); /*facciamo lo scambio*/ 
    for(i=0;i<7;i++){/*Copia del board*/
        for(j=0;j<7;j++){
            tmp[i][j]=board[i][j];
        }
    }
    if(arr!=NULL) free(arr); /*Se l'array arr non è vuoto lo libero*/
    arr=moves(board,player,&arr_size,&tp); /*creiamo l'array per il player attuale*/
    if(tp==-1){ /*Non sono state individuate mosse possibili, esco dalla ricorsione(possibile vittoria)*/
        return;
    }
    if(player=='1'){  
        for(i=0;i<arr_size;i+=4){/*Cicliamo tutte le mosse presenti in arr*/
            value-=find_score(board,arr[i],arr[i+1],arr[i+2],arr[i+3]); /*Calcoliamo il value per la mossa di arr selezionata dall'indice i, (peso negativo poiché player 1)*/
            shift_player(&player);/*Cambio il player del turno*/
            f_ricorsiva(board,player,value,depth-1,arr[i],arr[i+1],arr[i+2],arr[i+3],vector,counter,tp);/*Chiamata ricorsiva per la mossa di arr selezionata dall'indice i, diminuisco la profondità*/
            board=tmp;/*Undo della mossa, board ritorna allo stato precedente, per ogni chiamata ricorsiva nel for, il board deve essere uguale(non modificato da mosse)*/
        }
    }else{
        for(i=0;i<arr_size;i+=4){/*Cicliamo tutte le mosse presenti in arr*/
            value+=find_score(board,arr[i],arr[i+1],arr[i+2],arr[i+3]);/*Calcoliamo il value per la i-esima mossa, (peso positivo poiché CPU)*/
            shift_player(&player);/*Cambio il player del turno*/
            f_ricorsiva(board,player,value,depth-1,arr[i],arr[i+1],arr[i+2],arr[i+3],vector,counter,tp);/*Chiamata ricorsiva per la mossa di arr selezionata dall'indice i, diminuisco la profondità*/
            board=tmp;/*Undo della mossa, board ritorna allo stato precedente, per ogni chiamata ricorsiva nel for, il board deve essere uguale(non modificato da mosse)*/
        }
    }
}
