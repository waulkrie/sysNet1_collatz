CFLAGS = -g -Wall -std=c++14 -pthread
CC = g++
PROG_NAME=mt-collatz

objects = main.o collatz.o

collatz: $(objects)
	$(CC) $(CFLAGS) -o $(PROG_NAME) $(objects)

main.o: main.cpp collatz.hpp
collatz.o: collatz.cpp collatz.hpp

.PHONY : clean
clean: 
	rm $(PROG_NAME) $(objects)
