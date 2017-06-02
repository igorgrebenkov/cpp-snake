CPPFLAGS = -g -Wall -I include/ 
LDFLAGS = -L lib/

snake : main.o snake.o game.o 
	g++ -std=c++11 -Iinclude/ -o snake main.o snake.o game.o -lncurses

main.o : src/main.cpp
	g++ -std=c++11 -Iinclude/  -c src/main.cpp

point.o : include/point.h

food.o : include/food.h

snake.o : src/snake.cpp include/snake.h
	g++ -std=c++11 -Iinclude/ -c src/snake.cpp

window.o : include/window.h

game.o : src/game.cpp include/game.h
	g++ -std=c++11 -Iinclude/  -c src/game.cpp

clean : 
	rm -r *.o