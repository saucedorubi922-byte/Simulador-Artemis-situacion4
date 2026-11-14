#include <stdio.h>
#include <string.h>
#include <math.h>

#include "simulador.h"
#include "validaciones.h"

void cargarValoresOriginales(Capsula *capsula) {
    if (capsula == NULL) {
        return;
    }

    capsula->masa = 10400.0;
    capsula->velocidadInicial = 11000.0;
    capsula->alturaInicial = 120000.0;
    capsula->velocidadParacaidas = 25.0;
    capsula->alturaParacaidas = 2500.0;
    capsula->tiempoFrenado = 400.0;
    capsula->velocidadImpacto = 8.0;
    capsula->distanciaHundimiento = 1.50;

    /* El enunciado no fija gamma: 6,25 grados es solo un ejemplo. */
    capsula->gamma = 6.25;
}

int validarCapsula(const Capsula *c, char *mensaje, size_t tamMensaje) {
    if (c == NULL || mensaje == NULL || tamMensaje == 0) {
        return 0;
    }

    if (!isfinite(c->masa) || !isfinite(c->velocidadInicial) ||
        !isfinite(c->alturaInicial) || !isfinite(c->velocidadParacaidas) ||
        !isfinite(c->alturaParacaidas) || !isfinite(c->tiempoFrenado) ||
        !isfinite(c->velocidadImpacto) || !isfinite(c->distanciaHundimiento) ||
        !isfinite(c->gamma)) {
        snprintf(mensaje, tamMensaje, "Todos los parametros deben ser numeros finitos.");
        return 0;
    }

    if (c->masa <= 0.0 ||
        c->velocidadInicial < 0.0 ||
        c->velocidadParacaidas < 0.0 ||
        c->velocidadImpacto < 0.0 ||
        c->alturaParacaidas < 0.0 ||
        c->alturaInicial <= c->alturaParacaidas ||
        c->tiempoFrenado <= 0.0 ||
        c->distanciaHundimiento <= 0.0 ||
        c->gamma < 0.0 || c->gamma > 90.0) {
        snprintf(mensaje, tamMensaje, "Hay parametros fuera de rango o incompatibles.");
        return 0;
    }

    if (c->velocidadInicial < c->velocidadParacaidas) {
        snprintf(mensaje, tamMensaje,
                 "La velocidad inicial debe ser mayor o igual que la velocidad al abrir los paracaidas.");
        return 0;
    }

    snprintf(mensaje, tamMensaje, "Parametros validos.");
    return 1;
}

int ingresarParametrosPersonalizados(Capsula *capsula) {
    Capsula temporal;
    char mensaje[180];

    if (capsula == NULL) {
        return 0;
    }

    for (;;) {
        printf("\n--- INGRESO DE PARAMETROS PERSONALIZADOS ---\n");

        if (!leerDoubleRango("Masa (kg): ", 0.001, 1e9, &temporal.masa) ||
            !leerDoubleRango("Velocidad inicial (m/s): ", 0.0, 1e7, &temporal.velocidadInicial) ||
            !leerDoubleRango("Altura inicial (m): ", 0.001, 1e8, &temporal.alturaInicial) ||
            !leerDoubleRango("Velocidad al abrir paracaidas (m/s): ", 0.0, 1e6, &temporal.velocidadParacaidas) ||
            !leerDoubleRango("Altura al abrir paracaidas (m): ", 0.0, 1e7, &temporal.alturaParacaidas) ||
            !leerDoubleRango("Tiempo de frenado (s): ", 0.001, 1e7, &temporal.tiempoFrenado) ||
            !leerDoubleRango("Velocidad de impacto (m/s): ", 0.0, 1e6, &temporal.velocidadImpacto) ||
            !leerDoubleRango("Distancia de hundimiento (m): ", 0.001, 1e6, &temporal.distanciaHundimiento) ||
            !leerDoubleRango("Angulo gamma (grados, 0 a 90): ", 0.0, 90.0, &temporal.gamma)) {
            return 0;
        }

        if (validarCapsula(&temporal, mensaje, sizeof(mensaje))) {
            *capsula = temporal;
            printf("%s\n", mensaje);
            return 1;
        }

        printf("\nError: %s\n", mensaje);
        printf("Volvamos a ingresar todos los parametros.\n");
    }
}

