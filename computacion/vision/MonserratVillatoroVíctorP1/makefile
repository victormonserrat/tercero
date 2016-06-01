all: getStats

getStats: getStats.cpp
	g++ -Wall -o getStats getStats.cpp `pkg-config opencv --cflags --libs`

clean:
	rm getStats
