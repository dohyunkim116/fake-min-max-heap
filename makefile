Driver: Driver.o MinHeap.h MaxHeap.h
	g++ -g MinHeap.h MaxHeap.h Driver.o -o Driver

Driver.o: Driver.cpp
	g++ -g -c Driver.cpp

clean:
	\rm *.o *~

run: Driver
	./Driver
