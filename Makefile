# Makefile - Simulador Artemis (Grupo 14)
# Uso:  make                   -> programa principal por consola (./artemis)
#       make grafica           -> ventana de telemetria con raylib (opcional)
#       make test              -> pruebas de fisica
#       make test_validaciones -> pruebas de entradas
#       make clean             -> borra objetos y ejecutables

CC     = gcc
CFLAGS = -Wall -Iinclude
LIBS   = -lm

# interfaz_grafica.c tiene su propio main y necesita raylib: no va en el programa principal
FUENTES = $(filter-out src/interfaz_grafica.c,$(wildcard src/*.c))
OBJETOS = $(FUENTES:.c=.o)

# En Windows se agrega el icono del ejecutable
ifeq ($(OS),Windows_NT)
EXTRA = icono.o
RAYLIB = -lraylib -lopengl32 -lgdi32 -lwinmm
icono.o: icono.rc icono.ico
	windres icono.rc -o icono.o
else
EXTRA =
RAYLIB = -lraylib -lGL -lpthread -ldl
endif

artemis: $(OBJETOS) $(EXTRA)
	$(CC) $(OBJETOS) $(EXTRA) -o artemis $(LIBS)

# Regla para compilar cada .c en un .o (compilacion separada)
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Ventana grafica (requiere raylib instalada)
grafica: src/interfaz_grafica.c src/fisica.c
	$(CC) $(CFLAGS) src/interfaz_grafica.c src/fisica.c -o interfaz_grafica $(RAYLIB) $(LIBS)

# Pruebas (cada una tiene su propio main)
test: tests/test_fisica.c src/fisica.c
	$(CC) $(CFLAGS) tests/test_fisica.c src/fisica.c -o test_fisica $(LIBS)

test_validaciones: tests/test_validaciones.c src/validaciones.c
	$(CC) $(CFLAGS) tests/test_validaciones.c src/validaciones.c -o test_validaciones $(LIBS)

clean:
	rm -f src/*.o *.o artemis artemis.exe interfaz_grafica interfaz_grafica.exe test_fisica test_fisica.exe test_validaciones test_validaciones.exe datos_mision.txt

.PHONY: grafica test test_validaciones clean
