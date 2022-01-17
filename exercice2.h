#ifndef EXERCICE2_H
#define EXERCICE2_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>   // utile pour rand()
#include <string.h>     // utile pour memcpy()


// Structure tableau_variable
struct tableau_variable{
    
    void** data;
    size_t size;
    int n_max;
    int n_items;
};


// nommage du pointeur sur structure tableau_variable
typedef struct tableau_variable* T_var;



// prototypes des fonctions/méthodes de exercice2.c

T_var creer_var(size_t, int, int);

T_var aleatoire_var(size_t, int, int, void (void**, size_t));

void afficher_var(T_var, void(void**));

void detruire_tout(T_var, void(void*));

void push(T_var* tab, void* val);

void* pop(T_var* tab);

void push_index(T_var*, void*, int);

void* pop_index(T_var*, int);

void maximum(T_var, int(void**, void**), void(void**));

T_var slice(T_var tab, int n, int m);

T_var filtrer(T_var tab, bool(*predicat)(void*));

#endif
