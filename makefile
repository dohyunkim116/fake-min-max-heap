Driver: Driver.o MinHeap.h
	g++ -g MinHeap.h Driver.o -o Driver

Driver.o: Driver.cpp
	g++ -g -c Driver.cpp

clean:
	\rm *.o *~

run: Driver
	./Driver
