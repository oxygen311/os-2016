CFLAGS = -c -Wall

hello_world: hello_world.o
	gcc -s hello_world.o -o hello_world

hello_world.o: hello_world.c
	gcc $(CFLAGS) hello_world.c -o hello_world.o

clean:
	rm hello_world hello_world.o
