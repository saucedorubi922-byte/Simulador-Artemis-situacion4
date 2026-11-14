#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/*
 * Las funciones devuelven 1 cuando la lectura fue correcta y 0
 * cuando se alcanzo el fin de archivo (EOF).
 */
int leerEnteroRango(const char *mensaje, int minimo, int maximo, int *valor);
int leerDoubleRango(const char *mensaje, double minimo, double maximo, double *valor);
int leerCaracterPermitido(const char *mensaje, const char *permitidos, char *valor);
void pausarConsola(void);

#endif
