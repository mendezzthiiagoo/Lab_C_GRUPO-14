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

    // Etapa 1: verificar el reingreso
    printf("\nETAPA 1: REINGRESO\n");

    if (verificarReingreso(angulo) == 0) {
        printf("MISION FALLIDA: Reingreso inseguro.\n");
        return 0;
    }

    // Etapa 2: controlar el descenso
    printf("\nETAPA 2: DESCENSO\n");

    controlarDescenso(velocidad);

    if (velocidad < 0 || velocidad > 10.0) {
        printf("MISION FALLIDA: Velocidad insegura.\n");
        return 0;
    }

    // Etapa 3: verificar el amerizaje
    printf("\nETAPA 3: AMERIZAJE\n");

    if (altura <= 0) {
        verificarAmerizaje(velocidad, altura);
        printf("MISION COMPLETADA CON EXITO.\n");
        return 1;
    }

    printf("La nave todavia esta descendiendo.\n");
    return 0;
}

