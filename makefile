Driver: Driver.o MinMaxHeap.h
	g++ -g MinMaxHeap.h Driver.o -o Driver

Driver.o: Driver.cpp
	g++ -g -c Driver.cpp

Driver1: Driver1.o MinHeap.h
	g++ -g MinHeap.h Driver1.o -o Driver1

Driver1.o: Driver1.cpp
	g++ -g -c Driver1.cpp

clean:
	\rm *.o *~

run: Driver
	./Driver

run1: Driver1
	./Driver1
