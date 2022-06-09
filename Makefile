all: test

test: test.c main.o main.h
		gcc -o test test.o main.o
test.o: test.c main.h
		gcc -c test.c
main.o: main.c main.h
		gcc -c main.c