#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regra.h"
#include "psinterface.h"

typedef struct arvore {
	char *info;
	struct arvore *prim;
	struct arvore *irmao;
} Arvore;

Arvore *criarArvore(char *axiom);
boolean ehFolha(Arvore *arv);
void crescerArvore(Arvore *arv, Regra *regras);
void imprimirFolhas(Arvore *arv);
void finalString(Arvore *arv, char *out);
void liberarArvore(Arvore **arv);


