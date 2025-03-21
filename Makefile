.PHONY: clean
main: main.o Vector.o
	g++ main.o Vector.o -o main
main.o: main.cpp
	g++ -c main.cpp
Vector.o: Vector.cpp
	g++ -c Vector.cpp
clean:
	rm *.o main