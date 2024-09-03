# Nombre del ejecutable
TARGET = Cat-Tastrofe

# Compilador
CXX = g++

# Flags de compilación
CXXFLAGS = -std=c++17 -Wall -Wextra -Ilib/include

# Librerías necesarias
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Directorios de código fuente y de cabeceras
SRC_DIR = lib/src
INCLUDE_DIR = lib/include
MAIN_DIR = main
OBJ_DIR = obj

# Archivos fuente
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
MAIN_FILES = $(wildcard $(MAIN_DIR)/*.cpp)

# Archivos objeto (se generan en el directorio obj/)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) \
            $(MAIN_FILES:$(MAIN_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regla por defecto
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Regla para compilar archivos .cpp a .o, y colocar .o en el directorio obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MAIN_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear el directorio obj si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpiar archivos generados
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
