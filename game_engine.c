//
// Created by rsh on 25/11/2020.
//

#include "string.h"
#include "game_engine.h"
#include "stdlib.h"
#include "stdio.h"
#include "swap.h"
#include "recursive.h"


void game_setup(char *p1, char *p2, torre_t campo[7][7]) {
    printf("Benvenuto alla versione figa di MiniLaska!!!!\n\n");
    printf("Inserisci il nome del Player 1: ");
    scanf("%s", p1);
    printf("\n");
    printf("Inserisci il nome del Player 2: ");
    scanf("%s", p2);
    printf("\n");
    fill_board(campo);
    print_board(campo);
}

int read_coord(char *in, int *xy, const int *arr,const int * dim ){
    int err=-1;
    int i;
    printf("Inserisci le coordinate della pedina (x,y):");
    scanf("%s",in);
    for(i=0; i<3; i++){
        if(i==0) {
            if (!(in[i] >= 'a' && in[i] <= 'g')) {
                printf("\nInserisci dei valori validi!!!\n");
                return err;
            }
        }
        if(i==1) {
            if (in[i] != ','){
                printf("\nInserisci dei valori validi!!!\n");
                return err;
            }
        }
        if(i==2){
            if(!(in[i]>= 48 && in[i]<= 55)){
                printf("\nInserisci dei valori validi!!!\n");
            }
        }
    }

    printf("\n");

    printf("Inserisci le coordinate della destinazione (x,y):");
    scanf("%s",in+3);
    for(i=3; i<6; i++){
        if(i==3) {
            if (!(in[i] >= 'a' && in[i] <= 'g')) {
                printf("\nInserisci dei valori validi!!!\n");
                return err;
            }
        }
        if(i==4) {
            if (in[i] != ',') {
                printf("\nInserisci dei valori validi!!!\n");
                return err;
            }
        }
        if(i==5){
            if(!(in[i]>= 48 && in[i]<= 55)){
                printf("\nInserisci dei valori validi!!!\n");
            }
        }
    }
    //asssegno le coordinate all'array di interi contenente esse, convertendole nel formato della matrice c
    xy[1]=(int)in[0]-96;
    xy[0]=(int)in[2]-'0';
    xy[3]=(int)in[3]-96;
    xy[2]=(int)in[5]-'0';
    //printf("\n%d %d %d %d\n", xy[0],xy[1],xy[2],xy[3]);
    //conversione indici matrice
    xy[0]=abs(xy[0]-7);
    xy[1]=xy[1]-1;
    xy[2]=abs(xy[2]-7);
    xy[3]=xy[3]-1;
    //"sottraggo" 0 perche' effettuando converisone da stringa a int otterrei solo corrispondende ascii, sottraggo 96 per
    //conversione lettera a numero in tabella ascii
    //printf("\n%d %d %d %d\n", xy[0],xy[1],xy[2],xy[3]);

    for (i = 0; i < *dim; i += 4) {
        if ((arr[i] == xy[0] && arr[i + 1] == xy[1]) && (arr[i + 2] == xy[2] && arr[i + 3] == xy[3])) {
            return 0;
            //se troviamo questo vuol dire che quella posizione ha obbligo di mangiata
            // x1 y1 ce l'altro giocatore
        }
    }

    printf("\n\nINSERISCI DEI VALORI VALIDI!!!!\n\n");
    return err;
}


void print_move(int dim,int *arr, char player, char* p1, char*p2) {
    int i;
    for (i = 0; i < dim; i++) {
        if (i == 0) {
            if (player == '1')
                printf("Mosse Disponibili:                 Turno del giocatore %c - %s\n", player, p1);
            else
                printf("Mosse Disponibili:                 Turno del giocatore %c - %s\n", player, p2);
        }
        if (i % 4 == 0 && i != 0)
            printf("\n");
        if (i % 2 != 0)
            printf(",");
        if (i % 2 == 0 && i % 4 != 0)
            printf("->");
        if(i % 4==0 )//Inversione indici matrice asse x
            printf("%c", (arr[i+1]+1)+96);
        if(i % 4==1)
            printf("%d", (abs(arr[i-1]-7)));
        if(i % 2==0 && i!=0 && i%4!=0)//Inversione indici matrice asse y
            printf("%c", (arr[i+1]+1)+96);
        if(i % 2==1 && i!=0 && i%4!=1)
            printf("%d", abs(arr[i-1]-7));
    }
    printf("\n");
}

