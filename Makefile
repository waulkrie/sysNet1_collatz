CFLAGS = -g -Wall -std=c++14 -pthread
CC = g++
PROG_NAME=mt-collatz

objects = main.o collatz.o

.PHONY : all
all: $(PROG_NAME)

mt-collatz: $(objects)
	$(CC) $(CFLAGS) -o $(PROG_NAME) $(objects)

main.o: main.cpp collatz.hpp
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c main.cpp

collatz.o: collatz.cpp collatz.hpp
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c collatz.cpp

.PHONY : clean
clean: 
	rm $(PROG_NAME) $(objects)
