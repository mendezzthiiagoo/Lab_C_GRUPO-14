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
