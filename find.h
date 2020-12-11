//
// Created by rsh on 25/11/2020.
//

#ifndef MINILASKA_DIVISO_FIND_H
#define MINILASKA_DIVISO_FIND_H
#endif //MINILASKA_DIVISO_FIND_H

#include "struct.h"



char find_player(int x, int y, torre_t campo[7][7]);
int find_t_height(int x, int y, torre_t campo[7][7]);
int find_t_strenght(int x, int y, torre_t campo[7][7]);
void find_t_composition(int x, int y,int *amiche,int *nemiche ,torre_t campo[7][7]);
void find_mid(int *xmezzo, int *ymezzo, int x, int y, int x1, int y1);
int find_status(int x, int y, torre_t campo[7][7]);
int find_score(torre_t campo[7][7],int x,int x1,int y,int y1);
