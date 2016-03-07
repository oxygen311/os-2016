CFLAGS = -c -Wall

cat: cat.o
	gcc cat.o -o cat

cat.o: cat.c
	gcc $(CFLAGS) cat.c

clean:
	rm cat cat.o
