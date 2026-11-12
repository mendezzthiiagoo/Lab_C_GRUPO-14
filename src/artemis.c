#include <stdio.h>

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
    if (velocidad > 0 && velocidad <= 10.0) {
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
