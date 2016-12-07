CC=/usr/bin/g++
CPP_FLAGS=-Wall -std=c++11 -g -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -pedantic
LD_FLAGS=-lboost_system  -lboost_program_options
BINARY=bin/client
SRCS=src/debug.cpp src/request.cpp
INCLUDE=-Iinclude/
TESTS=

all:
	$(CC) $(CPP_FLAGS) $(INCLUDE) $(LD_FLAGS) -Iinclude/ -o $(BINARY) $(SRCS) src/main.cpp

tests: compile-tests run-tests

compile-tests:
	for test in $(TESTS); do  $(CC) -Iinclude/ -std=c++11 -otests/$$test -lboost_system -lpthread -lboost_unit_test_framework tests/$$test.cpp $(SRCS) ; done


run-tests:
	for test in $(TESTS); do  ./tests/$$test ; done

clean:
	rm -f $(BINARY)
	find . -name '*~' | xargs rm -f
	find . -name '*.swp' | xargs rm -f
	for test in $(TESTS); do  rm -f ./tests/$$test ; done
