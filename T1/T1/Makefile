all: tad.o main.o
	@gcc tad.o main.o -o teste

tad.o:
	@gcc -c tad.c

main.o:
	@gcc -c main.c

run:
	@./teste

zip:
	@zip -r teste.zip Makefile main.c tad.c tad.h