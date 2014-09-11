##
# Makefile 
# Author: Mario Román
# From: https://github.com/M42/mp-tsp/blob/master/makefile
##

# Directory macros.
INCLUDE=./include
OBJ=./obj
SRC=./src
DOC=./doc
BIN=./bin

# Executable and object files macros.
EXECUTABLE= $(BIN)/granasatClient
EXECUTABLE2= $(BIN)/imageConvert
HEADERS= $(wildcard $(INCLUDE)/*.h)
SOURCES= $(filter-out $(SRC)/imageconvert.c, $(wildcard $(SRC)/*.c))
OBJECTS= $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

# Compiling and linking flags.
CC=gcc
INCLUDES=-I./include -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/cairo
FLAGS=-O0 -g3 -Wall -fmessage-length=0 `pkg-config --cflags --libs gtk+-3.0 opencv` -export-dynamic





# Executables are the main objetive.
all: $(EXECUTABLE) $(EXECUTABLE2)

# Linking and compiling.
$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(INCLUDES) $(FLAGS)

$(EXECUTABLE2): $(SRC)/imageconvert.c
	$(CC) -o $@ $(SRC)/imageconvert.c $(FLAGS)

# Compiling.
$(OBJ)/%.o: $(SRC)/%.c $(HEADERS)
	$(CC) -o $@ $(INCLUDES) -c $< $(FLAGS)




# Cleaning.
clean:
	@rm $(OBJ)/*.o && echo "Borrados ficheros objeto."
	@rm $(EXECUTABLE) && echo "Borrado ejecutable."
	@rm $(EXECUTABLE2) && echo "Borrado ejecutable 2."
doc:
	doxygen doxyfile

.PHONY: clean doc
