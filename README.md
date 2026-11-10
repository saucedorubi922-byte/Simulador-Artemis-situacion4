# Simulador de Misiones Artemis — Situación 4

**Reingreso atmosférico, frenado aerodinámico y amerizaje**  
Universidad Tecnológica Nacional — Facultad Regional Resistencia  
Algoritmos y Estructuras de Datos — Ingeniería en Sistemas de Información — 2026

> Completar antes de entregar: comisión, integrantes y enlace al repositorio.

## 1. Descripción

El proyecto implementa un simulador interactivo por consola para representar, con fines didácticos, distintas etapas del reingreso de la cápsula Orion. Permite cargar los valores del enunciado o ingresar parámetros propios, resolver los incisos A, B, C y D, recorrer una simulación por eventos y consultar un reporte y un historial.

La simulación por eventos es ilustrativa: los valores intermedios de altura y rapidez se interpolan para mostrar el avance. No constituye un modelo aerodinámico real.

## 2. Datos originales de la Situación 4

| Parámetro | Valor |
|---|---:|
| Masa | 10.400 kg |
| Rapidez inicial | 11.000 m/s |
| Altura inicial | 120.000 m |
| Rapidez al desplegar paracaídas | 25 m/s |
| Altura de despliegue | 2.500 m |
| Tiempo de frenado | 400 s |
| Rapidez de impacto | 8 m/s |
| Distancia de hundimiento | 1,50 m |
| Gravedad terrestre | 9,8 m/s² |
| Ventana segura de gamma | 5,5° a 7,0° |

El enunciado no fija un valor inicial para el ángulo gamma. El programa utiliza 6,25° como ejemplo, pero permite modificarlo.

## 3. Cálculos físicos

### Inciso A — Trabajo del rozamiento atmosférico

Se aplica el teorema trabajo-energía entre 120.000 m y 2.500 m:

`Wroz + Wgravedad = Kf - Ki`

Como el desplazamiento es descendente:

`Wgravedad = m * g * (hi - hf)`

Por lo tanto:

`Wroz = (Kf - Ki) - m * g * (hi - hf)`

Con los datos originales:

`Wroz = -641.172.350.000 J`

El signo negativo indica que el trabajo del rozamiento se opone al movimiento y disipa energía mecánica.

### Inciso B — Desaceleración media

`a_media = (vf - vi) / delta_t`

Con los datos originales:

- Aceleración media con signo: `-27,4375 m/s²`.
- Magnitud de la desaceleración: `27,4375 m/s²`.
- Desaceleración expresada en gravedad terrestre: aproximadamente `2,7997 g` (2,80 g redondeado).

### Inciso C — Fuerza promedio del agua

Se toma como positivo el sentido vertical hacia abajo. Durante el hundimiento actúan el peso hacia abajo y la fuerza del agua hacia arriba:

`(Peso - FuerzaAgua) * d = -Ki`

Despejando:

`FuerzaAgua = Peso + Ki / d`

Con los datos originales:

- Peso: `101.920 N`.
- Energía cinética al impacto: `332.800 J`.
- Fuerza promedio del agua: `323.786,67 N`.
- Relación fuerza/peso: `3,1769`, aproximadamente `3,18`.

Este resultado corresponde al modelo de fuerza promedio constante equivalente durante los 1,50 m de hundimiento.

### Inciso D — Ángulo de reingreso gamma

El programa compara el ángulo ingresado con el intervalo indicado en el enunciado:

`5,5° <= gamma <= 7,0°`

- Si `gamma` está dentro del intervalo, se informa que está dentro de la ventana segura indicada.
- Si `gamma > 7,0°`, se explican cualitativamente los posibles aumentos de desaceleración, calentamiento y cargas aerodinámicas.
- Si `gamma < 5,5°`, se explica el posible rebote atmosférico de una trayectoria demasiado rasante.

El inciso es cualitativo: el enunciado no proporciona datos para calcular temperaturas, fuerzas aerodinámicas ni probabilidades de rebote.

## 4. Organización de archivos

| Archivo | Responsabilidad |
|---|---|
| `main.c` | Función `main`, menú y flujo general |
| `simulador.h` | Constantes, estructuras y prototipos |
| `simulador.c` | Validación de parámetros, cálculos, simulación, reportes e historial |
| `validaciones.h` | Prototipos de lectura segura |
| `validaciones.c` | Lectura y validación de enteros, reales y caracteres |
| `Makefile` | Compilación, ejecución y limpieza |
| `GUIA_COLOQUIO.md` | Preguntas orientativas para preparar la defensa |

## 5. Recursos de C utilizados

- **Estructuras (`struct`)**: `Capsula`, `Resultados` y `Evento` agrupan datos relacionados.
- **Arreglos**: `energia[3]` almacena energías; la simulación utiliza arreglos de alturas, velocidades y nombres de etapas; `eventos[MAX_EVENTOS]` almacena el historial.
- **Punteros**: se utilizan para modificar estructuras desde funciones, devolver valores leídos mediante parámetros de salida y actualizar la cantidad de eventos.
- **Condicionales**: validan parámetros, controlan el menú y clasifican el ángulo gamma.
- **Ciclos**: permiten repetir el menú, solicitar nuevamente entradas inválidas y avanzar por los eventos.
- **Modularización**: separa la interfaz principal, la lógica del simulador y las validaciones de entrada.

