################################################################################
## Declaracion de variables del fichero «Makefile»

## DIRECTORIOS
SOURCE_PB1_DIR = pb1-combinar-ficheros
SOURCE_PB2_DIR = pb2-mayor-sismicidad
BUILD_DIR = build
BIN_DIR = bin

VPATH = $(SOURCE_PB1_DIR) $(SOURCE_PB2_DIR) 

## COMPILADOR Y OPCIONES DE COMPILACIÓN:
CXX = g++
CXXFLAGS = -g -Wall -Wextra -I.


## FICHEROS OBJETO (RESULTADOS INTERMEDIOS DE COMPILACIÓN):
OBJECTS_PB1 = $(addprefix $(BUILD_DIR)/, obtenerUltimoCodigo.o pb1-main.o)
OBJECTS_PB2 = $(BUILD_DIR)/pb2-main.o

################################################################################
## Reglas del fichero «Makefile»

pb1: $(OBJECTS_PB1) | $(BIN_DIR)  
	$(CXX) -g $^ -o $(BIN_DIR)/$@ 

pb2: $(OBJECTS_PB2) | $(BIN_DIR)
	$(CXX) -g $^ -o $(BIN_DIR)/$@ 

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@  

$(BUILD_DIR)/obtenerUltimoCodigo.o: constantes.hpp
$(BUILD_DIR)/pb1-main.o: constantes.hpp obtenerUltimoCodigo.hpp
$(BUILD_DIR)/pb2-main.o: constantes.hpp

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
ifeq ($(OS),Windows_NT)
	if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)
	if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
else
	rm -f $(OBJECTS_PB1) $(OBJECTS_PB2) $(BIN_DIR)/*
endif

