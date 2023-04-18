CC=gcc
FLAGS=-Wall -fpic -g

cmp.o:cmp.c
	$(CC) $(FLAGS) -c cmp.c

cmp:cmp.o
	$(CC) $(FLAGS) -o cmp cmp.o

copy.o:copy.c
	$(CC) $(FLAGS) -c copy.c

copy:copy.o
	$(CC) $(FLAGS) -o copy copy.o

clean:
	rm -f copy cmp *.o

.PHONY:clean cmp copy