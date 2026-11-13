#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <stddef.h>

#define G_TERRESTRE 9.8
#define GAMMA_MIN 5.5
#define GAMMA_MAX 7.0
#define MAX_EVENTOS 100
#define CANT_ETAPAS 5

typedef struct {
    double masa;
    double velocidadInicial;
    double alturaInicial;
    double velocidadParacaidas;
    double alturaParacaidas;
    double tiempoFrenado;
    double velocidadImpacto;
    double distanciaHundimiento;
    double gamma;
} Capsula;

typedef struct {
    double energia[3]; /* Inicial, apertura de paracaidas e impacto */
    double trabajoRozamiento;
    double aceleracionMedia;
    double desaceleracionG;
    double peso;
    double fuerzaAgua;
    double vecesPeso;
    int calculoA;
    int calculoB;
    int calculoC;
    int calculoD;
    int estadoGamma; /* 0: sin analizar, 1: seguro, 2: mayor, 3: menor */
} Resultados;

typedef struct {
    int numero;
    char descripcion[120];
} Evento;

/* Carga, configuracion y validacion */
void cargarValoresOriginales(Capsula *capsula);
int validarCapsula(const Capsula *capsula, char *mensaje, size_t tamMensaje);
int ingresarParametrosPersonalizados(Capsula *capsula);

/* Calculos fisicos */
void calcularIncisoA(const Capsula *capsula, Resultados *resultados);
void calcularIncisoB(const Capsula *capsula, Resultados *resultados);
void calcularIncisoC(const Capsula *capsula, Resultados *resultados);
void analizarGamma(const Capsula *capsula, Resultados *resultados);
void calcularTodo(const Capsula *capsula, Resultados *resultados);

/* Presentacion de datos y reportes */
void mostrarParametros(const Capsula *capsula);
void mostrarIncisoA(const Capsula *capsula, const Resultados *resultados);
void mostrarIncisoB(const Capsula *capsula, const Resultados *resultados);
void mostrarIncisoC(const Capsula *capsula, const Resultados *resultados);
void mostrarIncisoD(const Capsula *capsula, const Resultados *resultados);
void mostrarReporte(const Capsula *capsula, const Resultados *resultados);

/* Simulacion interactiva e historial */
int simularDescenso(const Capsula *capsula);
int agregarEvento(Evento eventos[], int *cantidad, const char *descripcion);
void mostrarHistorial(const Evento eventos[], int cantidad);

#endif
