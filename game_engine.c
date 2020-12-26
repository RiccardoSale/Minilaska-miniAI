#include "game_engine.h"
#include "stdlib.h"
#include "stdio.h"
#include "shift.h"
#include "recursive.h"
#include "vector.h"

#ifdef _WIN32
#define CLEAR_SCREEN system("cls");
#endif

#if defined unix || defined __APPLE__ || defined linux
#define CLEAR_SCREEN printf("\e[1;1H\e[2J");
#endif

void game_setup( char *p1, char *p2, torre_t board[7][7]) {
    char mode='0';
    do {
        CLEAR_SCREEN;
        if(mode!='0') printf("INSERISCI UN VALORE VALIDO!!!");
        printf("\n\nBenvenuto alla versione figa di MiniLaska!!!!\n\n");
        printf("Seleziona la modalita' di gioco:\n ");
        printf("1) Player Vs Player;\n ");
        printf("2) Player Vs CPU;\n ");
        printf("Inserisci il valore: ");
        scanf(" %s", &mode); /*Leggo la modalità di gioco*/
        printf("\n\n");
    } while (!(mode =='1' || mode =='2'));

    if (mode == '1'){
        /*Setup della partita Playern Vs Player*/
        printf("\n");
        /*Lettura nick player 1 da char*, per leggere input continuo*/
        printf("Inserisci il nome del Player 1: ");
        scanf("%s", p1);
        printf("\n");
        /*Lettura nick player 2 da char*, per leggere input continuo*/
        printf("Inserisci il nome del Player 2: ");
        scanf("%s", p2);
        printf("\n");
        fill_board(board); /*Chiamata a fill_board per inizializzare board da gioco*/
        print_board(board); /*Chiamata a print_board per stampare board da gioco*/
        game_engine_pvp(board,&p1[0],&p2[0]); /*Chiamata a game_engine_pvp passando il board appena inizializzato ed i nick dei player letti in input*/

    }

    if (mode == '2'){

        printf("2c\n");
        printf("\n");
        /*Lettura nick player 1 da char*, per leggere input continuo*/
        printf("Inserisci il nome del Player 1: ");
        scanf("%s", p1);
        printf("\n");
        fill_board(board); /*Chiamata a fill_board per inizializzare board da gioco*/
        print_board(board); /*Chiamata a print_board per stampare board da gioco*/
        game_engine_cpu(board,&p1[0]); /*Chiamata a game_engine_pvp passando il board appena inizializzato ed il nick del player letto in input*/

    }

}

int read_coord(char *in, int *xy, const int *arr,const int * dim ){
    int err=-1;
    int i;

    printf("Inserisci le coordinate della pedina (x,y):");
    /*Lettura delle coordinate in formato (lettera,numero)*/
    scanf("%s",in);
    for(i=0; i<3; i++){
        if(i==0) {
            /*Controllo se il primo carattere è una lettera valida a<lettera<g*/
            if (!(in[i] >= 'a' && in[i] <= 'g')) {
                printf("\nInserisci dei valori validi!!!\n");
                return err;
            }
        }
        if(i==1) {
            /*Controllo se il secondo carattere è una virgola*/
            if (in[i] != ','){
                printf("\nInserisci dei valori validi!!!\n");
                return err;
            }
        }
        if(i==2){
            /*Controllo se il terzo carattere è un numero compreso tra 1 e 7*/
            if(!(in[i]> 48 && in[i]<= 55)){ /*Uso il codice ascii relativo al carattere 1 e 7*/
                printf("\nInserisci dei valori validi!!!\n");
                return err;
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
                return err;
            }
        }
    }

    /*asssegno all'array di interi xy le coordinate lette in input come stringa, convertendole nel formato della matrice c*/
    /*Casto il carattere char in intero per ottenere il suo codice ascii e sottraggo 96 per ottenere il valore numerico della lettera*/
    xy[1]=(int)in[0]-96;    /*Esempio (int)in[0]-96 con in[0]=c; c in ascii è 99, sottraendolo a 96 ottengo che c==3 */
    xy[0]=(int)in[2]-48;    /*Esempio (int)in[2]-48 con in[2]=3; c in ascii è 51, sottraendolo a 48 ottengo che 3==3 */
    xy[3]=(int)in[3]-96;
    xy[2]=(int)in[5]-48;

    /*Inversione indici matrice, il nostro 0,0 è in alto a sinistra mentre la lettura delle coordinate avviene con 0,0 basso a sinistra*/
    xy[0]=abs(xy[0]-7); /*Esempio: xy[0]=7 -> abs(7-7)=0, l'indice della riga nella matrice originale sarà 0*/
    xy[1]=xy[1]-1;          /*Esempio: xy[1]=6 -> 6-1=5, l'indice della colonna nella matrice originale sarà 5*/
    xy[2]=abs(xy[2]-7);
    xy[3]=xy[3]-1;


    for (i = 0; i < *dim; i += 4) { /*Controllo tutte le quaterne di coordinate*/
        if ((arr[i] == xy[0] && arr[i + 1] == xy[1]) && (arr[i + 2] == xy[2] && arr[i + 3] == xy[3])) {
            /*se trovo che le coordinate lette corritpondono a quelle di una pedina ritorno 0*/
            return 0;

        }
    }
    /*Se arrivo a questo punto la coordinata inserita non è tra quelle effettuabili ritorno quindi la variabile err con valore -1 */
    printf("\n\nINSERISCI DEI VALORI VALIDI!!!!\n\n");
    return err;
}

