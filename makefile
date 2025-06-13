# Directorios de origen y destino
SRC_DIR := src
BIN_DIR := bin
INCLUDE_DIR := include

# Bibliotecas de SFML y Box2D
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

# Archivos fuente
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Archivos objeto
OBJ_FILES := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Archivo ejecutable principal
TARGET := $(BIN_DIR)/main.exe

# Regla por defecto
all: $(TARGET)

# Compilar todos los archivos fuente en archivos objeto
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -c $< -o $@ -I$(INCLUDE_DIR)

# Crear el ejecutable final a partir de los archivos objeto
$(TARGET): $(OBJ_FILES)
	g++ $^ -o $@ $(SFML)

# Ejecutar el programa principal
run: $(TARGET)
	./$(BIN_DIR)/main.exe

# Limpiar los archivos generados
clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/main.exe

.PHONY: all clean run