#include <stdlib.h>
#include <string.h>
#include "lsystem.h"

//#define FREE2(p) if(p != NULL) {free(p); p = NULL;}

typedef struct regra {
	char c;
	char *result; // vamos usar alocação dinâmica aqui
	struct regra *prox;
} Regra;

Regra *criarRegra();
void incluirRegra(Regra **regras, char c, char *result);
void eliminarRegra(Regra **regras);

