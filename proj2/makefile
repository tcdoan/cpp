OBJS = test.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG)

dijkstra : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o dijkstra

test.o : graph.h priority_queue.h test.cpp
	$(CC) $(CFLAGS) test.cpp

clean:
	\rm *.o dijkstra
zip :
	zip dijskstra.zip graph.h priority_queue.h client.cpp 
