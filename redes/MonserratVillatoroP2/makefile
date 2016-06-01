all: bingo_server.cpp bingo_client.cpp card.cpp card.hpp game.cpp game.hpp split.cpp split.hpp user.cpp user.hpp
	g++ bingo_server.cpp card.cpp game.cpp split.cpp user.cpp -o bingo_server -std=c++11
	g++ bingo_client.cpp card.cpp game.cpp split.cpp user.cpp -o bingo_client -std=c++11

server: bingo_server.cpp card.cpp card.hpp game.cpp game.hpp split.cpp split.hpp user.cpp user.hpp
	g++ bingo_server.cpp card.cpp game.cpp split.cpp user.cpp -o bingo_server -std=c++11

client: bingo_client.cpp card.cpp card.hpp game.cpp game.hpp split.cpp split.hpp user.cpp user.hpp
	g++ bingo_client.cpp card.cpp game.cpp split.cpp user.cpp -o bingo_client -std=c++11

clean:
	rm bingo_server bingo_client