## 6. Compilación y ejecución

Se necesita GCC y `make` (opcional).

Desde la carpeta del proyecto:

```bash
make
make run
```

También se puede compilar directamente:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -pedantic-errors -O2 main.c simulador.c validaciones.c -lm -o simulador_artemis
```

En Linux/macOS:

```bash
./simulador_artemis
```

En Windows, si se utiliza MinGW:

```bash
simulador_artemis.exe
```

Para borrar el ejecutable:

```bash
make clean
```

## 7. Prueba de referencia

Con los valores originales, seleccionar la opción 7. Los resultados esperados, con redondeo, son:

| Inciso | Resultado |
|---|---:|
| A | −641.172.350.000 J |
| B | −27,4375 m/s² |
| B en magnitud | 27,4375 m/s² ≈ 2,80 g |
| C | 323.786,67 N |
| C / peso | 3,1769 ≈ 3,18 |
| D | 6,25°: dentro de la ventana segura indicada |

## 8. Uso responsable de inteligencia artificial

Registrar aquí el uso real realizado por el equipo y completar los prompts exactos que decidan documentar.

### Herramientas y tareas

- **ChatGPT**: apoyo para organizar la estructura modular, revisar la interpretación de las fórmulas físicas, proponer validaciones y mejorar la documentación y la preparación del coloquio.
- **GitHub Copilot**: se consultaron propuestas de organización y explicaciones conceptuales. Sus fórmulas simplificadas para A y C fueron revisadas y no se incorporaron porque no contemplaban, respectivamente, el trabajo de la gravedad y el peso durante el hundimiento.

### Consultas realizadas (resumen; completar con los prompts exactos del equipo)

- Solicitud de un simulador modular en C para la Situación 4 de Artemis.
- Revisión de los cálculos de trabajo del rozamiento, desaceleración media y fuerza promedio del agua.
- Comparación crítica de una propuesta de código y explicación de sus limitaciones.
- Solicitud de mejoras para validaciones, simulación por eventos, documentación y defensa técnica.

### Cómo se debe validar y adaptar

El equipo debe compilar el proyecto, ejecutar los casos de prueba, contrastar los resultados con los cálculos analíticos y revisar el código. Cada integrante debe comprender y poder explicar las decisiones de implementación. No se debe declarar como realizada una prueba que el equipo no haya ejecutado.

## 9. Antes de entregar

- [ ] Completar comisión e integrantes.
- [ ] Verificar que todos los integrantes comprendan el código.
- [ ] Ejecutar las pruebas y guardar evidencia.
- [ ] Crear el repositorio público GitHub/GitLab.
- [ ] Realizar commits progresivos y reales de los integrantes; no subir todo en un único commit final.
- [ ] Completar el registro de IA con los prompts reales.
- [ ] Grabar el video grupal de hasta 5 minutos con la participación y voces reales de todos los integrantes.


## 10. Preparación para el coloquio

### ¿Por qué se dividió el programa en varios archivos?
Para separar responsabilidades: `main.c` controla el menú; `simulador.c` contiene los cálculos y la simulación; `validaciones.c` concentra la lectura segura. Los encabezados `.h` comparten estructuras, constantes y prototipos.

### ¿Para qué se utilizan las estructuras?
`Capsula` agrupa los parámetros físicos, `Resultados` guarda los resultados y el estado de cada cálculo, y `Evento` representa una operación del historial.

### ¿Dónde se utilizan punteros?
Las funciones reciben punteros a `Capsula` y `Resultados` para consultar y modificar estructuras sin copiarlas. También se utiliza `int *cantidad` para actualizar la cantidad de eventos registrados.

### ¿Qué arreglos utiliza el programa?
Se utiliza `energia[3]` para almacenar energías cinéticas; arreglos locales para las etapas, alturas y velocidades de la simulación; y `eventos[MAX_EVENTOS]` para el historial.

### ¿Por qué el trabajo del rozamiento es negativo?
Porque el rozamiento se opone al movimiento. Para aislar su trabajo se considera también el trabajo positivo de la gravedad durante el descenso.

### ¿Por qué se suma el peso en el inciso C?
Porque durante el hundimiento actúan el peso hacia abajo y la fuerza del agua hacia arriba. Con el eje positivo hacia abajo, el trabajo neto es `(Peso - FuerzaAgua) * distancia`.

### ¿La simulación representa una trayectoria real?
No. Los puntos intermedios se interpolan con fines didácticos. No se modelan densidad atmosférica, coeficientes aerodinámicos ni una trayectoria física completa.

### Demostración sugerida
1. Ejecutar la opción 7 para mostrar los cuatro incisos.
2. Mostrar los parámetros actuales.
3. Avanzar por los cinco eventos de la simulación interactiva.
4. Consultar el historial.
5. Probar una entrada inválida y un ángulo gamma fuera de la ventana segura.

