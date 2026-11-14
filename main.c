
#include <stdio.h>
#include <stdlib.h>
#include "simulador.h"
#include "validaciones.h"

/* Muestra las opciones disponibles */
void mostrarMenu(void) {
    printf("\n=================================\n");
    printf("       SIMULADOR DE FISICA\n");
    printf("=================================\n");
    printf("1. Cargar valores originales\n");
    printf("2. Resolver inciso A\n");
    printf("3. Resolver inciso B\n");
    printf("4. Resolver inciso C\n");
    printf("5. Resolver inciso D\n");
    printf("6. Mostrar resultados\n");
    printf("7. Simulacion interactiva\n");
    printf("8. Ver historial\n");
    printf("0. Salir\n");
    printf("=================================\n");
    printf("Seleccione una opcion: ");
}

/* Lee una opcion numerica de forma segura */
int leerOpcion(void) {
    char entrada[100];
    char *fin;
    long opcion;

    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return 0;
    }

    opcion = strtol(entrada, &fin, 10);

    if (fin == entrada) {
        return -1;
    }

    while (*fin == ' ' || *fin == '\t') {
        fin++;
    }

    if (*fin != '\n' && *fin != '\0') {
        return -1;
    }

    if (opcion < 0 || opcion > 8) {
        return -1;
    }

    return (int)opcion;
}

int main(void) {
    int opcion;

    printf("Bienvenido al Simulador de Fisica\n");

    do {
        mostrarMenu();
        opcion = leerOpcion();

        switch (opcion) {
            case 1:
                printf("\nCargar valores originales\n");
                /* Conectar funcion de simulador.c */
                break;

            case 2:
                printf("\nResolviendo inciso A...\n");
                /* Conectar funcion del inciso A */
                break;

            case 3:
                printf("\nResolviendo inciso B...\n");
                /* Conectar funcion del inciso B */
                break;

            case 4:
                printf("\nResolviendo inciso C...\n");
                /* Conectar funcion del inciso C */
                break;

            case 5:
                printf("\nResolviendo inciso D...\n");
                /* Conectar funcion del inciso D */
                break;

            case 6:
                printf("\nMostrando resultados...\n");
                /* Conectar funcion de reportes */
                break;

            case 7:
                printf("\nSimulacion interactiva...\n");
                /* Conectar funcion de simulacion */
                break;

            case 8:
                printf("\nHistorial de operaciones...\n");
                /* Conectar funcion de historial */
                break;

            case 0:
                printf("\nGracias por utilizar el simulador.\n");
                break;

            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
                break;
        }

    } while (opcion != 0);

    return 0;
}
