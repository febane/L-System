/**
 *  Sistemas de Lindenmayer
 *  arvore.c 
 *  Implementacao da TAD arvore
 *  Ver documentacao para mais informacoes
 *
 *  @author Fernando Barbosa Neto
 *  @author Jeferson De Oliveira Batista
 *
 */
 
#include "arvore.h"

/**
 *  Cria arvore
 *
 *  @param axiom axioma que gerara a arvore inicial
 *  @return arvore criada
 *
 */
Arvore *criarArvore(char *axiom) {
	Arvore *nova = (Arvore*) malloc(sizeof(Arvore));
	int t = strlen(axiom) + 1;
	nova->info = (char*) calloc(t, sizeof(char));
	strcpy(nova->info, axiom);
	nova->prim = NULL;
	nova->irmao = NULL;
	return nova;
}

/**
 *  Verifica se eh uma folha
 *
 *  @param arv arvore a ser checada
 *  @return TRUE se for folha ou FALSE caso contrario
 *
 */
boolean ehFolha(Arvore *arv) {
	return (arv->prim == NULL);
}

/**
 *  Desenvolve a arvore segundo as regras
 *
 *  @param arv arvore que crescera
 *  @param regras regras a serem seguidas
 *
 */
void crescerArvore(Arvore *arv, Regra *regras) {
	char aux, copia[2], *s;
	boolean flag;
	int tam;
	int i;
	Regra *atual;
	Arvore **r;
	Arvore *raiz;
	if(ehFolha(arv)) {
		r = &(arv->prim);
		s = arv->info;
		tam = strlen(s);
		for(i = 0; i < tam; i++) {
			aux = s[i];
			flag = FALSE;
			atual = regras;
			while(atual != NULL) {
				if(atual->c == aux) {
					*r = criarArvore(atual->result);
					flag = TRUE;
					break;
				}
				atual = atual->prox;
			}
			if(!flag) {
				copia[0] = aux;
				copia[1] = '\0';
				*r = criarArvore(copia);
			}
			r = &((*r)->irmao);
		}
		return;
	}
	raiz = arv->prim;
	while(raiz != NULL) {
		crescerArvore(raiz, regras);
		raiz = raiz->irmao;
	}
}

/**
 *  Imprime folhas da arvore
 *
 *  @param arv arvore que sera imprimida
 *
 */
void imprimirFolhas(Arvore *arv) {
	if(ehFolha(arv)) {
		printf("%s", arv->info);
		return;
	}
	Arvore *r = arv->prim;
	while(r != NULL) {
		imprimirFolhas(r);
		r = r->irmao;
	}
}

/**
 *  Captura string final de arvore
 *  A string out deve ser passada vazia para a função
 *
 *  @param arv arvore que contem string final
 *  @param out string a ser escrita a string final
 *
 */
void finalString(Arvore *arv, char *out) {
	if(ehFolha(arv))
		strcat(out, arv->info);
	else {
		Arvore *r = arv->prim;
		while(r != NULL) {
			finalString(r, out);
			r = r->irmao;
		}
	}
	return;
}

/**
 *  Libera arvore
 *
 *  @param arv arvore a ser liberada
 *
 */
void liberarArvore(Arvore **arv) {
	Arvore **r, **aux;
	if(ehFolha(*arv)) {
		FREE((*arv)->info);
		FREE(*arv);
		return;
	}
	r = &((*arv)->prim);
	aux = &((*r)->irmao);
	while(TRUE) {
		liberarArvore(r);
		r = aux;
		if(*r == NULL)
			break;
		else
			aux = &((*r)->irmao);
	}
	FREE((*arv)->info);
	FREE(*arv);
}


