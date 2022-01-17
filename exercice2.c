#include "exercice2.h"


// fonction permettant la création de la structure tableau_variable
// sz : taille mémoire d'un élément du tableau
// p : nombre d'éléments du tableau à initialiser
// n : nombre maximum d'éléments du tableau
// // Retourne : un pointeur de structure de type tableau_variable
T_var creer_var(size_t sz, int p, int n){

	T_var tab = malloc(sizeof(struct tableau_variable));
	assert(tab!=NULL); 
	
	tab->data = malloc(n * sizeof(void*));
	assert(tab->data!=NULL); 
	for (int i = 0; i < p; i++){
		(tab->data)[i] = malloc(sz);
		assert(tab->data[i]!=NULL); 
	}

	tab->size = sz;
	tab->n_max = n;
	tab->n_items = p;

	return tab;
}



// fonction permettant de générer de manière aléatoire les éléments contenus dans le champ data de la structure tableau_variable
// sz : taille mémoire d'un élément du tableau
// p : nombre d'éléments du tableau à initialiser
// n : nombre maximum d'éléments du tableau
// void (*copie_alea)(void**,size_t) : fonction permettant de donner une valeur à un élément du champ data de manière aléatoire
// Retourne : un pointeur de structure de type tableau_variable ayant tout ses éléments initialisés par une valeur générée aléatoirement
T_var aleatoire_var(size_t sz, int p, int n, void (*copie_alea)(void**, size_t)){
	if (p > n){
		puts("You are trying to create an array with more items than space, NULL returned.");
		return NULL;
	}
	T_var tab = creer_var(sz, p, n);	
	
	for (int i = 0; i < p; i++){
		(*copie_alea)((tab->data)+i, tab->size); 
	}
	return tab;
}



// fonction permettant d'afficher les éléments contenu dans le champ data de la structure tableau_variable
// tab : tableau_variable dont les éléments contenus dans le champ data sont à afficher
// void(*printing)(void**) : fonction permettant d'afficher un élément contenu dans data
void afficher_var(T_var tab, void (*printing)(void**)){
	if (tab != NULL){
		printf("\nTableau affiché : [");
		for (int i = 0; i < tab->n_items; i++){
			//printf("%d\n", i);
			(*printing)(&(tab->data)[i]);
			if (i < (tab->n_items)-1){
				printf(", ");
			}
		}
		printf("]\n");
	}
}



// fonction permettant de détruire une structure tableau_variable
// tab : tableau_variable à détruire
// void(*detruire)(void*) : void pemettant de détruire un élément du champ data
void detruire_tout(T_var tab, void(*detruire)(void*)){
	
	for(int i = 0; i < tab->n_items; i++){
		(*detruire)((tab->data)[i]);
		free(tab->data[i]);
	}
	
	free(tab->data);
	free(tab);
}



// fonction permettant de réallouer de l'espace mémoire pour une structure tableau_variable
// tab : structure tableau_variable ayant besoin d'une réallocation de la mémoire
void tab_realloc(T_var tab){
	if (tab->n_max <= tab->n_items){
		tab->data = realloc(tab->data, (sizeof(void*)) * tab->n_max * 2);
		assert(tab->data!=NULL); 
		tab->n_max = tab->n_max * 2;
	}
	else if (tab->n_items <= (tab->n_max)/2) {
		tab->data = realloc(tab->data, (sizeof(void*)) * tab->n_items);
		
		tab->n_max = tab->n_items;
	}
}



// fonction pemettant d'ajouter un élément à la fin d'un tableau dans le champ data
// tab : tableau auquel on souhaite ajouter un élément à la fin
// val : élément à ajouter à la fin d'un tableau
void push(T_var* tab, void* val){
	
	(*tab)->n_items++;
	tab_realloc(*tab);

	(*tab)->data[(*tab)->n_items-1] = malloc((*tab)->size);
	memcpy((*tab)->data[(*tab)->n_items-1], val, (*tab)->size);
}



