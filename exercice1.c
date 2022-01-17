#include "exercice1.h"

// fonction permettant la création d'une structure tableau
// t : nombre d'éléments du tableau
// sv : taille mémoire d'un élément du tableau
// Retourne : un pointeur de structure de type tableau
T creer(int t,size_t sv){

	T tab = malloc(sizeof(struct tableau));

	tab->val = malloc(t * sizeof(void*));
	for (int i = 0; i < t; i++){
		(tab->val)[i] = malloc(sv);
	}

	tab->taille = t;
	tab->size_val = sv;

	return tab;
}



// fonction permettant d'afficher les éléments contenus dans le champ val de la structure tableau
// tab : tableau dont les éléments contenus dans le champ val sont à afficher
// void(*affiche)(void**) : fonction permettant d'afficher un élément contenu dans val
void afficher(T tab, void (*affiche)(void**)){
	if (tab != NULL){
		printf("\nTableau affiché : [ ");
		for (int i = 0; i < tab->taille; i++){

			(*affiche)(&(tab->val)[i]);

			if (i < (tab->taille)-1){
				printf(", ");
			}
		}
		printf(" ]\n");
	}
}



// fonction permettant de générer de manière aléatoire les éléments contenus dans le champ val de la structure tableau
// n : nombre d'éléments du tableau
// size : taille mémoire d'un élément du tableau
// void (*copie_aleatoire)(void**,size_t) : fonction permettant de donner une valeur à un élément du champ val de manière aléatoire
// Retourne : un pointeur de structure de type tableau ayant tout ses éléments initialisés par une valeur générée aléatoirement
T aleatoire(int n, size_t size, void (*copie_aleatoire)(void**,size_t)){
	T tab = creer(n, size);
	
	for (int i = 0; i < tab->taille; i++){
		
		(*copie_aleatoire)((tab->val)+i, tab->size_val);
	}

	return tab;
}



// fonction permettant de détruire une structure tableau
// tab : tableau à détruire
// void(*detruire)(void*) : void pemettant de détruire un élément du champ val
void detruire_tout(T tab, void(*detruire)(void*)){

	for (int i = 0; i < tab->taille; i++){
		(*detruire)((tab->val)[i]);
		free(tab->val[i]);
	}
	free(tab->val);
	free(tab);
}



// fonctions de tri 

// fonction permettant d'intervertir deux éléments
// x : premier élément à intervertir avec le second
// y : second élément à intervertir avec le premier
void swap(void** x, void** y){
	
	void * swapping = *x;
	*x = *y;
	
	*y = swapping;
	
}



// fonction permettant le partitionnement du tableau en mettant tout les éléments supérieur au pivot après ce dernier
// et tout les éléments inférieurs au pivot avant
// first : index du premier élément du tableau
// last : index du dernier élément du tableau
// pivot : index de l'élément servant de pivot pour le partitionnement
// int (*cmpr)(const void*,const void*) : fonction permettant de comparer deux éléments d'un tableau
// Retourne : un entier utilisé comme pivot par les récursions de quick_sort
int partition(T* tab, int first, int last, int pivot, int (*cmpr)(const void*, const void*)){
	swap(&((*tab)->val)[pivot], &((*tab)->val)[last]);
	int j = first;
	//puts("before loop");
	for (int i = first; i < last; i++){
		//printf("%d th loop\n", i);
		if ((*cmpr)(((*tab)->val)[i], ((*tab)->val)[last]) <= 0){
			//puts("before swap in loop");
			swap(&((*tab)->val)[i], &((*tab)->val)[j]);
			j++;
		}
	}
	//puts("after loop");
	swap(&((*tab)->val)[j], &((*tab)->val)[last]);
	return j;
}



// fonction de tri rapide implémentée en C
// first : index du premier élément du tableau
// last : index du dernier élément du tableau
// int (*cmpr)(const void*,const void*) : fonction permettant de comparer deux éléments d'un tableau
void quick_sort(T* tab, int first, int last, int (*cmpr)(const void*, const void*)){
	if (first < last){
		int pivot = (rand() % (last-first)) + first;
		
		pivot = partition(tab, first, last, pivot, (*cmpr));
		
		quick_sort(tab, first, pivot-1, (*cmpr));
		
		quick_sort(tab, pivot+1, last, (*cmpr));
		
	}
}



// fonction permettant de trier les éléments du tableau générique
// tab : tableau à trier
// int (*cmpr)(const void*,const void*) : fonction permettant de comparer deux éléments d'un tableau
void trier(T tab, int (*cmpr)(const void*,const void*)){
	quick_sort(&tab, 0, (tab->taille)-1, (*cmpr));
}
