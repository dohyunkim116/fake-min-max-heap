Driver: Driver.o MinMaxHeap.h
	g++ -g MinMaxHeap.h Driver.o -o Driver

test1: MinMaxHeap.h test1.cpp
	g++ -g MinMaxHeap.h test1.cpp -o test1
	./test1

test2: MinMaxHeap.h test2.cpp
	g++ -g MinMaxHeap.h test2.cpp -o test2
	./test2

test3: MinMaxHeap.h NoCopyString.h
	g++ -g test3.cpp NoCopyString.cpp -o test3
	./test3

test4: MinMaxHeap.h test4.cpp
	g++ -g MinMaxHeap.h test4.cpp -o test4
	./test4

test5: MinMaxHeap.h test5.cpp
	g++ -g MinMaxHeap.h test5.cpp -o test5
	./test5

test6: MinMaxHeap.h test6.cpp
	g++ -g MinMaxHeap.h test6.cpp -o test6
	./test6

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
