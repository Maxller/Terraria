# Nombre del ejecutable
TARGET = bin/Terraria

# Compilador
CC = g++

# Directorios
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Flags
CFLAGS = -I$(INCDIR) -Wall -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

# Archivos de fuente y objetos
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

# Regla para el ejecutable
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $(TARGET))
	$(CC) -o $@ $^ $(LDFLAGS)

# Regla para los archivos objetos
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Regla para limpiar los archivos compilados
clean:
	rm -rf $(BUILDDIR) $(TARGET)

runa: clean run

.PHONY: clean run