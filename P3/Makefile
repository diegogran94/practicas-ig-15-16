# fichero Makefile

SRC = src
OBJ = obj
#LIB = lib
BIN = bin
INCLUDE = include

# nombre del fichero ejecutable
#
TARGETS= main

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE)
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE)

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut

# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
default: $(BIN)/$(TARGETS) 

# regla de ejecucion
#
$(BIN)/main: $(OBJ)/main.o $(OBJ)/Objeto3d.o $(OBJ)/file_ply_stl.o $(OBJ)/figuras.o $(OBJ)/objetos.o
	$(CC) -o $@ $(CXXFLAGS) $(OBJ)/main.o $(OBJ)/Objeto3d.o $(OBJ)/file_ply_stl.o $(OBJ)/figuras.o $(OBJ)/objetos.o $(LDFLAGS)

$(OBJ)/main.o: $(SRC)/main.cc $(INCLUDE)/Objeto3d.h $(INCLUDE)/vertex.h $(INCLUDE)/figuras.h $(INCLUDE)/objetos.h
	$(CC) -c -o $@ $(CXXFLAGS) $(SRC)/main.cc $(LDFLAGS)

$(OBJ)/Objeto3d.o: $(SRC)/Objeto3d.cc $(INCLUDE)/Objeto3d.h $(INCLUDE)/file_ply_stl.h
	$(CC) -c -o $@ $(CXXFLAGS) $(SRC)/Objeto3d.cc $(LDFLAGS)

$(OBJ)/file_ply_stl.o: $(SRC)/file_ply_stl.cc $(INCLUDE)/file_ply_stl.h $(INCLUDE)/vertex.h 
	$(CC) -c -o $@ $(CXXFLAGS) $(SRC)/file_ply_stl.cc $(LDFLAGS)

$(OBJ)/figuras.o: $(SRC)/figuras.cc $(INCLUDE)/figuras.h $(INCLUDE)/vertex.h $(INCLUDE)/Objeto3d.h
	$(CC) -c -o $@ $(CXXFLAGS) $(SRC)/figuras.cc $(LDFLAGS)

$(OBJ)/objetos.o: $(SRC)/objetos.cc $(INCLUDE)/objetos.h $(INCLUDE)/vertex.h $(INCLUDE)/Objeto3d.h $(INCLUDE)/figuras.h
	$(CC) -c -o $@ $(CXXFLAGS) $(SRC)/objetos.cc $(LDFLAGS)
#
#
clean:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/$(TARGETS)

#
#
redo:
	touch $(SRC)/*.cc
	make

#
#
superclean:
	rm -f $(OBJ)/*.o
	#rm $(SRC)/*~
	rm -f $(BIN)/$(TARGETS)

#
#
tgz:
	rm -f $(OBJ)/*.o
	#rm $(SRC)/*~
	rm -f $(BIN)/$(TARGETS)
	tar -zcvf $(TARGETS).tgz *

