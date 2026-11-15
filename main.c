
#include <stdio.h>
#include <string.h>

#include "simulador.h"
#include "validaciones.h"

static void mostrarMenu(void) {
    printf("\n========== SIMULADOR ARTEMIS - SITUACION 4 ==========\n");
    printf("1. Cargar valores originales del enunciado\n");
    printf("2. Ingresar parametros personalizados\n");
    printf("3. Calcular inciso A - Trabajo del rozamiento\n");
    printf("4. Calcular inciso B - Desaceleracion media\n");
    printf("5. Calcular inciso C - Fuerza promedio del agua\n");
    printf("6. Analizar inciso D - Angulo gamma\n");
    printf("7. Calcular todo y mostrar reporte final\n");
    printf("8. Ejecutar simulacion interactiva por eventos\n");
    printf("9. Mostrar parametros actuales\n");
    printf("10. Mostrar historial de operaciones\n");
    printf("0. Salir\n");
    printf("=====================================================\n");
}

int main(void) {
    Capsula capsula;
    Resultados resultados = {0};
    Evento eventos[MAX_EVENTOS];
    int cantidadEventos = 0;
    int opcion;
    char mensaje[180];

    cargarValoresOriginales(&capsula);
    (void)agregarEvento(eventos, &cantidadEventos,
                        "Se cargaron los valores originales del escenario.");

    do {
        mostrarMenu();

        if (!leerEnteroRango("Selecciona una opcion: ", 0, 10, &opcion)) {
            break;
        }

        switch (opcion) {
            case 1:
                cargarValoresOriginales(&capsula);
                memset(&resultados, 0, sizeof(resultados));
                (void)agregarEvento(eventos, &cantidadEventos,
                                    "Se restauraron los valores originales.");
                printf("\nValores originales cargados correctamente.\n");
                printf("Gamma inicia en 6,25 grados como valor de ejemplo.\n");
                break;

            case 2:
                if (ingresarParametrosPersonalizados(&capsula)) {
                    memset(&resultados, 0, sizeof(resultados));
                    (void)agregarEvento(eventos, &cantidadEventos,
                                        "Se ingresaron parametros personalizados.");
                } else {
                    printf("No se modificaron los parametros actuales.\n");
                }
                break;

            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                if (!validarCapsula(&capsula, mensaje, sizeof(mensaje))) {
                    printf("No se puede continuar: %s\n", mensaje);
                    break;
                }

                if (opcion == 3) {
                    calcularIncisoA(&capsula, &resultados);
                    mostrarIncisoA(&capsula, &resultados);
                    (void)agregarEvento(eventos, &cantidadEventos,
                                        "Se calculo el inciso A.");
                } else if (opcion == 4) {
                    calcularIncisoB(&capsula, &resultados);
                    mostrarIncisoB(&capsula, &resultados);
                    (void)agregarEvento(eventos, &cantidadEventos,
                                        "Se calculo el inciso B.");
                } else if (opcion == 5) {
                    calcularIncisoC(&capsula, &resultados);
                    mostrarIncisoC(&capsula, &resultados);
                    (void)agregarEvento(eventos, &cantidadEventos,
                                        "Se calculo el inciso C.");
                } else if (opcion == 6) {
                    analizarGamma(&capsula, &resultados);
                    mostrarIncisoD(&capsula, &resultados);
                    (void)agregarEvento(eventos, &cantidadEventos,
                                        "Se analizo el inciso D.");
                } else if (opcion == 7) {
                    calcularTodo(&capsula, &resultados);
                    mostrarReporte(&capsula, &resultados);
                    (void)agregarEvento(eventos, &cantidadEventos,
                                        "Se calcularon todos los incisos y se genero el reporte.");
                } else {
                    if (simularDescenso(&capsula)) {
                        (void)agregarEvento(eventos, &cantidadEventos,
                                            "Se ejecuto la simulacion interactiva por eventos.");
                    }
                }
                break;

            case 9:
                mostrarParametros(&capsula);
                break;

            case 10:
                mostrarHistorial(eventos, cantidadEventos);
                break;

            case 0:
                printf("\nFinalizando simulador. Hasta luego.\n");
                break;
        }

        if (opcion != 0) {
            pausarConsola();
        }
    } while (opcion != 0);

    return 0;
}

