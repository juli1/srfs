CC=/usr/bin/g++
CPP_FLAGS=-Wall -std=c++11 -g -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -pedantic
LD_FLAGS=-lboost_system -lpthread
BINARY=bin/server
SRCS=src/main.cpp src/client.cpp src/server.cpp src/filehandle.cpp
INCLUDE=-Iinclude/

all:
	$(CC) $(CPP_FLAGS) $(INCLUDE) $(LD_FLAGS) -Iinclude/ -o $(BINARY) $(SRCS) 

clean:
	rm -f $(BINARY)
	find . -name '*~' | xargs rm -f
	find . -name '*.swp' | xargs rm -f
