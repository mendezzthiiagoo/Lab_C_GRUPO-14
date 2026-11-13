#include <stdio.h>
#include <stdlib.h> /* system() */
#include "../include/artemis.h"
#include "../include/calculadora.h"
#include "../include/validaciones.h"

int main(void)
{
    /* Inicializamos la cabeza de la lista enlazada en NULL */
    NodoMision *historial = NULL; 
    int opcion;
    int ventana_abierta = 0;   /* 1 = ya se lanzo la ventana grafica */

    do {
        printf("\n+==================================================+\n");
        printf("|        ARTEMIS - REINGRESO Y AMERIZAJE           |\n");
        printf("+==================================================+\n");
        printf(" 1. Iniciar mision\n");
        printf(" 2. Calculadora de analisis\n");
        printf(" 3. Reglas del juego\n");
        printf(" 4. Ver historial de misiones\n");
        printf(" 0. Salir\n");
        opcion = leer_entero("Elija una opcion", 0, 4);

        switch (opcion) {
        case 1:
            /* La ventana grafica es opcional: se abre una sola vez, y solo si
               existe interfaz_grafica.exe (en Windows). Sin ella el juego sigue igual. */
            if (!ventana_abierta) {
                FILE *prueba = fopen("interfaz_grafica.exe", "rb");
                if (prueba != NULL) {
                    fclose(prueba);
                    system("start interfaz_grafica.exe");
                    ventana_abierta = 1;
                }
            }

            /* Pasamos la direccion de memoria del puntero para modificar la lista */
            jugar_mision(&historial); 
            break;
        case 2:
            ejecutar_calculadora();
            break;
        case 3:
            mostrar_reglas();
            esperar_enter();
            break;
        case 4:
            /* Pasamos el puntero por valor porque aca solo queremos leer/imprimir */
            mostrar_reporte(historial); 
            esperar_enter();
            break;
        case 0:
            printf("\nHasta la proxima, comandante.\n");
            break;
        }
    } while (opcion != 0);

    /* MUY IMPORTANTE EN AED: Liberar la memoria dinamica antes del return */
    liberar_historial(&historial);

    return 0;
}
