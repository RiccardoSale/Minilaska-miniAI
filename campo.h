//
// Created by rsh on 25/11/2020.
//

#ifndef MINILASKA_DIVISO_CAMPO_H
#define MINILASKA_DIVISO_CAMPO_H

#endif //MINILASKA_DIVISO_CAMPO_H

#include "struct.h"
#include "find.h"

torre_t fill_board(torre_t campo[7][7]);
void print_board(torre_t campo[7][7]);
int *moves(torre_t campo[7][7], char giocatore, int *size ,int *speciale);