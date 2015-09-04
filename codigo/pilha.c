/**
 *  Sistemas de Lindenmayer
 *  arvore.c 
 *  Implementacao da TAD pilha
 *  Ver documentacao para mais informacoes
 *
 *  @author Fernando Barbosa Neto
 *  @author Jeferson De Oliveira Batista
 *
 */

#include "pilha.h"

/**
 *  Empilha pilha
 *
 *  @param p pilha a ser empilhada
 *  @param posx posicao x a ser empilhada
 *  @param posy posicao y a ser empilhada
 *  @param orienta estado de orientacao a ser empilhado
 *  @param comprimento comprimento da linha a ser empilhado
 *  @return pilha empilhada
 *
 */
Pilha *empilharPilha(Pilha *p, double posx, double posy, double orienta, double comprimento) {
	Pilha *nova = (Pilha*) malloc(sizeof(Pilha));
	nova->x = posx;
	nova->y = posy;
	nova->ori = orienta;
	nova->comp = comprimento;
	nova->prox = p;
	return nova;
}

/**
 *  Desempilha pilha
 *
 *  @param p pilha a ser desempilhada
 *  @return pilha desempilhada
 *
 */
Pilha *desempilharPilha(Pilha *p) {
	Pilha *t = p->prox;
	LIBERAR(p);
	return t;
}

/**
 *  Destroi pilha
 *
 *  @param p pilha a ser detruida
 *  @return pilha destruida
 *
 */
Pilha *destruirPilha(Pilha *p) {
	while(p != NULL) {
		p = desempilharPilha(p);
	}
	return p;
}


