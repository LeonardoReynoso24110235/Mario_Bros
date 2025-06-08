# Makefile para compilar el juego completo y generar el ejecutable en la carpeta bin

# Compilador
CXX = g++

# Directorios
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

# Archivos fuente y objeto
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Nombre del ejecutable
EXECUTABLE = $(BIN_DIR)/mario_bros

# Flags de compilación
CXXFLAGS = -I$(INCLUDE_DIR) -std=c++17 -Wall -Wextra \
  -IC:/msys64/ucrt64/include -IC:/msys64/ucrt64/include/SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d \
  -LC:/msys64/ucrt64/lib

# Regla principal
all: $(EXECUTABLE)

# Regla para compilar el ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Regla para compilar archivos objeto
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Agregar la regla `run` para ejecutar el programa
run: all
	./$(EXECUTABLE)

# Regla combinada para compilar y ejecutar
make_run: all run

# Limpiar archivos generados
clean:
	rm -rf $(BIN_DIR)/*.o $(EXECUTABLE)

.PHONY: all clean