dynamicarray: dynamicarray.o 
	g++ -Wall dynamicarray.o -o dynamicarray -L../lib/ -lds -lboost_unit_test_framework

dynamicarray.o: dynamicarray.cpp
	g++ -Wall -c dynamicarray.cpp 

clean:
	rm -f *.o dynamicarray 
