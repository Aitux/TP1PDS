main: main.o
	gcc -o exec main.o

main.o: main.c
	gcc -o main.o -c main.c -W -Wall -Werror