void print_move(int dim,int *arr, char player, char* p1, char* p2) {
    int i;
    for (i = 0; i < dim; i++) {
        if (i == 0) {/*Se prima iterazione del ciclo stampo intestazione*/
            if (player == '1')
                printf("Mosse Ditponibili:                 Turno del giocatore %c - %s\n", player, p1);
            else
                printf("Mosse Ditponibili:                 Turno del giocatore %c - %s\n", player, p2);
        }
        if (i % 4 == 0 && i != 0) /*Se prima iterazione del ciclo stampo intestazione*/
            printf("\n");
        if (i % 2 != 0) /*Stampa carattere separatore tra x ed y di una coppia di coordinate*/
            printf(",");
        if (i % 2 == 0 && i % 4 != 0) /*Stampa carattere separatore tra le due coppie di coordinate */
            printf("->");
        if(i % 4==0 ) /*Stampa x prima coppia di coordinate*/
            printf("%c", (arr[i+1]+1)+96);
        if(i % 4==1) /*Stampa y prima coppia di coordinate*/
            printf("%d", (abs(arr[i-1]-7)));
        if(i % 2==0 && i!=0 && i%4!=0)/*Stampa x seconda coppia di coordinate*/
            printf("%c", (arr[i+1]+1)+96);
        if(i % 2==1 && i!=0 && i%4!=1) /*Stampa y seconda coppia di coordinate*/
            printf("%d", abs(arr[i-1]-7));
    }
    printf("\n");
}

void game_engine_cpu(torre_t board[7][7], char* p1) {
    int dim = 0; /*Dimensione array mosse*/
    int dim_tmp = 0; /*Dimensione array mosse */
    int i;
    int j;
    int * arr; /*Puntatore all'array delle mosse, da liberare (array dinamico)*/
    int * arr_rec; /*Puntatore all'array delle mosse, da liberare (array dinamico)*/
    int valore, valore_max;
    int tp= 0; /*Tipo di mossa*/
    int tp_rec=0; /*Tipo mossa della cpu*/
    char player = '1';
    char user_in[6];
    int cpu_mv[4]={0}; /*Coordinate della mossa effettuata dalla CPU*/
    int user_mv[4] = {0};
    int coord_control;
    vector_t * vector; /*Contiene il punteggio di ogni ramo determinato dalla ricorsione di una certa mossa*/
    int counterglobal=0; /*Numero di rami trovati con la ricorsione per una singola mossa(azzerato ad ogni ciclo) != da size di vector*/
    torre_t tmp_board[7][7]={0};
    do {
            arr=moves(board,player,&dim,&tp); /*assegno ad arr l'array delle mosse disponibili*/
            if(tp==-1){ /*Se tipo mossa -1 (errore) vince CPU*/
                printf("Hai perso %s !!!", p1); /*Tramite puntatore stampo l'intera stringa*/
                break;
            }
            print_move(dim,arr,player,p1,"");
            reinserisci: /*label per reinserimento coordinate*/
            coord_control= read_coord(&user_in[0], user_mv, arr, &dim); /*Lettura coordinate da tastiera*/
            if(coord_control==-1) { /* se leggi coord_control -1 rileggo coordinate, errore in input*/
                printf("\n");
                print_move(dim,arr,player,p1,"");
                printf("\n");
                goto reinserisci; /*Richiamo alla label per ripetere operazione*/
            }
            /*CLEAR_SCREEN;*/
            shift(board,user_mv[0], user_mv[1], user_mv[2], user_mv[3], tp); /*Eseguo mossa del tipo indicato da tp, con le cordinate presenti in user_mv*/
            arr_rec=moves(board,'2',&dim_tmp,&tp_rec); /*Array delle mosse su cui si basa la ricorsione*/
            if (tp_rec == -1) { /*Se cpu non ha mosse disponibili ha vinto il giocatore*/
                printf("Hai vinto %s !!! ",p1);
                break;
            }
            if(dim_tmp==4){ /*Se la cpu ha solo una mossa disponibile la effettuo immediatamente, non entro in ricorsione*/
                shift(board,arr_rec[0],arr_rec[1],arr_rec[2],arr_rec[3],tp_rec); /*Eseguo mossa del tipo indicato da tp_rec, con le cordinate presenti in arr_rec*/
            }else {
                vector=v_create(); /*Vettore contenente i punteggi dei rami*/
                for (i = 0; i < 7; i++) { /*Creo board temporaneo per ricorsione*/
                    for (j = 0; j < 7; j++) {
                        tmp_board[i][j] = board[i][j];
                    }
                }
                for (i = 0; i < dim_tmp; i += 4) { /*Eseguo la ricorsione per tutte le mosse che la cpu può eseguire presenti in arr_rec(origine dei rami)*/
                    valore = find_score( tmp_board, arr_rec[i], arr_rec[i + 1], arr_rec[i + 2], arr_rec[i + 3]); /*Valore prende il punteggio relativo alla mossa di arr_rec selezionata in base all'indice i*/
                    /*Chiamata ricorsiva relativa alla mossa di arr_rec selezionata in base all'indice i*/
                    f_ricorsiva( tmp_board, '1', valore, 5, arr_rec[i], arr_rec[i + 1], arr_rec[i + 2], arr_rec[i + 3], vector, &counterglobal, tp_rec);
                    /*La prima mossa di arr_rec non determina la vittoria (la prima mossa di arr_rec viene eseguita all'interno della ricorsione, 
                     *(se determina vittoria, non inserisco valore ed esco subito -> counterglobal=0)*/
                    if(counterglobal>0) { 
                        if (i == 0) valore_max = v_get(vector, 0); /*Se prima iterazione ramo di valore max = il primo elemento del vettore*/
                        for (j = 0; j < counterglobal; ++j) { /*Scorriamo tutti i rami trovati*/
                            if (valore_max < v_get(vector, j)) { /*Se il ramo j-esimo è maggiore rispetto al valore_max aggiorniamo il valore di valore_max con il ramo attuale*/
                                valore_max = v_get(vector, j);
                                /*Se il valore del ramo è più grande di valore_max, salviamo la mossa generatrice del ramo*/
                                cpu_mv[0] = arr_rec[i];
                                cpu_mv[1] = arr_rec[i + 1];
                                cpu_mv[2] = arr_rec[i + 2];
                                cpu_mv[3] = arr_rec[i + 3];
                            }
                        }
                    } else { /*Se counterglobal == 0, la mossa che ho "valutato" mi porta alla vittoria, la memorizzo immediatamente*/
                        cpu_mv[0] = arr_rec[i];
                        cpu_mv[1] = arr_rec[i + 1];
                        cpu_mv[2] = arr_rec[i + 2];
                        cpu_mv[3] = arr_rec[i + 3];
                        tp_rec=2; /*Tp_rec modificato manualmente perché ricorsione ha riconosciuto vittoria (tp_rec sarebbe -1)*/
                        shift(board,cpu_mv[0],cpu_mv[1],cpu_mv[2],cpu_mv[3],tp_rec);/*Effettuiamo subito mossa*/
                        tp_rec=-1; /*Reimpostiamo te_rec -1 perché non abbiamo generato arr_rec*/
                    }
                    counterglobal = 0; /*Azzero il numero di rami trovati per la singola mossa*/
                }
                if(tp_rec!=-1)
                    shift(board,cpu_mv[0],cpu_mv[1],cpu_mv[2],cpu_mv[3],tp_rec); /*Eseguo mossa del tipo indicato da tp_rec, con le cordinate presenti in cpu_mv*/
                v_free(vector); /*Libero il vettore per resettare i valori*/
            }
            print_board(board);
            if(tp_rec!=-1) /*Se ho generato l'array arr_rec, lo libero*/
                free(arr_rec);
            if(tp!=-1)  /*Se ho generato l'array arr, lo libero*/
               free(arr);
        }while (tp!=-1);
}

