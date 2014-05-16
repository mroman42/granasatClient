SRC=./src
INCLUDES=-I./include -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/cairo
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp, %.out, $(SOURCES))
FLAGS=-O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags --libs gtk+-2.0`

EXE=./bin/granasatClient


all: $(EXE)

$(EXE): $(SRC)/main.c $(OBJECTS)
	gcc $< -o $@ $(INCLUDES) $(FLAGS)

clean:
	rm -f $(EXE) 
