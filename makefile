##
# Makefile 
# Author: Mario Román
# From: https://github.com/M42/mp-tsp/blob/master/makefile
##

# Macros para identificar los directorios.
INCLUDE=./include
OBJ=./obj
SRC=./src
DOC=./doc
BIN=./bin

# Macros para identificar el ejecutable y los archivos objeto.
EXECUTABLE= $(BIN)/granasatClient
EXECUTABLE2= $(BIN)/imageConvert
HEADERS= $(wildcard $(INCLUDE)/*.h)
SOURCES= $(filter-out $(SRC)/imageconvert.c, $(wildcard $(SRC)/*.c))
OBJECTS= $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

# Flags usados al compilar y enlazar
CC=gcc
INCLUDES=-I./include -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/cairo
FLAGS=-O0 -g3 -Wall -fmessage-length=0 `pkg-config --cflags --libs gtk+-3.0 opencv` -export-dynamic





# El objetivo global es el ejecutable.
all: $(EXECUTABLE) $(EXECUTABLE2)

# Generación del ejecutable a partir de ficheros objeto.
$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(INCLUDES) $(FLAGS)

$(EXECUTABLE2): $(SRC)/imageconvert.c
	$(CC) -o $@ $(SRC)/imageconvert.c $(FLAGS)

# Generación de ficheros objeto.
$(OBJ)/%.o: $(SRC)/%.c $(HEADERS)
	$(CC) -o $@ $(INCLUDES) -c $< $(FLAGS)




# Falsos objetivos para limpieza, documentación y generacion HTML.
clean:
	@rm $(OBJ)/*.o && echo "Borrados ficheros objeto."
	@rm $(EXECUTABLE) && echo "Borrado ejecutable."

.PHONY: clean documentacion tabla
