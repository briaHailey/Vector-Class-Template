driver.x : driver.cpp
	g++ -std=c++11 -o driver.x driver.cpp

proj: driver.o tvector.o
	g++ -std=c++11 tvector.o driver.o -o proj

tvector.o: tvector.cpp tvector.h
	g++ -c  tvector.cpp

driver.o: driver.cpp tvector.h
	g++ -c driver.cpp

clean:
	rm -f *.o proj
