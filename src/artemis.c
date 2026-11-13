#include <stdio.h>
#include <stdlib.h>
#include "../include/artemis.h"
#include "../include/fisica.h"
#include "../include/validaciones.h"

// =========================================================
// PARTE 1: LOGICA DE LA MISION Y LISTA ENLAZADA
// =========================================================

void jugar_mision(NodoMision **historial)
{
    double angulo;
    int evaluacion;

    /* 1. Uso de memoria dinamica (malloc) para el nuevo nodo de la lista */
    NodoMision *nuevo_nodo = (NodoMision *)malloc(sizeof(NodoMision));
    if (nuevo_nodo == NULL) {
        printf("Error: No hay memoria suficiente para iniciar la mision.\n");
        return;
    }

    printf("\n--- SECUENCIA DE REINGRESO INICIADA ---\n");
    angulo = leer_real("Comandante, ingrese el angulo de reingreso [grados]", 0.0, 90.0);
    
    nuevo_nodo->info.angulo_ingreso = angulo;
    evaluacion = ejecutarMision(angulo, 8.0, 0.0);

    if (evaluacion == 1) {
        nuevo_nodo->info.estado_partida = 1;
    } else {
        nuevo_nodo->info.estado_partida = 2;
    }

    /* 2. Calculos fisicos apoyandose en la libreria del companero */
    nuevo_nodo->info.trabajo_roz = trabajo_rozamiento(MASA_ORION, VELOCIDAD_INICIAL, 25.0, 
                                                      ALTURA_INICIAL, 2500.0, GRAVEDAD);
    nuevo_nodo->info.desaceleracion = desaceleracion_media(VELOCIDAD_INICIAL, 25.0, 400.0);
    nuevo_nodo->info.fuerza_impacto = fuerza_amerizaje(MASA_ORION, 8.0, 1.5, GRAVEDAD);

    /* 3. Insercion al principio de la lista enlazada (actualizamos la cabeza) */
    nuevo_nodo->sig = *historial;
    *historial = nuevo_nodo;

    /* --------------------------------------------------------- */
    /* PUENTE PARA LA INTERFAZ GRAFICA                           */
    /* --------------------------------------------------------- */
    /* Formato: masa v_inicial v_final gamma profundidad v_impacto delta_t */
    FILE *archivo = fopen("datos_mision.txt", "w");
    if (archivo != NULL) {
        fprintf(archivo, "%f %f %f %f %f %f %f\n",
                (double)MASA_ORION,
                (double)VELOCIDAD_INICIAL,
                25.0,      /* v_final: apertura de paracaidas */
                angulo,
                1.5,       /* profundidad de hundimiento */
                8.0,       /* v_impacto */
                400.0);    /* delta_t de mayor desaceleracion */
        fclose(archivo);
    }
}

void liberar_historial(NodoMision **historial)
{
    NodoMision *aux;
    while (*historial != NULL) {
        aux = *historial;
        *historial = (*historial)->sig;
        free(aux);
    }
}

// =========================================================
// PARTE 2: CONTROL Y VERIFICACION DE LA MISION
// =========================================================

void iniciarMision(void) {
    printf("=== SIMULADOR ARTEMIS ===\n");
    printf("Iniciando mision...\n");
}

int verificarReingreso(double angulo) {
    if (angulo >= 5.5 && angulo <= 7.0) {
        printf("Angulo de reingreso seguro.\n");
        printf("La mision puede continuar.\n");
        return 1;
    }
    else if (angulo > 7.0) {
        printf("PELIGRO: Desaceleracion excesiva.\n");
        return 0;
    }
    else {
        printf("PELIGRO: Riesgo de rebote atmosferico.\n");
        return 0;
    }
}

void controlarDescenso(double velocidad) {
    if (velocidad >= 0 && velocidad <= 10.0) {
        printf("Descenso controlado.\n");
    }
    else {
        printf("PELIGRO: Velocidad de descenso no segura.\n");
    }
}  

void verificarAmerizaje(double velocidad, double altura) {
    if (altura <= 0 && velocidad >= 0 && velocidad <= 10.0) {
        printf("Amerizaje exitoso.\n");
        printf("Mision Artemis completada.\n");
    }
    else {
        printf("Amerizaje no confirmado.\n");
    }
}

int ejecutarMision(double angulo, double velocidad, double altura) {
    printf("\n=== CONTROL DE MISION ARTEMIS ===\n");

    printf("\nETAPA 1: REINGRESO\n");
    if (verificarReingreso(angulo) == 0) {
        printf("MISION FALLIDA: Reingreso inseguro.\n");
        return 0;
    }

    printf("\nETAPA 2: DESCENSO\n");
    controlarDescenso(velocidad);
    if (velocidad < 0 || velocidad > 10.0) {
        printf("MISION FALLIDA: Velocidad insegura.\n");
        return 0;
    }

    printf("\nETAPA 3: AMERIZAJE\n");
    if (altura <= 0) {
        verificarAmerizaje(velocidad, altura);
        printf("MISION COMPLETADA CON EXITO.\n");
        return 1;
    }

    printf("La nave todavia esta descendiendo.\n");
    return 0;
}
