CC=g++
DEPENDS= ~/Code/3D/engine/include
CFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -I $(DEPENDS) -Wall -Wextra 

.PHONY: all clean install uninstall 

all: engine

engine: main.o vector.o polygon.o object.o parser.o mesh.o render.o
	$(CC) $(CFLAGS) main.o vector.o polygon.o object.o parser.o mesh.o render.o -o engine 

main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

vector.o: src/geometry/vector.cpp
	$(CC) $(CFLAGS) -c src/geometry/vector.cpp 

polygon.o: src/geometry/polygon.cpp
	$(CC) $(CFLAGS) -c src/geometry/polygon.cpp 

object.o: src/object.cpp
	$(CC) $(CFLAGS) -c src/object.cpp

parser.o: src/parser.cpp
	$(CC) $(CFLAGS) -c src/parser.cpp

mesh.o: src/geometry/mesh.cpp
	$(CC) $(CFLAGS) -c src/geometry/mesh.cpp

render.o: src/render/render.cpp
	$(CC) $(CFLAGS) -c src/render/render.cpp

clean: 
	rm -rf *.o 
