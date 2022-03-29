CFLAGS = -c 
STD = -std=c++17
CC = g++
LIBS = -lm 

all:  clean main

run:  clean main
	./main 5 4

main:	 util.o solver.o test.o
	${CC} ${STD}  solver.o util.o test.o main.cpp -o main
util.o:
	${CC} ${STD} ${CFLAGS} util.cpp
solver.o:
	${CC} ${STD} ${CFLAGS} solver.cpp
test.o:
	${CC} ${STD} ${CFLAGS} test.cpp
clean:
	rm -f *.o *~ main
