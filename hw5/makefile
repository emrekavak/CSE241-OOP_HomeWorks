all: header

header : main.o connectfourabstract.o cell.o connectfourplus.o connectfourdiag.o connectfourplusundo.o
	 g++ -std=c++11 main.cpp connectfourabstract.cpp cell.cpp connectfourplus.cpp connectfourdiag.cpp connectfourplusundo.cpp -o exe
main.o:  main.cpp
	 g++ -std=c++11 -c main.cpp
connectfourabstract.o: connectfourabstract.cpp
	g++ -std=c++11 -c connectfourabstract.cpp
cell.o: cell.cpp
	g++ -std=c++11 -c cell.cpp
connectfourplus.o:connectfourplus.cpp
	g++ -std=c++11 -c connectfourplus.cpp
connectfourdiag.o: connectfourdiag.cpp
	g++ -std=c++11 -c connectfourdiag.cpp 	
connectfourplusundo.o: connectfourplusundo.cpp
	g++ -std=c++11 -c connectfourplusundo.cpp
clean:
	 rm *.o exe
