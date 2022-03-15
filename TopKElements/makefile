proj6.x: proj6.o topkelements.o
	g++ -o proj6.x -std=c++11 proj6.o topkelements.o
proj6.o: proj6.cpp
	g++ -c -std=c++11 proj6.cpp
topkelements.o: topkelements.cpp topkelements.h
	g++ -c -std=c++11 topkelements.h
	g++ -c -std=c++11 topkelements.cpp
clean:
	-rm *.o
	-rm *.h.gch
