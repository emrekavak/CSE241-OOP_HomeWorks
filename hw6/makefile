all: header

header : main.o gtusetbase.o gtuset.o gtumap.o
	 g++ -std=c++11 main.cpp gtusetbase.cpp gtuset.cpp gtumap.cpp -o exe
main.o:  main.cpp
	 g++ -std=c++11 -c main.cpp
gtusetbase.o: gtusetbase.cpp
	g++ -std=c++11 -c gtusetbase.cpp
gtuset.o: gtuset.cpp
	g++ -std=c++11 -c gtuset.cpp

gtumap.o: gtumap.cpp
	g++ -std=c++11 -c gtumap.cpp

clean:
	 rm *.o exe