/*tp_rec si riferirà sempre alla mossa generatrice del ramo quindi non cambierà mai*/

void game_engine_pvp(torre_t board[7][7], char* p1, char* p2) {
    int dim = 0; /*Dimensione array mosse*/
    int * arr; /*Puntatore all'array delle mosse, da liberare (array dinamico)*/
    int tp= 0; /*Tipo di mossa*/
    char player = '1'; /*Indica il player attuale*/
    char user_in[6]; /*Array contenente coordinate lette da tastiera come stringa*/
    int user_mv[4] = {0}; /*Array contenente coordinate lette da tastiera convertite in interi*/
    int coord_control; /*Controllo validità coordinate lette in input*/
    do {
        arr=moves(board,player,&dim,&tp); /*assegno ad arr l'array delle mosse disponibili*/
        if(tp==-1){ /*Se tipo mossa -1 (errore) vince giocatore opposto*/
            shift_player(player);
            printf("Hai vinto giocatore: %c ",player);
            break; 
        }
        print_move(dim,arr,player,p1,p2);

        reinserisci: /*label per reinserimento coordinate*/
        coord_control= read_coord(&user_in[0], user_mv, arr, &dim); /*Lettura coordinate da tastiera*/
        if(coord_control==-1) { /* se leggi coord_control -1 rileggo coordinate, errore in input*/
            printf("\n");
            print_move(dim,arr,player,p1,p2);
            printf("\n");
            goto reinserisci; /*Richiamo alla label per ripetere operazione*/
        }

        CLEAR_SCREEN;

        shift(board,user_mv[0], user_mv[1], user_mv[2], user_mv[3], tp); /*Eseguo mossa del tipo indicato da tp, con le cordinate presenti in xy*/
        print_board(board);
        if(tp!=-1) /*Se tipo mossa -1, array delle mosse non generato, libero la memoria allocata*/
            free(arr);
        shift_player(&player);
    } while (tp!=-1);
}






