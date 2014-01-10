othello.exe: othello.o board.o player.o 
	g++ -o othello.exe othello.o board.o player.o
		
othello.o: othello.cpp
	g++ -c othello.cpp
	
board.o: board.cpp board.hpp
	g++ -c board.cpp
	
player.o: player.cpp player.hpp
	g++ -c player.cpp

debug:
	g++ -g -o othelloDebug.exe othello.cpp board.cpp player.cpp 

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.hpp backups
	cp Makefile backups
