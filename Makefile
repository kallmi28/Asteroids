CXX=g++
CFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11 -g
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf
PROGRAM_NAME=kallumir
DOXYFILE=Doxyfile


.PHONY: all
all: compile doc

.PHONY: compile
compile: $(PROGRAM_NAME)

.PHONY: clean
clean:
	rm -rf src/*.o $(PROGRAM_NAME) doc/* doc/

.PHONY: run
run:
	./$(PROGRAM_NAME)

.PHONY: doc
doc: $(DOXYFILE) src/*
	doxygen $(DOXYFILE)

$(PROGRAM_NAME):  src/vector.o src/polygon.o src/upgrade.o src/movingobject.o src/player.o src/shot.o src/asteroid.o src/game.o src/window.o src/main.o
	$(CXX) $(CFLAGS) -o $@ $^ $(LIBS)

src/main.o: src/main.cpp src/window.h src/player.h src/vector.h src/polygon.h src/shot.h src/movingobject.h src/asteroid.h src/game.h src/upgrade.h src/constants.cpp
	$(CXX) $(CFLAGS) -c -o $@ $< $(LIBS)
src/window.o: src/window.cpp src/window.h src/player.h src/vector.h src/polygon.h src/shot.h src/movingobject.h src/asteroid.h src/game.h src/upgrade.h src/constants.cpp
	$(CXX) $(CFLAGS) -c -o $@ $< $(LIBS)
src/game.o: src/game.cpp src/game.h src/player.h src/vector.h src/polygon.h src/shot.h src/movingobject.h src/asteroid.h src/upgrade.h src/constants.cpp
	$(CXX) $(CFLAGS) -c -o $@ $< $(LIBS)
src/asteroid.o: src/asteroid.cpp src/asteroid.h src/vector.h src/polygon.h src/movingobject.h src/constants.cpp
	$(CXX) $(CFLAGS) -c -o $@ $< $(LIBS)
src/shot.o: src/shot.cpp src/shot.h src/vector.h src/polygon.h src/movingobject.h src/constants.cpp
	$(CXX) $(CFLAGS) -c -o $@ $< $(LIBS)
src/player.o: src/player.cpp src/player.h src/vector.h src/polygon.h src/shot.h src/movingobject.h src/constants.cpp
	$(CXX) $(CFLAGS) -c -o $@ $< $(LIBS)
src/movingobject.o: src/movingobject.cpp src/movingobject.h src/vector.h src/polygon.h src/constants.cpp
	$(CXX) $(CFLAGS) -c -o $@ $< $(LIBS)
src/upgrade.o: src/upgrade.cpp src/upgrade.h src/polygon.h src/vector.h
	$(CXX) $(CFLAGS) -c -o $@ $< $(LIBS)
src/polygon.o: src/polygon.cpp src/polygon.h src/vector.h
	$(CXX) $(CFLAGS) -c -o $@ $< $(LIBS)
src/vector.o: src/vector.cpp src/vector.h
	$(CXX) $(CFLAGS) -c -o $@ $< $(LIBS)

	

