all: bancoDeDados.o listaInvertida.o indiceSecundario.o indicePrimario.o controler.o main.o compile

compile:
	@gcc bancoDeDados.o listaInvertida.o indiceSecundario.o indicePrimario.o controler.o main.o -o trab3 -g -lm

main.o:
	@gcc -c main.c -g

bancoDeDados.o:
	@gcc -c bancoDeDados.c -g

indicePrimario.o:
	@gcc -c indicePrimario.c -g

indiceSecundario.o:
	@gcc -c indiceSecundario.c -g

listaInvertida.o:
	@gcc -c listaInvertida.c -g

controler.o:
	@gcc -c controler.c -g

clean:
	@rm *.o

run:
	@./trab3

zip:
	zip -r trab3 *.c *.h Makefile
