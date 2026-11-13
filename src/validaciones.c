#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/validaciones.h"

static void leer_linea(char *linea, int tamanio)
{
    int c;

    if (fgets(linea, tamanio, stdin) == NULL) {
        printf("\nEntrada finalizada.\n");
        exit(EXIT_SUCCESS);
    }

    /* Descarta lo que no entro en el buffer */
    if (linea[0] != '\0') {
        int i = 0;
        while (linea[i] != '\0' && linea[i] != '\n') {
            i++;
        }
        if (linea[i] != '\n') {
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            linea[0] = '\0';
        }
    }
}

int leer_entero(const char *mensaje, int minimo, int maximo)
{
    char linea[256];
    char extra;
    int valor;

    while (1) {
        printf("%s [%d a %d]: ", mensaje, minimo, maximo);
        leer_linea(linea, sizeof(linea));

        if (sscanf(linea, "%d %c", &valor, &extra) == 1 &&
            valor >= minimo && valor <= maximo) {
            return valor;
        }

        printf("Entrada invalida. Intente nuevamente.\n");
    }
}

double leer_real(const char *mensaje, double minimo, double maximo)
{
    char linea[256];
    char extra;
    double valor;

    while (1) {
        printf("%s [%.2f a %.2f]: ", mensaje, minimo, maximo);
        leer_linea(linea, sizeof(linea));

        if (sscanf(linea, "%lf %c", &valor, &extra) == 1 &&
            isfinite(valor) && valor >= minimo && valor <= maximo) {
            return valor;
        }

        printf("Entrada invalida. Use punto para los decimales.\n");
    }
}

void esperar_enter(void)
{
    char linea[256];

    printf("\nPresione Enter para continuar...");
    leer_linea(linea, sizeof(linea));
}
