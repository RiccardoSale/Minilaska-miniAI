//
// Created by rsh on 27/11/2020.
//
#include "recursive.h"
#include "campo.h"
#include "swap.h"


void f_ricorsiva(torre_t campo[7][7],char giocatore,int valore,int depth ,int x ,int y,int x1,int y1,int *global,int * counter, int sp) {
    int size=0;
    int *arr;
    int i;
    int j;
    torre_t temporaneo[7][7];
    if(depth==0) {
        global[*counter] = valore;
        (*counter)++;
        return;
    }//qui aggiungo somma del ramo all array
    swap(x,y,x1,y1,campo,sp); //facciamo lo scambio
    //print_board(campo);
    sp=0;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            temporaneo[i][j]=campo[i][j];
        }
    }
    arr=moves(campo,giocatore,&size,&sp); //creiamo l array
    if(sp==-1){
        return;
    }
    if(giocatore=='1'){  // se profondità dispari sommo se pari sottraggo
        for(i=0;i<size;i+=4){
            valore-=find_score(campo,arr[i],arr[i+2],arr[i+1],arr[i+3]);
            swap_player(&giocatore);
            f_ricorsiva(campo,giocatore,valore,depth-1,arr[i],arr[i+1],arr[i+2],arr[i+3],global,counter,sp);
            campo=temporaneo;
        }
    }else{
        for(i=0;i<size;i+=4){
            valore+=find_score(campo,arr[i],arr[i+2],arr[i+1],arr[i+3]);
            swap_player(&giocatore);
            f_ricorsiva(campo,giocatore,valore,depth-1,arr[i],arr[i+1],arr[i+2],arr[i+3],global,counter,sp);
            campo=temporaneo;
        }
    }
}