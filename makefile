compress: compress.o main.o
	gcc -o compress compress.o main.o

compress.o: compress.c
	gcc -o compress.o -c compress.c -W -Wall -ansi -pedantic

main.o: main.c compress.h
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic