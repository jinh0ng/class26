all: add-nbo

add-nbo: main.o add-nbo.o
	g++ -o add-nbo main.o add-nbo.o

main.o: main.cpp add-nbo.h
	g++ -c -o main.o main.cpp

sum.o: add-nbo.h add-nbo.cpp
	g++ -c -o add-nbo.o add_nbo.cpp

clean:
	rm -f *.o
	rm -f add-nbo
