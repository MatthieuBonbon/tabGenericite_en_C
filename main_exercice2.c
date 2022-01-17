#include "exercice2.h"

// prototype des méthodes du main_exercice_2

static void afficher_structure(void**);

long long int aleatoire_lli();

void aleatoire_structure(void**, size_t);

void detruire_struct(void*);

int maximum_struct(void**, void**);

static void afficher_int(void**);

void aleatoire_int(void**, size_t);

void aleat_test(void**, size_t);

void detruire_int(void*);

int maximum_int(void**, void**);



// définition de la structure test

struct test {
    long long int a;
    long long int b;
    long long int c;
};



// fonction permettant d'afficher une structure test
// x : structure test que la fonction doit afficher
static void afficher_structure(void** x) {
    struct test* t = (struct test*) *x;	
	printf("[%lld, %lld, %lld]", t->a, t->b, t->c);
}



// fonction permettant de générer aléatoirement un long long int
// Retourne : un long long int généré de manière aléatoire
long long int aleatoire_lli(){
	long long int b = rand() % 50;
    int random = rand()%2;
	if (random == 1) {
		b = -b;
		return b;
	}
	return b;
}



// fonction permettant de générer aléatoirement les éléments d'une structure test
// dest : structure test qui doit recevoir les champs ayant des valeurs générées aléatoirement
// size : taille mémoire d'une structure test
void aleatoire_structure(void** dest, size_t size) {
	
	struct test *src = malloc(sizeof(struct test));
	assert(src != NULL);
	
	src->a = aleatoire_lli();  
	src->b = aleatoire_lli();
	src->c = aleatoire_lli();
	
	memcpy((struct test*) *dest, src, size);
	free(src);
}



// fonction permettant de détruire une structure test
// t : structure test à détruire
void detruire_struct(void* t) {}



// fonction permettant de comparer deux structures test
// val : structure test actuelle à comparer avec la structure test contenant la valeur maximale
// val_max : structure test contenant la valeur maximale à comparer avec la structure test actuelle
// Retourne : l'entier 1 si la valeur maximale se trouve dans un élément de val, l'entier 0 si la valeur maximale se trouve dans un élément de val_max
int maximum_struct(void** val, void** val_max){
    struct test* t_val = (struct test*) *val;
    struct test* t_val_max = (struct test*) *val_max;

    long long int x = 0;
    long long int y = 0;

    // récupération du de la valeur max de val
    if((t_val->a > t_val->b)&&(t_val->a > t_val->c)){
        x = t_val->a;
    }
    else if ((t_val->c > t_val->b)&&(t_val->c > t_val->a)){
        x = t_val->c;
    }
    else{
        x = t_val->b;
    }

    // récupération du de la valeur max de val_max
    if((t_val_max->a > t_val_max->b)&&(t_val_max->a > t_val_max->c)){
        y = t_val_max->a;
    }
    else if ((t_val_max->c > t_val_max->b)&&(t_val_max->c > t_val_max->a)){
        y = t_val_max->c;
    }
    else{
        y = t_val_max->b;
    }

    if(x > y){
        return 1;
    }
    else{
        return 0;
    }
    
}



// fonction permettant d'afficher un int
// v : int que la fonction doit afficher
static void afficher_int(void** v) {
    int *a = (int*) *v;
    printf("%d", *a);
}



// fonction permettant de générer aléatoirement un int
// dest : int qui doit recevoir la valeur générée aléatoirement
// size : taille mémoire d'un int 
void aleatoire_int(void** dest, size_t size) {
    int src = rand() % 101;
    memcpy((int*)*dest, &src, size);
}



//fonction permettant de détruire un int
// x : int à détruire
void detruire_int(void* t) {}



// fonction permettant de comparer deux int
// val : int actuel à comparer avec le int contenant la valeur maximale
// val_max : int contenant la valeur maximale à comparer avec le int actuel
// Retourne : l'entier 1 si la valeur maximale est pointée val, l'entier 0 si la valeur maximale est pointée par val_max
int maximum_int(void** val, void** val_max){
    int *a = (int*) *val;
    int *b = (int*) *val_max;
    if ((*a) > (*b)){
        return 1;
    }
    else{
        return 0;
    }
}



// fonction appliquant un prédicat de parité sur un élément
// x : élément sur lequel le prédicat est appliqué
// Retourne : un booléen indiquant si x est validé par le prédicat avec : true si x est validé, false sinon
bool predicat_pair(void* x){
	int* a = (int*) x;
	if ((*a) % 2 == 0){return true;}
	else {return false;}
}



int main() {

    srand(time(NULL)); // pour générer des nombres "aléatoires" selon le temps
    
    T_var tableau = aleatoire_var(sizeof(int), 11, 12, &aleatoire_int);
    T_var tableau_1 = aleatoire_var(sizeof(struct test), 10, 12, &aleatoire_structure);

    afficher_var(tableau, &afficher_int); // affichage de tableau
    afficher_var(tableau_1, &afficher_structure); // affichage de tableau_1
	
    int a = 8473843;
    push_index(&tableau, &a, 10); 

    afficher_var(tableau, &afficher_int); // affichage de tableau

    free(pop_index(&tableau,11)); // suppression du dernier élément de tableau);	
    

    afficher_var(tableau, &afficher_int); // affichage de tableau
    free(pop(&tableau)); // suppression du dernier élément de tableau

    afficher_var(tableau, &afficher_int); // affichage de tableau

    free(pop(&tableau_1)); // suppression du dernier élément de tableau_1
    free(pop(&tableau_1)); // suppression du dernier élément de tableau_1
    
    afficher_var(tableau_1, &afficher_structure);
    
    maximum(tableau, &maximum_int, &afficher_int);
    maximum(tableau_1, &maximum_struct, &afficher_structure);
    
    T_var predicated = filtrer(tableau, &predicat_pair);
    afficher_var(predicated, &afficher_int); // affichage de tableau
    
    T_var sliced = slice(tableau, 5, 8);
    afficher_var(sliced, &afficher_int);
    
    detruire_tout(sliced, &detruire_int);
    detruire_tout(tableau, &detruire_int); // destruction de tableau
    detruire_tout(predicated, &detruire_int);
    detruire_tout(tableau_1, &detruire_struct); // destruction de tableau_1

    

    return EXIT_SUCCESS;
}
