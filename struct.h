//
// Created by rsh on 26/11/2020.
//

#ifndef MINILASKA_DIVISO_STRUCT_H
#define MINILASKA_DIVISO_STRUCT_H
#endif //MINILASKA_DIVISO_STRUCT_H
#pragma once
typedef struct {
    char symbol;
    int status;
} pedina_t;

typedef struct {
    pedina_t pa[3];
} torre_t;

typedef struct {
    int x;
    int y;
} coord_t;