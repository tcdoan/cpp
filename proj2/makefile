OBJS = main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG)

shortest_path : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o shortest_path

main.o : graph.h priority_queue.h shortest_path.h main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	\rm *.o shortest_path thanh*.zip
zip :
	zip thanh_hw2.zip graph.h priority_queue.h shortest_path.h main.cpp makefile README.txt screen_shots.pdf
