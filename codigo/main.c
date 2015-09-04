/**
 *  Sistemas de Lindenmayer
 *  main.c 
 *  Arquivo Principal para uso do Sistema
 *  de Lindenmayer
 *  Ver documentacao para mais informacoes
 *
 *  @author Fernando Barbosa Neto
 *  @author Jeferson De Oliveira Batista
 *
 */

#include "arvore.h"
#include "pilha.h"

void le_arquivo(char arquivo[], double *angle, uint *order, double *imagerotate, char aaxiom[], Regra **r);
char *geraTurtleStr(char *output, double angle);

int main(int argc, char *argv[]) {
	
	if(argc < 4) {
		printf("Usage: ./main arqDeEntrada arqDeSaida1 arqDeSaida2\n");
		return 1;
	}
	
	int i;
	
	double angle = 0.0;
	uint order = 0;
	double imagerotate = 0.0;
	char aaxiom[1024] = "";
	
	Regra *regras = NULL;
	
	le_arquivo(argv[1], &angle, &order, &imagerotate, aaxiom, &regras);
	
	Arvore *arv = criarArvore(aaxiom);
	
	imprimirFolhas(arv);
	//printf("\n");
	for(i = 0; i < order; i++) {
		crescerArvore(arv, regras);
		//imprimirFolhas(arv);
		//printf("\n");
	}
	char *output = (char*) calloc(1000001, sizeof(char));
	output[0] = '\0';
	finalString(arv, output);
	//printf("\n%s\n", output);
	genps(angle, order, imagerotate, output, argv[2]);
	
	char *turtlestr;
	turtlestr = geraTurtleStr(output, angle);
	
	genpsTurtle(angle, order, imagerotate, turtlestr, argv[3]);
	
	eliminarRegra(&regras);
	FREE(output);
	FREE(turtlestr);
	liberarArvore(&arv);
	return 0;
}

/**
 *  Le arquivo de entrada
 *
 *  @param arquivo nome do arquivo de entrada
 *  @param angle angulo a ser lido
 *  @param order ordem a ser lida
 *  @param imagerotate rotacao da imagem a ser lida
 *  @param aaxiom axioma a ser lido
 *  @param r regras a serem lidas
 *
 */
void le_arquivo(char arquivo[], double *angle, uint *order, double *imagerotate, char aaxiom[], Regra **r){

	FILE *entrada;
	
	char check[1024], trash[1024];
	char c, result[1024];
	
	entrada = fopen(arquivo, "r");
	
	if(entrada == NULL) {
		printf("Erro ao acessar %s\n", arquivo);
		return;
	}
	
	while(!feof(entrada)){
		
		fscanf(entrada, "%s", check);
		
		if(!strcmp(check, "angle")){
			
			// recebe angulo
			fscanf(entrada, "%lf", angle);
			
		}
		else if(!strcmp(check, "order")){
			
			// recebe ordem
			fscanf(entrada, "%u", order);
			
		}
		
		else if(!strcmp(check, "rotate")){
			
			// recebe rotacao da imagem
			fscanf(entrada, "%lf", imagerotate);
			
		}
		else if(!strcmp(check, "axiom")){
			
			// recebe axioma
			fscanf(entrada, "%s", aaxiom);
			
		}
		else if(fscanf(entrada, " = %s", result)){
			
			// recebe regra de producao
			c = check[0];
			incluirRegra(r, c, result);
			
		}
		else if(check[0]==';'){
			
			// ignora ateh final da linha
			if(strlen(check)==1)
				fgets(trash, sizeof(trash), entrada);
			else
				fscanf(entrada, "\n");
			
		}
		
	}
	
	fclose(entrada);
}

/**
 *  Gera a string de tartaruga
 *
 *  @param output string para gerar a string de tartaruga
 *  @param angle angulo usado
 *  @return string da tartaruga
 *
 */
char *geraTurtleStr(char *output, double angle) {
	
	Pilha *p = NULL;
	double x=0, y=0;
	double antx=0, anty=0;
	double orienta = 0;
	double comp = 72, aospoucos;
	int i, j;
	//char *pega = NULL;
	char pega[2];
	char *precioso = (char*) calloc(1000001, sizeof(char));
	precioso[0] = '\0';
	char temp[100];
	
	for(i = 0; i < strlen(output); i++) {
	
		if(output[i] == 'F') {
		
			// gera string da forma n 0 0 m 72 0 l s
			antx = x;
			anty = y;
			x = antx + comp*cos(orienta);
			y = anty + comp*sin(orienta);
			sprintf(temp, "n %lf %lf m %lf %lf l s \n", antx, anty, x, y);
			strcat(precioso, temp);
			
		}
		
		else if(output[i] == 'G') {
		
			// gera string da forma n 0 0 m 72 0 l
			antx = x;
			anty = y;
			x = antx + comp*cos(orienta);
			y = anty + comp*sin(orienta);
			sprintf(temp, "n %lf %lf m %lf %lf l \n", antx, anty, x, y);
			strcat(precioso, temp);
			
		}
		
		else if(output[i] == '+') {
		
			// vira tartaruga com angulo positivo
			orienta += 2*PI/angle;
		}
		
		else if(output[i] == '-') {
		
			// vira tartaruga com angulo negativo
			orienta -= 2*PI/angle;
		}
		
		else if(output[i] == '[') {
		
			// empilha estado da tartaruga
			p = empilharPilha(p, x, y, orienta, comp);
		}
		
		else if(output[i] == ']') {		
		
			// desempilha estado da tartaruga	
			x = p->x;
			y = p->y;
			orienta = p->ori;
			comp = p->comp;
			p = desempilharPilha(p);
		}
		
		else if(output[i] == '!') {
		
			// inverte sentidos
			angle = -angle;
		}
		
		else if(output[i] == '|') {
		
			// gira 180 graus
			orienta += PI;
		}
		
		else if(output[i] == '@') {
			
			// altera comprimento do traco		
			aospoucos = 0;
			++i;
			
			if(output[i]=='I'){
				++i;
				
				if(output[i]=='Q'){
					++i;
					for(j=i;output[i]>'0'&&output[i]<'9';i++){
						pega[0] = output[i];
						aospoucos += ((double)(atoi(pega)))*pow(10,i-j);
					}
					--i;
					comp *= 1/sqrt(aospoucos);
					
				}
				
				else{
					++i;
					for(j=i;output[i]>'0'&&output[i]<'9';i++){
						pega[0] = output[i];
						aospoucos += ((double)(atoi(pega)))*pow(10,i-j);
					}
					--i;
					
					comp *= 1/aospoucos;
					
				}
				
			}
				
			else if(output[i]=='Q'){
				++i;
					for(j=i;output[i]>'0'&&output[i]<'9';i++){
						pega[0] = output[i];
						aospoucos += ((double)(atoi(pega)))*pow(10,i-j);
					}
				--i;
				
				comp *= sqrt(aospoucos);
					
			}
			
			else{
					for(j=i;output[i]>'0'&&output[i]<'9';i++){
						pega[0] = output[i];
						aospoucos += ((double)(atoi(pega)))*pow(10,i-j);
					}
				--i;
				
				comp *= aospoucos;
				
			}				
		}	
	}
	destruirPilha(p);
	return precioso;
}


