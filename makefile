CC=gcc
FLAGS=-Wall -fpic -g

all:cmp copy encode decode

cmp:cmp.c
	$(CC) $(FLAGS) -o cmp cmp.c

copy:copy.c
	$(CC) $(FLAGS) -o copy copy.c

libcodecA.so:codecA.c
	$(CC) -shared -fpic codecA.c -o libcodecA.so

libcodecB.so:codecB.c
	$(CC) -shared -fpic codecB.c -o libcodecB.so

encode:encode.c libcodecA.so libcodecB.so
	$(CC) encode.c -L. -lcodecA -lcodecB -o encode -ldl

decode:decode.c libcodecA.so libcodecB.so
	$(CC) decode.c -L. -lcodecA -lcodecB -o decode -ldl

stshell: stshell.c
	$(CC) $(FLAGS) -o stshell stshell.c

stshell_test: stshell_test.c
	$(cc) $(FLAGS) -o stshell_test stshell_test.c
clean:
	rm -f copy cmp encode decode stshell *.o *.so

.PHONY:clean all cmp copy encode decode