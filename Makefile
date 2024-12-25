all: arvore.o tp.o
	@gcc arvore.o tp.o -o exe
	@rm -r arvore.o tp.o
arvore.o: arvore.c
	@gcc arvore.c -c -Wall
tp.o: tp.c
	@gcc tp.c -c -Wall
run:
	@./exe
