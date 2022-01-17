#ifndef EXERCICE1_H
#define EXERCICE1_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h> // utilisé pour la commande memcpy

// Structure tableau
struct tableau {
	void** val;
	int taille;
	size_t size_val;
};

//nommage du pointeur sur structure tableau
typedef struct tableau* T;

// prototypes des fonctions/méthodes de exercice1.c

T creer(int taille, size_t size_val);

void afficher(T tab, void (*affiche)(void**));

T aleatoire(int n, size_t size, void (*copie_aleatoire)(void**, size_t));

void detruire_tout(T tab, void(*detruire)(void*));

void trier(T tab, int (*cmpr)(const void*,const void*));


#endif
