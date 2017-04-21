Driver: Driver.o MinMaxHeap.h
	g++ -g MinMaxHeap.h Driver.o -o Driver

test1: MinMaxHeap.h test1.cpp
	g++ -g MinMaxHeap.h test1.cpp -o test1
	./test1 > output1.txt
	g++ -g check1.cpp -o check1
	./check1
	valgrind ./test1

test2: MinMaxHeap.h test2.cpp
	g++ -g MinMaxHeap.h test2.cpp -o test2
	./test2 > output2.txt
	g++ -g check2.cpp -o check2
	./check2
	valgrind ./test2

test3: MinMaxHeap.h NoCopyString.h
	g++ -g test3.cpp NoCopyString.cpp -o test3
	./test3 > output3.txt
	g++ -g check3.cpp -o check3
	./check3
	valgrind ./test3

test4: MinMaxHeap.h test4.cpp
	g++ -g MinMaxHeap.h test4.cpp -o test4
	./test4 > output4.txt
	g++ -g check4.cpp -o check4
	./check4
	valgrind ./test4

test5: MinMaxHeap.h test5.cpp
	g++ -g MinMaxHeap.h test5.cpp -o test5
	./test5 > output5.txt
	g++ -g check5.cpp -o check5
	./check5
	valgrind ./test5

test6: MinMaxHeap.h test6.cpp
	g++ -g MinMaxHeap.h test6.cpp -o test6
	./test6 > output6.txt
	g++ -g check6.cpp -o check6
	./check6
	valgrind ./test6

Driver.o: Driver.cpp
	g++ -g -c Driver.cpp

Driver1: Driver1.o MinHeap.h
	g++ -g MinHeap.h Driver1.o -o Driver1

Driver1.o: Driver1.cpp
	g++ -g -c Driver1.cpp

clean:
	\rm -f test1 test2 test3 test4 test5 test6 Driver
	\rm -f check1 check2 check3 check4 check5 check6
	\rm -f *.o *~

run: Driver
	./Driver

run1: Driver1
	./Driver1
