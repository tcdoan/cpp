OBJS = main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG)

mst: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o mst

main.o : kruskal.h graph.h pq.h uf.h main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	\rm *.o mst thanh_hw3.zip
zip :
	zip thanh_hw3.zip README.txt makefile main.cpp kruskal.h graph.h pq.h uf.h tiny_input.graph medium_input.graph mst_test_data
