# Nome do executável final
TARGET = aplicacao.exe

# Compilador
CXX = g++

# Flags de compilação (avisos, otimização, etc.)
# -Isrc/... diz ao compilador para procurar arquivos de cabeçalho dentro das pastas do src
CXXFLAGS = -Wall -Wextra -g -Isrc/core -Isrc/lightning -Isrc/objects -Isrc/controls -Isrc/textures

# Flags de linkagem (bibliotecas a serem usadas)
LDFLAGS = -lfreeglut -lopengl32 -lglu32

# Encontra automaticamente todos os arquivos .cpp dentro da pasta src e suas subpastas
SOURCES = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
# Converte a lista de fontes .cpp em uma lista de arquivos objeto .o
OBJECTS = $(SOURCES:.cpp=.o)

# --- REGRAS DO MAKEFILE ---

# Ela depende de que o executável (TARGET) seja construído.
all: $(TARGET)

# Regra para construir o executável final (TARGET)
# Depende de todos os arquivos objeto (OBJECTS).
# O comando de linkagem junta todos os objetos para criar o executável.
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q /S src\*.o $(TARGET)

.PHONY: all clean