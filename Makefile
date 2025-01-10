main.o: main.c
	gcc -c main.c
jogo.o: jogo.c
	gcc -c jogo.c
avl.o: avl.c
	gcc -c avl.c
trie.o: trie.c
	gcc -c trie.c
prog: main.o jogo.o avl.o trie.o
	gcc -o prog main.o jogo.o avl.o trie.o
all: prog
	./prog
clean:
	rm *.o prog