// fonction permettant de retirer un élément à la fin d'un tableau dans le champ data
// tab : tableau auquel on doit retirer le dernier élément
// Retourne : un pointeur de le dernier élément du tableau; qui vient d'être retiré de ce dernier
void* pop(T_var* tab){
	
	if ((*tab)->n_items <= 0){
		puts("You are trying to pop an empty array, NULL returned.");
		return NULL;
	}
	
	void* res = malloc((*tab)->size);
	
	assert(res!=NULL); 
	
	memcpy( res, (*tab)->data[(*tab)->n_items-1], (*tab)->size);
	free((*tab)->data[(*tab)->n_items-1]);
	(*tab)->n_items--;
	tab_realloc(*tab);
	return res;
}



// fonction pemettant d'ajouter un élément à un index donné d'un tableau dans le champ data
// tab : tableau auquel on souhaite ajouter un élément à un index donné
// val : élément à ajouter à l'index donné d'un tableau
// index : index auquel l'élément doit être ajouté au tableau
void push_index(T_var* tab, void* val, int index){
	assert(index < (*tab)->n_items+1);
	(*tab)->n_items++;
	tab_realloc(*tab);
	(*tab)->data[(*tab)->n_items-1] = malloc((*tab)->size);
	for (int i = (*tab)->n_items-1; i > index ; i--){
		memcpy((*tab)->data[i],(*tab)->data[i-1], (*tab)->size); 	
	}
	
	memcpy((*tab)->data[index], val, (*tab)->size);
}



// fonction permettant de retirer un élément à un indéx donné d'un tableau dans le champ data
// tab : tableau auquel on doit retirer l'élément situé à un index donné
// index : index auquel l'élément doit être retiré du tableau
// Retourne : un pointeur de l'élément du tableau qui vient d'être retiré de ce dernier
void* pop_index(T_var* tab, int index){
	assert(index < (*tab)->n_items);
	if ((*tab)->n_items <= 0){
		puts("You are trying to pop an empty array, NULL returned.");
		return NULL;
	}
	
	void* res = malloc((*tab)->size);
	
	assert(res!=NULL); 
	
	memcpy( res, (*tab)->data[index], (*tab)->size);
	for (int i = index; i < (*tab)->n_items-1; i++){
		memcpy((*tab)->data[i],(*tab)->data[i+1], (*tab)->size); 	
	}
	free((*tab)->data[(*tab)->n_items-1]);
	(*tab)->n_items--;
	tab_realloc(*tab);
	return res;
}



// fonction permettant de connaître l'élément maximum d'un tableau
// tab : tableau dont on veut connaître l'élément ayant la valeur maximum
// int(*max)(void**,void**) : fonction permettant de comparer l'élément maximum du tableau (au moment de l'itération i) avec l'élément se situant à l'index i
// void(*afficher)(void**) : fonction permettant d'afficher un élément contenu dans data
void maximum(T_var tab, int(*max)(void**,void**), void(*afficher)(void**)){
	if(tab!=NULL){
		int index_max=0;

		for(int i = 1; i < tab->n_items; i++){
			if ((*max)(&(tab->data)[i],&(tab->data)[index_max]) == 1){
				index_max = i;
			}
		}

		printf("\nLe maximum est : ");
		(*afficher)(&(tab->data)[index_max]);
		puts("");
	}
}



// fonction permettant de retourner un tableau générique contenant les éléments du tableau initial de l'index n (inclu) à l'index m (exclu)
// tab : tableau dont l'on doit récupérer les éléments
// n : index de début (inclu)
// m : index de fin (exclu)
// Retourne : le pointeur de tableau_variable contenant les éléments du tableau initial de l'index n (inclu) à l'index m (exclu)
T_var slice(T_var tab, int n, int m){
	assert(n<m);
	int taille = m - n; 
	T_var res = creer_var(tab->size, 0, taille);
	for (int i = 0; i < taille; i++){
		push(&res, tab->data[i+n]);
	}
	return res;
}



// fonction permettan d'appliquer un prédicat sur les éléments du tableau
// tab : tableau dont sont filtrés les éléments selon le prédicat
// bool(*predicat)(void*) : prédicat selon lequel les éléments du tableau sont filtrés
// Retourne : le pointeur de tableau_variable contenant uniquement les éléments validés par le prédicat
T_var filtrer(T_var tab, bool(*predicat)(void*)){
	T_var resultat = creer_var(tab->size, 0, tab->n_max);
	for(int i = 0; i < tab->n_items; i++){
		if ((*predicat)(tab->data[i])){
			push(&resultat, tab->data[i]);
		}
	}
	
	return resultat;
}

