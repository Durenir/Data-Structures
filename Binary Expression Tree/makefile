proj4.x: proj4_driver.o bet.o
	g++ -o proj4.x -std=c++11 proj4_driver.o bet.o
proj4_driver.o: proj4_driver.cpp
	g++ -c -std=c++11 proj4_driver.cpp
bet.o: bet.h bet.cpp
	g++ -c -std=c++11 bet.h
	g++ -c -std=c++11 bet.cpp
clean:
	-rm *.o
	-rm *.h.gch
