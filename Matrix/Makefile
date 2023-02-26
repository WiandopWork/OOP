build: main.o matrix.o
	g++ main.o matrix.o
	./a.out

main.o: main.cpp
	g++ -c main.cpp

matrix.o: matrix.cpp
	g++ -c matrix.cpp

clean:
	rm -f *.o
	rm -f *.exe