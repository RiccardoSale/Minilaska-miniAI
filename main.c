#include "game_engine.h"
#include "stdio.h"
int main() {
    char p1[20], p2[20];
    torre_t campo[7][7];
    game_setup(&p1[0], &p2[0], campo);
    game_engine(campo,&p1[0],&p2[0]);
    return 0;
}
