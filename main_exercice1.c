#include "exercice1.h"


// protoypes des méthodes du main

static void afficher_structure(void** x);

long long int aleatoire_lli();

void aleatoire_structure(void**, size_t);	

static void afficher_int(void** vp);

void aleatoire_int(void**,size_t);

void detruire_int(void*);

int cmpr_int(const void*,const void*);

int cmpr_test(const void*,const void*);

// Fin de prototypes des méthodes





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
	long long int b = rand() % 10;
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
	
	src->a = aleatoire_lli();  
	src->b = aleatoire_lli();
	src->c = aleatoire_lli();
	
	memcpy((struct test*) *dest, src, size);
	free(src);
}	



// fonction permettant de détruire une structure test
// t : structure test à détruire
void detruire_struct(void* t) {
    
}



// fonction permettant d'afficher un int
// vp : int que la fonction doit afficher
static void afficher_int(void** vp) {
	int *a = (int*) *vp;
	printf("%d",*a);
}



// fonction permettant de générer aléatoirement un int
// dest : int qui doit recevoir la valeur générée aléatoirement
// size : taille mémoire d'un int 
void aleatoire_int(void** dest,size_t size) {
	int src = rand() % 100;
	memcpy((int*)*dest, &src, size);
}



//fonction permettant de détruire un int
// x : int à détruire
void detruire_int(void* x) {
}



// fonction permettant de comparer deux éléments de type int
// val_1 : premier élément à comparer avec le second
// val_2 : second élément à comparer avec le premier
// Retourne : un entier contenant la différence entre *a et *b
int cmpr_int(const void* val_1, const void* val_2){
	
	int* a = (int*) val_1;
	int* b = (int*) val_2;
	return (*a - *b);
}



// fonction de faire la somme des trois éléments d'une structure test
// Retourne : un long long int contenant la somme des champs a, b et c d'une structure test
long long int somme_test(struct test* t){
	return (t->a) + (t->b) + (t->c);
}



// fonction permettant de comparer deux éléments de type structure test
// val_1 : premier élément à comparer avec le second
// val_2 : second élément à comparer avec le premier
// Retourne : un entier égal à 1 si la somme des champs de val_1 est supérieure à la somme des champs de val_2, retourne -1 sinon
int cmpr_test(const void* val_1, const void* val_2){
	if ((somme_test((struct test*) val_1) - somme_test((struct test*) val_2)) > 0){
		return 1;
	} 
	return -1;
}



int main() {

    srand(time(NULL));
    
    T array = aleatoire(3, sizeof(struct test), &aleatoire_structure); // tableau de struct test
    T array_1 = aleatoire(4, sizeof(int), &aleatoire_int); // tableau de int

    afficher(array, &afficher_structure); // affichage de array
    afficher(array_1, &afficher_int); // affichage de array_1
	
	
    trier(array, &cmpr_test);
    afficher(array, &afficher_structure); // affichage de array
	
    trier(array_1, &cmpr_int);
    afficher(array_1, &afficher_int); // affichage de array	
    
    
    array_1->val = realloc(array_1->val, (sizeof(void*)) * array_1->taille);
    afficher(array_1, &afficher_int); // affichage de array	

    detruire_tout(array, &detruire_struct); // destruction de array
    detruire_tout(array_1, &detruire_int); // destruction de array_1

    return EXIT_SUCCESS;
}