void calcularIncisoA(const Capsula *c, Resultados *r) {
    if (c == NULL || r == NULL) {
        return;
    }

    r->energia[0] = 0.5 * c->masa * c->velocidadInicial * c->velocidadInicial;
    r->energia[1] = 0.5 * c->masa * c->velocidadParacaidas * c->velocidadParacaidas;

    /*
     * Teorema trabajo-energia:
     * Wroz + Wgravedad = Kf - Ki
     * Wgravedad = m*g*(hi-hf)
     * Wroz = (Kf-Ki) - m*g*(hi-hf)
     */
    r->trabajoRozamiento =
        (r->energia[1] - r->energia[0]) -
        c->masa * G_TERRESTRE * (c->alturaInicial - c->alturaParacaidas);

    r->calculoA = 1;
}

void calcularIncisoB(const Capsula *c, Resultados *r) {
    double magnitud;

    if (c == NULL || r == NULL) {
        return;
    }

    r->aceleracionMedia =
        (c->velocidadParacaidas - c->velocidadInicial) / c->tiempoFrenado;

    magnitud = fabs(r->aceleracionMedia);
    r->desaceleracionG = magnitud / G_TERRESTRE;
    r->calculoB = 1;
}

void calcularIncisoC(const Capsula *c, Resultados *r) {
    if (c == NULL || r == NULL) {
        return;
    }

    r->peso = c->masa * G_TERRESTRE;
    r->energia[2] = 0.5 * c->masa * c->velocidadImpacto * c->velocidadImpacto;

    /*
     * Eje positivo hacia abajo:
     * (Peso - FuerzaAgua)*d = -Ki
     * FuerzaAgua = Peso + Ki/d
     */
    r->fuerzaAgua = r->peso + r->energia[2] / c->distanciaHundimiento;
    r->vecesPeso = r->fuerzaAgua / r->peso;
    r->calculoC = 1;
}

void analizarGamma(const Capsula *c, Resultados *r) {
    if (c == NULL || r == NULL) {
        return;
    }

    if (c->gamma >= GAMMA_MIN && c->gamma <= GAMMA_MAX) {
        r->estadoGamma = 1;
    } else if (c->gamma > GAMMA_MAX) {
        r->estadoGamma = 2;
    } else {
        r->estadoGamma = 3;
    }

    r->calculoD = 1;
}

void calcularTodo(const Capsula *c, Resultados *r) {
    if (c == NULL || r == NULL) {
        return;
    }

    calcularIncisoA(c, r);
    calcularIncisoB(c, r);
    calcularIncisoC(c, r);
    analizarGamma(c, r);
}

void mostrarParametros(const Capsula *c) {
    if (c == NULL) {
        return;
    }

    printf("\n--- PARAMETROS DE LA CAPSULA ORION ---\n");
    printf("Masa: %.2f kg\n", c->masa);
    printf("Velocidad inicial: %.2f m/s\n", c->velocidadInicial);
    printf("Altura inicial: %.2f m\n", c->alturaInicial);
    printf("Velocidad al desplegar paracaidas: %.2f m/s\n", c->velocidadParacaidas);
    printf("Altura al desplegar paracaidas: %.2f m\n", c->alturaParacaidas);
    printf("Tiempo de frenado: %.2f s\n", c->tiempoFrenado);
    printf("Velocidad de impacto: %.2f m/s\n", c->velocidadImpacto);
    printf("Distancia de hundimiento: %.2f m\n", c->distanciaHundimiento);
    printf("Angulo gamma: %.2f grados (valor configurable)\n", c->gamma);
}

