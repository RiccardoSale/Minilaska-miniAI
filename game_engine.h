//
// Created by rsh on 25/11/2020.
//

#ifndef MINILASKA_DIVISO_GAME_ENGINE_H
#define MINILASKA_DIVISO_GAME_ENGINE_H
#endif //MINILASKA_DIVISO_GAME_ENGINE_H

#include "campo.h"
#include "find.h"

void game_setup(char *p1, char *p2, torre_t campo[7][7]);
int read_coord(char *in, int *xy, const int *arr, const int *dim);
void print_move(int dim,int *arr,char player, char* p1, char*p2);
void game_engine(torre_t campo[7][7], char* p1, char* p2);