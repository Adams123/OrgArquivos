all: prim.o btree.o main.o compile

compile:
	@gcc prim.o btree.o main.o -o trab4 -g -lm

main.o:
	@gcc -c main.c -g

prim.o:
	@gcc -c prim.c -g

btree.o:
	@gcc -c btree.c -g
clean:
	@rm *.o
run:
	@./trab4
zip:
	zip -r trab4 *.c *.h Makefile
