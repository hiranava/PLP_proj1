##===============================================
# the name of the compiled binary
TARGET  := p1

p1 : PLP.o Node.o 
	g++ -o p1 PLP.o Node.o 

PLP.o : PLP.cpp Node.h 
	g++ -c PLP.cpp
Node.o : Node.cpp Node.h
	g++ -c Node.cpp
run:./p1

cl:rm -f *.o p1
