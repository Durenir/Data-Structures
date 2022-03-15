all: driver.x mydriver.x
driver.x: driver.o
	g++ -o driver.x -std=c++11 driver.o
mydriver.x: mydriver.o
	g++ -o mydriver.x -std=c++11 mydriver.o
driver.o: driver.cpp tnode.h tlist.h tlist.hpp
	g++ -c -std=c++11 driver.cpp
mydriver.o: mydriver.cpp tnode.h tlist.h tlist.hpp
	g++ -c -std=c++11 mydriver.cpp
clean:
	-rm *.o

