proj5.x: proj5.cpp passserver.o
	g++ -std=c++11 -lcrypt proj5.cpp passserver.o -o proj5.x
passserver.o: passserver.h passserver.cpp hashtable.hpp hashtable.h
	g++ -c -std=c++11 passserver.cpp
clean:
	-rm *.o