void mostrarIncisoA(const Capsula *c, const Resultados *r) {
    if (r == NULL || !r->calculoA) {
        printf("\nEl inciso A todavia no fue calculado.\n");
        return;
    }

    printf("\nA) TRABAJO DEL ROZAMIENTO ATMOSFERICO\n");
    printf("Energia cinetica inicial: %.2f J\n", r->energia[0]);
    printf("Energia cinetica al desplegar paracaidas: %.2f J\n", r->energia[1]);
    printf("Trabajo del rozamiento: %.2f J\n", r->trabajoRozamiento);
    printf("Trabajo del rozamiento: %.3f GJ\n", r->trabajoRozamiento / 1e9);
    printf("Tramo analizado: %.2f m a %.2f m.\n", c->alturaInicial, c->alturaParacaidas);
    printf("El signo negativo indica que el rozamiento disipa energia mecanica.\n");
}

void mostrarIncisoB(const Capsula *c, const Resultados *r) {
    if (r == NULL || !r->calculoB) {
        printf("\nEl inciso B todavia no fue calculado.\n");
        return;
    }

    printf("\nB) DESACELERACION MEDIA\n");
    printf("Tiempo considerado: %.2f s\n", c->tiempoFrenado);
    printf("Aceleracion media (con signo): %.4f m/s2\n", r->aceleracionMedia);
    printf("Magnitud de la desaceleracion: %.4f m/s2\n",
           r->desaceleracionG * G_TERRESTRE);
    printf("Equivale a %.4f veces la gravedad terrestre.\n", r->desaceleracionG);
}

void mostrarIncisoC(const Capsula *c, const Resultados *r) {
    if (r == NULL || !r->calculoC) {
        printf("\nEl inciso C todavia no fue calculado.\n");
        return;
    }

    printf("\nC) FUERZA PROMEDIO DEL AGUA\n");
    printf("Peso de la capsula: %.2f N\n", r->peso);
    printf("Energia cinetica al impactar: %.2f J\n", r->energia[2]);
    printf("Distancia de hundimiento: %.2f m\n", c->distanciaHundimiento);
    printf("Fuerza promedio del agua: %.2f N\n", r->fuerzaAgua);
    printf("Equivale a %.4f veces el peso.\n", r->vecesPeso);
}

void mostrarIncisoD(const Capsula *c, const Resultados *r) {
    if (r == NULL || !r->calculoD) {
        printf("\nEl inciso D todavia no fue analizado.\n");
        return;
    }

    printf("\nD) ANALISIS DEL ANGULO DE REINGRESO\n");
    printf("Gamma ingresado: %.2f grados.\n", c->gamma);
    printf("Ventana segura indicada: %.1f a %.1f grados.\n", GAMMA_MIN, GAMMA_MAX);

    if (r->estadoGamma == 1) {
        printf("Resultado: dentro de la ventana segura indicada.\n");
    } else if (r->estadoGamma == 2) {
        printf("Resultado: angulo superior a %.1f grados.\n", GAMMA_MAX);
        printf("Un reingreso mas pronunciado puede aumentar las cargas aerodinamicas,\n");
        printf("el calentamiento y la desaceleracion, elevando el riesgo para la capsula.\n");
    } else {
        printf("Resultado: angulo inferior a %.1f grados.\n", GAMMA_MIN);
        printf("Una trayectoria demasiado rasante puede provocar un rebote atmosferico\n");
        printf("y dificultar que la capsula complete el descenso previsto.\n");
    }
    printf("El analisis es cualitativo: el enunciado no aporta datos para calcular\n");
    printf("temperaturas, fuerzas aerodinamicas ni probabilidades de rebote.\n");
}

void mostrarReporte(const Capsula *c, const Resultados *r) {
    printf("\n========== REPORTE FINAL - ARTEMIS ==========\n");
    mostrarIncisoA(c, r);
    mostrarIncisoB(c, r);
    mostrarIncisoC(c, r);
    mostrarIncisoD(c, r);
    printf("\n=============================================\n");
}

