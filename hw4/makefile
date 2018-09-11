all: header

header : main.o
	 g++ -std=c++11 main.cpp -o exe

main.o:  main.cpp
	 g++ -std=c++11 -c main.cpp

clean:
	 rm *.o exe
