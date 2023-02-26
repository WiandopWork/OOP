build: main.o long_arithmetic.o LongNum.o LongFrac.o LongComplexNum.o LongComplexFrac.o
	g++ main.o long_arithmetic.o LongNum.o LongFrac.o LongComplexNum.o LongComplexFrac.o
	./a.out

main.o: main.cpp
	g++ -c main.cpp

long_arithmetic.o: long_arithmetic.cpp	
	g++ -c long_arithmetic.cpp

LongNum.o: LongNum.cpp
	g++ -c LongNum.cpp

LongFrac.o: LongFrac.cpp
	g++ -c LongFrac.cpp

LongComplexNum.o: LongComplexNum.cpp
	g++ -c LongComplexNum.cpp

LongComplexFrac.o: LongComplexFrac.cpp
	g++ -c LongComplexFrac.cpp

clean: 
	rm *.out
	rm *.o