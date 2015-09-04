#include <math.h>
#include <stdlib.h>

#define PI 3.141593
#define LIBERAR(p) if(p != NULL) {free(p); p = NULL;}

typedef struct pilha {
	double x, y;
	double ori;
	double comp;
	//uint cor;
	struct pilha *prox;
} Pilha;

Pilha *empilharPilha(Pilha *p, double posx, double posy, double orienta, double comprimento);
Pilha *desempilharPilha(Pilha *p);
Pilha *destruirPilha(Pilha *p);


