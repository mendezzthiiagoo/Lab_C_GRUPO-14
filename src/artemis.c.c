#include <stdio.h>
#include <stdlib.h>
#include "../include/artemis.h"
#include "../include/fisica.h"
#include "../include/validaciones.h"



void jugar_mision(NodoMision **historial)
{
    double angulo;
    int evaluacion;

    /* 1. Uso de memoria dinámica (malloc) para el nuevo nodo de la lista */
    NodoMision *nuevo_nodo = (NodoMision *)malloc(sizeof(NodoMision));
    if (nuevo_nodo == NULL) {
        printf("Error: No hay memoria suficiente para iniciar la mision.\n");
        return;
    }

    printf("\n--- SECUENCIA DE REINGRESO INICIADA ---\n");
    angulo = leer_real("Comandante, ingrese el angulo de reingreso [grados]", 0.0, 90.0);
    
    nuevo_nodo->info.angulo_ingreso = angulo;
    evaluacion = evaluar_angulo(angulo);

    if (evaluacion == 1) {
        printf("\n[EXITO] Angulo nominal. La capsula penetra la atmosfera de forma segura.\n");
        printf("Paracaidas desplegados. Amerizaje confirmado.\n");
        nuevo_nodo->info.estado_partida = 1;
    } else if (evaluacion == 0) {
        printf("\n[FRACASO] Angulo muy rasante. La capsula reboto en la alta atmosfera.\n");
        printf("Se perdio el contacto. La mision ha fallado.\n");
        nuevo_nodo->info.estado_partida = 2;
    } else {
        printf("\n[FRACASO] Angulo muy empinado. Desaceleracion brutal y escudos superados.\n");
        printf("La capsula se desintegro por el calor.\n");
        nuevo_nodo->info.estado_partida = 2;
    }

    /* 2. Cálculos físicos apoyándose en la librería del compañero */
    nuevo_nodo->info.trabajo_roz = trabajo_rozamiento(MASA_ORION, VELOCIDAD_INICIAL, 25.0, 
                                                      ALTURA_INICIAL, 2500.0, GRAVEDAD);
    nuevo_nodo->info.desaceleracion = desaceleracion_media(VELOCIDAD_INICIAL, 25.0, 400.0);
    nuevo_nodo->info.fuerza_impacto = fuerza_amerizaje(MASA_ORION, 8.0, 1.5, GRAVEDAD);

    /* 3. Inserción al principio de la lista enlazada (actualizamos la cabeza) */
    nuevo_nodo->sig = *historial;
    *historial = nuevo_nodo;
}

void liberar_historial(NodoMision **historial)
{
    NodoMision *aux;
    /* Liberamos la memoria dinámica (free) para no dejar memory leaks */
    while (*historial != NULL) {
        aux = *historial;
        *historial = (*historial)->sig;
        free(aux);
    }
}
