/**
 *  Sistemas de Lindenmayer
 *  arvore.c 
 *  Implementacao do sistema de regras
 *  Ver documentacao para mais informacoes
 *
 *  @author Fernando Barbosa Neto
 *  @author Jeferson De Oliveira Batista
 *
 */

#include "regra.h"

/**
 *  Cria regra
 *
 *  @return conjunto vazio de regras
 *
 */
Regra *criarRegra() {
	return NULL;
}

/**
 *  Inclui regra no conjunto de regras
 *
 *  @param regras conjunto de regras a receber nova regra
 *  @param c caracter do lado esquerdo do sinal de igualdade da regra
 *  @param result string do lado direito do sinal de igualdade da regra
 *
 */
void incluirRegra(Regra **regras, char c, char *result) {
	Regra *nova = (Regra*) malloc(sizeof(Regra));
	nova->c = c;
	int t = strlen(result) + 1;
	nova->result = (char*) calloc(t, sizeof(char));
	strcpy(nova->result, result);
	nova->prox = NULL;
	Regra **r;
	r = regras;
	while(*r != NULL)
		r = &((*r)->prox);
	*r = nova;
}

/**
 *  Elimina regras
 *
 *  @param regras conjunto de regras que tera regras eliminadas
 *
 */
void eliminarRegra(Regra **regras) {
	Regra **r, **aux;
	r = regras;
	while(*r != NULL) {
		aux = &((*r)->prox);
		FREE((*r)->result);
		FREE(*r);
		r = aux;
	}
}


