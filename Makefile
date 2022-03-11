CFLAGS = -c 
STD = -std=c++17
CC = g++
LIBS = -lm 

all:  clean main

main:	 util.o solver.o
	${CC} ${STD}  solver.o util.o main.cpp -o main
util.o:
	${CC} ${STD} ${CFLAGS} util.cpp
solver.o:
	${CC} ${STD} ${CFLAGS} solver.cpp
clean:
	rm -f *.o *~ main
