# Nome do executável final
TARGET = aplicacao.exe

# Compilador
CXX = g++


# Flags de compilação (avisos, otimização, etc.)
# -Isrc/... diz ao compilador para procurar arquivos de cabeçalho dentro das pastas do src
CXXFLAGS = -Wall -Wextra -g -Isrc/core -Isrc/lightning -Isrc/objects -Isrc/controls -Isrc/textures
# Flags de linkagem (bibliotecas a serem usadas)
LDFLAGS = -mconsole -lfreeglut -lopengl32 -lglu32



# Lista manual dos arquivos .cpp
SRCS = src/main.cpp \
	   src/core/controls/controls.cpp \
	   src/core/lightning/lights.cpp \
	   src/scene/objects/objects.cpp \
	   src/scene/animations/animations.cpp \
	   src/scene/textures/textures.cpp
OBJECTS = src/obj/main.o \
		  src/obj/controls.o \
		  src/obj/lights.o \
		  src/obj/objects.o \
		  src/obj/animations.o \
		  src/obj/textures.o

# --- REGRAS DO MAKEFILE ---

# Ela depende de que o executável (TARGET) seja construído.
all: $(TARGET)

# Regra para construir o executável final (TARGET)
# Depende de todos os arquivos objeto (OBJECTS).
# O comando de linkagem junta todos os objetos para criar o executável.
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)


# Regra genérica para compilar qualquer .cpp listado em SRCS

# Regras para compilar cada objeto na raiz de src/
src/obj/main.o: src/main.cpp src/core/state.h src/core/controls/controls.h src/core/lightning/lights.h src/scene/objects/objects.h src/scene/animations/animations.h src/scene/textures/textures.h | src/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/obj/controls.o: src/core/controls/controls.cpp src/core/controls/controls.h src/core/state.h | src/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/obj/lights.o: src/core/lightning/lights.cpp src/core/lightning/lights.h src/core/state.h | src/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/obj/objects.o: src/scene/objects/objects.cpp src/scene/objects/objects.h src/core/state.h src/scene/animations/animations.h src/scene/textures/textures.h | src/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/obj/animations.o: src/scene/animations/animations.cpp src/scene/animations/animations.h src/core/state.h | src/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/obj/textures.o: src/scene/textures/textures.cpp src/scene/textures/textures.h src/core/state.h | src/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/obj:
	mkdir -p src/obj

clean:
	del /Q /S src\*.o $(TARGET)

.PHONY: all clean