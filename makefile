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

codecA.o:codecA.c
	$(CC) $(FLAGS) -c codecA.c

libcodecA.so:codecA.o
	$(CC) -shared -o libcodecA.so codecA.o

codecB.o:codecB.c
	$(CC) $(FLAGS) -c codecB.c

libcodecB.so:codecB.o
	$(CC) -shared -o libcodecB.so codecB.o

encode:encode.c libcodecA.so libcodecB.so
	$(CC) -o encode encode.c -L. -lcodecA -lcodecB

decode:decode.c libcodecA.so libcodecB.so
	$(CC) -o decode decode.c -L. -lcodecA -lcodecB

clean:
	rm -f copy cmp encode decode *.o *.so

.PHONY:clean cmp copy encode decode