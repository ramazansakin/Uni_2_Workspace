all:
	gcc -c module1.c
	gcc -c MMMmodule.c
	gcc -c VMmodule.c
	gcc module1.o -o module1 -lpthread -lrt
	gcc MMMmodule.o -o MMMmodule -lpthread -lrt 
	gcc VMmodule.o -o VMmodule -lpthread  -lrt -lm
