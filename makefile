CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

all: show_node count_nodes alphatoe ttt1.o ttt2.o

alphatoe: ttt2.o ttt1.o alphatoe.o
	$(CC) $(CFLAGS) ttt1.o ttt2.o alphatoe.o -o alphatoe

alphatoe.o: alphatoe.c
	$(CC) $(CFLAGS) -c alphatoe.c -o alphatoe.o

ttt2.o: ttt2.c
	$(CC) $(CFLAGS) -c ttt2.c -o ttt2.o

ttt1.o: ttt1.c
	$(CC) $(CFLAGS) -c ttt1.c -o ttt1.o

show_node: show_node.o ttt1.o ttt2.o
	$(CC) $(CFLAGS) show_node.o ttt1.o ttt2.o -o show_node

show_node.o: show_node.c
	$(CC) $(CFLAGS) -c show_node.c -o show_node.o

count_nodes: count_nodes.o ttt1.o ttt2.o
	$(CC) $(CFLAGS) count_nodes.o ttt1.o ttt2.o -o count_nodes

count_nodes.o: count_nodes.c
	$(CC) $(CFLAGS) -c count_nodes.c -o count_nodes.o

clean:
	rm *.o show_node count_nodes alphatoe
