
# Compilador
CC = gcc

# Opciones de compilacion
CFLAGS = -Wall -Wextra -std=c11

# Nombre del ejecutable
TARGET = simulador

# Archivos fuente
SRC = main.c simulador.c validaciones.c

# Archivos objeto
OBJ = $(SRC:.c=.o)

# Compilacion principal
all: $(TARGET)

# Enlazar archivos objeto
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compilar cada archivo fuente
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Eliminar archivos generados
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all run clean