void game_engine(torre_t campo[7][7], char* p1, char* p2) {
    int dim = -1;
    int dim_tmp=-1;
    int i;
    int j;
    int k;
    int * arr;
    int * arr_tmp;
    int valore, valore_max;
    int sp= 0;
    int sp_tmp=0;
    char player = '1';
    char xy_in[6];
    int ia_moves[4]={0};
    int xy[4] = {0};
    int coord;
    int * global= malloc(1000*sizeof(int));
    int counterglobal=0;
    torre_t * temporaneo = malloc(49*sizeof(torre_t));
    do {
            arr=moves(campo,player,&dim,&sp);
            if(sp==-1){
                printf("Hai vinto giocatore: %c ",'2');
                break;
            }
            print_move(dim,arr,player,p1,p2);// azzera mossa non valida quando il player sbaglia a inserire le coordinate
            reinserisci:
            coord= read_coord(&xy_in[0], xy, arr, &dim);
            if(coord==-1) { // se leggi coord returna -1 rileggo coordinate
                printf("\n");
                print_move(dim,arr,player,p1,p2);
                printf("\n");
                goto reinserisci;
            }
            //printf("%d%d%d%d  mosse che vanno in swap\n\n\n\n",xy[0],xy[1],xy[2],xy[3]);
            //generare l array per ogni mossa dell array chiamare la f ricorsiva
            swap(xy[0], xy[1], xy[2], xy[3], campo, sp);
            arr_tmp=moves(campo,'2',&dim_tmp,&sp_tmp);
            for (i = 0; i < 4; i++) {
                printf("Mossa arr_tmp %d\n",arr_tmp[i]);
            }
            if (sp_tmp == -1) {
                printf("Hai vinto giocatore: %c ",'1');
                break;
            }
            if(dim_tmp==4){
                swap(arr_tmp[0],arr_tmp[1],arr_tmp[2],arr_tmp[3],campo,sp_tmp);
            }else {
                for (i = 0; i < 7; i++) {
                    for (j = 0; j < 7; j++) {
                        temporaneo[i * 7 + j] = campo[i][j];
                    }
                }
                for (i = 0; i < dim_tmp; i += 4) {
                    valore = find_score(temporaneo, arr_tmp[i], arr_tmp[i + 2], arr_tmp[i + 1], arr_tmp[i + 3]);
                    f_ricorsiva(temporaneo, '1', valore, 4, arr_tmp[i], arr_tmp[i + 1], arr_tmp[i + 2], arr_tmp[i + 3],
                                global, &counterglobal, sp_tmp);
                    if (i == 0) valore_max = global[0];
                    for (k = 0; k < counterglobal; ++k) {
                        if (valore_max < global[k]) {
                            valore_max = global[k];
                            ia_moves[0] = arr_tmp[i];    //x
                            ia_moves[1] = arr_tmp[i + 1];  //y
                            ia_moves[2] = arr_tmp[i + 2];  //x1
                            ia_moves[3] = arr_tmp[i + 3];  //y1
                        }
                    }
                    memset(global, 0, sizeof(int) * 1000);
                    counterglobal = 0;
                    //troviamo il max dell'array, se il max è > del massimo assoluto salviamo la coordinata
                    //reset array counter=0;
                }
                for (i = 0; i < 4; ++i) {
                    printf("Mossa arr_tmp  ghcghcghcghcghcggch%d\n", arr_tmp[i]);
                }
                printf("\n");
                //Stampa mosse CPU
                for (i = 0; i < 4; ++i) {
                    printf("Mossa %d\n", ia_moves[i]);
                }
                printf("QUESTA E' SP_TMP %d\n", sp_tmp);
                swap(ia_moves[0],ia_moves[1],ia_moves[2],ia_moves[3],campo,sp_tmp);
                memset(temporaneo,0,sizeof(torre_t)*49);
            }
            print_board(campo);
            free(arr_tmp);

            if(sp!=-1)
               free(arr);
            //sp=0;
        }while ((sp)!=-1);
        free(global);
        free(temporaneo);
}

/*
void game_engine(torre_t campo[7][7], char* p1, char* p2) {
    int dim1 = -1;
    int dim2 = -1;
    int *arr1;
    int *arr2;
    char player = '1';
    int mossanonvalida = 0;
    char xy_in[6];
    int xy[4] = {0};
    int coord;
    do {
        arr1 = must_moves(campo, player, &dim1);
        arr2 = single_moves(campo, player, &dim2);
        if(!(dim1 == 0 && dim2== 0)){
            //print_move(&dim1, &dim2, arr1, arr2,player,p1,p2);
            mossanonvalida = 0;
            reinserisci:
            coord= read_coord(&xy_in[0], xy);
            if(coord==-1) { // se leggi coord returna -1 rileggo coordinate
                printf("\n");
                //print_move(&dim1, &dim2, arr1, arr2,player,p1,p2);
                printf("\n");
                goto reinserisci;
            }
            swap(xy[0], xy[1], xy[2], xy[3], campo, &mossanonvalida);
            print_board(campo);
            if (mossanonvalida != -1) {
                if (player == '1') {
                    player = '2';
                } else {
                    player = '1';
                }
            } else {
                printf("Mossa non valida !!!!\n");
            }
        }

    } while (!(dim1 == 0 && dim2 == 0));
    printf("Hai vinto giocatore: %c ",player);
}
*/









