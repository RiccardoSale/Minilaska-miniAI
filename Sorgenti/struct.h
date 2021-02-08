#pragma once
/**
 * \file struct.h
 * \brief Struct inerenti alle componenti del gioco.
 */


/**
 * \brief Struct della pedina.
 * \details Struct pedina costituita da due campi,symbol e is_enhanced.
*/
typedef struct {
    /**Identifica il possessore della pedina o l'eventuale pedina vuota attraverso i caratteri '1' '2'   '#'->pedina vuota*/
    char symbol;
    /** Identifica se la pedina è un soldato o un ufficiale / valore 1->soldato / valore 2->ufficiale*/
    int is_enhanced;
} pedina_t;
/**
 *\brief Struct della torre.
 * \details Struct torre costituita da un singolo campo, un array di tipo pedina_t con dimensione 3.
*/
typedef struct {
    /** array di tipo pedina_t con dimensione massima 3.(altezza massima delle torri)*/
    pedina_t pa[3];
} torre_t;


