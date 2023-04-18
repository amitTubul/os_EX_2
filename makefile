CC=gcc
FLAGS=-Wall -fpic -g

cmp.o:cmp.c
	$(CC) $(FLAGS) -c cmp.c

cmp:cmp.o
	$(CC) $(FLAGS) -o cmp cmp.o

clean:
	rm -f cmp *.o

.PHONY:clean cmp