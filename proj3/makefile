OBJS = main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG)

shortest_path : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o mst

main.o : graph.h pq.h main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	\rm *.o mst thanh*.zip
zip :
	zip thanh_hw3.zip graph.h pq.h mst.h main.cpp makefile README.txt output.pdf
