all: arvore regra psinterface main

arvore: arvore.c
	gcc -std=c99 -Wall -Werror -pedantic -c arvore.c
	
regra: regra.c
	gcc -std=c99 -Wall -Werror -pedantic -c regra.c
	
pilha: pilha.c
	gcc -std=c99 -Wall -Werror -pedantic -c pilha.c
	
psinterface: psinterface.c
	gcc -std=c99 -c psinterface.c
	
main: arvore.o regra.o psinterface.o pilha.o main.c 
	gcc -std=c99 -Wall -Werror -pedantic -o lsystem main.c arvore.o regra.o pilha.o psinterface.o -lm
	
run:
	valgrind ./lsystem entrada.lsy saida1.ps saida2.ps
	
clean:
	rm arvore.o regra.o psinterface.o pilha.o lsystem saida1.ps saida2.ps


