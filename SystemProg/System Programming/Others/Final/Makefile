all:
	gcc -c sunucu.c
	gcc -c istemci.c
	gcc -o sunucu sunucu.o -lpthread
	gcc -o istemci istemci.o -lpthread
	rm sunucu.o
	rm istemci.o
