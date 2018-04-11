all:
	gcc -c Client.c
	gcc -c Server.c
	gcc -o Client Client.o
	gcc -o Server Server.o -lpthread
	rm Server.o
	rm Client.o
