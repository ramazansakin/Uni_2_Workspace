all:
	gcc -c verifier.c
	gcc -c matrixMultilier.c
	gcc -c randMatGenerator.c
	gcc matrixMultilier.o -o matMult -lpthread
	gcc randMatGenerator.o -o rand -lpthread
	gcc verifier.o -o very -lpthread
