all: test clean
CFLAGS = -wall -werror -g
test: threadPool.o
	gcc -o run test.c threadPool.o osqueue.o -lpthread

threadPool.o: osqueue.o
	gcc -static -g -c threadPool.c

osqueue.o:
	gcc -static -g -c osqueue.c

clean: 
	rm -f *.o
