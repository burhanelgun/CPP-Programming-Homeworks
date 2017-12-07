connectfour: main.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o Cell.o 
	g++ -std=c++11 Cell.o ConnectFourDiag.o ConnectFourPlus.o ConnectFourPlusUndo.o ConnectFourAbstract.o main.o -o exe

main.o: main.cpp ConnectFourAbstract.h ConnectFourPlus.h ConnectFourDiag.h ConnectFourPlusUndo.h Cell.h
	g++ -std=c++11 -c main.cpp 

ConnectFourAbstract.o: ConnectFourAbstract.cpp ConnectFourAbstract.h
	g++ -std=c++11 -c ConnectFourAbstract.cpp 

ConnectFourPlus.o: ConnectFourPlus.cpp ConnectFourPlus.h ConnectFourAbstract.h Cell.h
	g++ -std=c++11 -c ConnectFourPlus.cpp 

ConnectFourDiag.o:ConnectFourDiag.cpp ConnectFourDiag.h ConnectFourAbstract.h Cell.h
	g++ -std=c++11 -c ConnectFourDiag.cpp 

ConnectFourPlusUndo.o:ConnectFourPlusUndo.cpp ConnectFourPlusUndo.h ConnectFourPlus.h
	g++ -std=c++11 -c ConnectFourPlusUndo.cpp 

Cell.o:Cell.cpp Cell.h
	g++ -std=c++11 -c Cell.cpp 


clean:
	rm *.o exe
