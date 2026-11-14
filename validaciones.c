#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "validaciones.h"

#define TAM_LINEA 256

/*
 * Lee una linea completa. Devuelve:
 *  1: lectura correcta
 *  0: linea demasiado larga
 * -1: fin de archivo o error de lectura
 */
static int leerLinea(char linea[], size_t tam) {
    size_t largo;
    int caracter;

    if (fgets(linea, (int)tam, stdin) == NULL) {
        return -1;
    }

    largo = strlen(linea);

    if (largo > 0 && linea[largo - 1] == '\n') {
        linea[largo - 1] = '\0';
        if (largo > 1 && linea[largo - 2] == '\r') {
            linea[largo - 2] = '\0';
        }
        return 1;
    }

    if (!feof(stdin)) {
        while ((caracter = getchar()) != '\n' && caracter != EOF) {
            /* Descarta el resto de la linea demasiado larga. */
        }
        return 0;
    }

    return 1;
}

static const char *saltarEspacios(const char *texto) {
    while (*texto != '\0' && isspace((unsigned char)*texto)) {
        texto++;
    }
    return texto;
}

static int soloQuedanEspacios(const char *texto) {
    texto = saltarEspacios(texto);
    return *texto == '\0';
}

int leerEnteroRango(const char *mensaje, int minimo, int maximo, int *valor) {
    char linea[TAM_LINEA];
    char *fin;
    long numero;
    int estado;

    if (valor == NULL || minimo > maximo) {
        return 0;
    }

    for (;;) {
        printf("%s", mensaje);
        fflush(stdout);

        estado = leerLinea(linea, sizeof(linea));
        if (estado == -1) {
            printf("\nFin de entrada. Se cerrara el simulador.\n");
            return 0;
        }
        if (estado == 0) {
            printf("Entrada demasiado larga. Intenta nuevamente.\n");
            continue;
        }

        errno = 0;
        numero = strtol(linea, &fin, 10);

        if (fin == linea || errno == ERANGE ||
            !soloQuedanEspacios(fin) ||
            numero < minimo || numero > maximo) {
            printf("Entrada invalida. Ingresa un entero entre %d y %d.\n",
                   minimo, maximo);
            continue;
        }

        *valor = (int)numero;
        return 1;
    }
}

int leerDoubleRango(const char *mensaje, double minimo, double maximo, double *valor) {
    char linea[TAM_LINEA];
    char *fin;
    double numero;
    int estado;

    if (valor == NULL || minimo > maximo) {
        return 0;
    }

    for (;;) {
        printf("%s", mensaje);
        fflush(stdout);

        estado = leerLinea(linea, sizeof(linea));
        if (estado == -1) {
            printf("\nFin de entrada. Se cancelara la carga de parametros.\n");
            return 0;
        }
        if (estado == 0) {
            printf("Entrada demasiado larga. Intenta nuevamente.\n");
            continue;
        }

        errno = 0;
        numero = strtod(linea, &fin);

        if (fin == linea || errno == ERANGE ||
            !soloQuedanEspacios(fin) || !isfinite(numero) ||
            numero < minimo || numero > maximo) {
            printf("Entrada invalida. Ingresa un numero finito entre %.3f y %.3f.\n",
                   minimo, maximo);
            continue;
        }

        *valor = numero;
        return 1;
    }
}

int leerCaracterPermitido(const char *mensaje, const char *permitidos, char *valor) {
    char linea[TAM_LINEA];
    const char *inicio;
    char candidato;
    int estado;

    if (permitidos == NULL || valor == NULL) {
        return 0;
    }

    for (;;) {
        printf("%s", mensaje);
        fflush(stdout);

        estado = leerLinea(linea, sizeof(linea));
        if (estado == -1) {
            printf("\nFin de entrada.\n");
            return 0;
        }
        if (estado == 0) {
            printf("Entrada demasiado larga. Intenta nuevamente.\n");
            continue;
        }

        inicio = saltarEspacios(linea);
        if (*inicio == '\0') {
            printf("Debes ingresar un caracter.\n");
            continue;
        }

        candidato = (char)toupper((unsigned char)*inicio);
        inicio++;

        if (!soloQuedanEspacios(inicio) ||
            strchr(permitidos, candidato) == NULL) {
            printf("Opcion invalida. Caracteres permitidos: %s.\n", permitidos);
            continue;
        }

        *valor = candidato;
        return 1;
    }
}

void pausarConsola(void) {
    char linea[TAM_LINEA];
    printf("\nPresiona ENTER para volver al menu...");
    (void)leerLinea(linea, sizeof(linea));
}
