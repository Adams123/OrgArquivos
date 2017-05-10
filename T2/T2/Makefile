all:
	@gcc huffman.o run_lenght.o main.o -o main
clean:
	@rm *.o
huffman.o:
	@gcc -g -c huffman.c

run_lenght.o:
	@gcc -g -c run_lenght.c

main.o:
	@gcc -g -c main.c

run:
	@./main

zip:
	@zip -r T2.zip Makefile main.c run_lenght.c run-lenght.h huffman.c huffman.h