int simularDescenso(const Capsula *c) {
    const char *nombres[CANT_ETAPAS] = {
        "Ingreso a la atmosfera",
        "Frenado atmosferico inicial",
        "Desaceleracion intermedia",
        "Apertura de paracaidas",
        "Amerizaje"
    };
    double alturas[CANT_ETAPAS];
    double velocidades[CANT_ETAPAS];
    double diferenciaAltura;
    double diferenciaVelocidad;
    char respuesta;
    int i;

    if (c == NULL) {
        return 0;
    }

    diferenciaAltura = c->alturaInicial - c->alturaParacaidas;
    diferenciaVelocidad = c->velocidadInicial - c->velocidadParacaidas;

    alturas[0] = c->alturaInicial;
    alturas[1] = c->alturaInicial - diferenciaAltura * 0.25;
    alturas[2] = c->alturaInicial - diferenciaAltura * 0.50;
    alturas[3] = c->alturaParacaidas;
    alturas[4] = 0.0;

    velocidades[0] = c->velocidadInicial;
    velocidades[1] = c->velocidadInicial - diferenciaVelocidad * 0.25;
    velocidades[2] = c->velocidadInicial - diferenciaVelocidad * 0.50;
    velocidades[3] = c->velocidadParacaidas;
    velocidades[4] = c->velocidadImpacto;

    printf("\n--- SIMULACION INTERACTIVA DEL DESCENSO ---\n");
    printf("La simulacion avanza por eventos. Ingresa S para avanzar o N para cancelar.\n");

    for (i = 0; i < CANT_ETAPAS; i++) {
        if (!leerCaracterPermitido("\n¿Avanzar al siguiente evento? (S/N): ", "SN", &respuesta)) {
            return 0;
        }

        if (respuesta == 'N') {
            printf("Simulacion cancelada por el usuario.\n");
            return 1;
        }

        printf("\nEVENTO %d: %s\n", i + 1, nombres[i]);
        printf("Altura de referencia: %.2f m\n", alturas[i]);
        printf("Rapidez de referencia: %.2f m/s\n", velocidades[i]);

        if (i == 3) {
            printf("Se despliegan los paracaidas principales.\n");
        } else if (i == 4) {
            printf("La capsula llega al oceano y comienza el hundimiento.\n");
            printf("Distancia de hundimiento supuesta: %.2f m\n", c->distanciaHundimiento);
        }
    }

    printf("\nSimulacion finalizada.\n");
    printf("Aclaracion: los valores intermedios se interpolan solo con fines didacticos.\n");
    printf("No constituyen un modelo aerodinamico real ni calculan la trayectoria exacta.\n");
    return 1;
}

int agregarEvento(Evento eventos[], int *cantidad, const char *descripcion) {
    if (eventos == NULL || cantidad == NULL || descripcion == NULL ||
        *cantidad < 0 || *cantidad >= MAX_EVENTOS) {
        return 0;
    }

    eventos[*cantidad].numero = *cantidad + 1;
    snprintf(eventos[*cantidad].descripcion,
             sizeof(eventos[*cantidad].descripcion), "%s", descripcion);
    (*cantidad)++;
    return 1;
}

void mostrarHistorial(const Evento eventos[], int cantidad) {
    int i;

    printf("\n--- HISTORIAL DE OPERACIONES ---\n");
    if (cantidad == 0) {
        printf("Todavia no se registraron operaciones.\n");
        return;
    }

    for (i = 0; i < cantidad; i++) {
        printf("%d. %s\n", eventos[i].numero, eventos[i].descripcion);
    }

    if (cantidad == MAX_EVENTOS) {
        printf("Se alcanzo el limite de %d eventos; no se registran operaciones nuevas.\n",
               MAX_EVENTOS);
    }
}
