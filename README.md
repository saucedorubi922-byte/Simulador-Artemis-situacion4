Simulador de Misiones Artemis — Situación 4 

Reingreso atmosférico, frenado aerodinámico y amerizaje 

Universidad Tecnológica Nacional — Facultad Regional Resistencia 

Ingeniería en Sistemas de Información — Algoritmos y Estructuras de Datos — 2026 

Integrantes y comisión 

Comisión: k1.4 

Integrantes: 

Maza, Fausto 

Ulibarrie, Andrea 

Saucedo, Rubi 

 Descripción del escenario Artemis y reglas del juego 

El proyecto corresponde a la Situación 4 de la misión Artemis, que trata del reingreso de la cápsula Orion a la Tierra. El escenario contempla el descenso de la cápsula desde el espacio, la reducción de velocidad provocada por el rozamiento atmosférico, el despliegue de los paracaídas y, finalmente, el amerizaje. 

Para representar esta situación, el simulador trabaja con los siguientes parámetros establecidos en el enunciado: 

Parámetro 

Valor 

Masa de la cápsula 

10.400 kg 

Velocidad inicial 

11.000 m/s 

Altura inicial 

120.000 m 

Velocidad al desplegar los paracaídas 

25 m/s 

Altura de despliegue 

2.500 m 

Tiempo de frenado 

400 s 

Velocidad de impacto 

8 m/s 

Distancia de hundimiento 

1,50 m 

Gravedad terrestre 

9,8 m/s² 

Intervalo seguro del ángulo gamma 

5,5° a 7,0° 

Reglas y condiciones del escenario: 

La cápsula inicia el reingreso a 120.000 metros de altura y con una velocidad de 11.000 m/s. 

Durante el descenso, el rozamiento atmosférico provoca la disminución de su velocidad. 

Se considera el despliegue de los paracaídas a 2.500 metros de altura y a una velocidad de 25 m/s. 

El tiempo de frenado establecido es de 400 segundos. 

Para el amerizaje se considera una velocidad de impacto de 8 m/s y una distancia de hundimiento de 1,50 metros. 

El ángulo gamma debe encontrarse entre 5,5° y 7,0° para estar dentro de la ventana segura indicada en el enunciado. 

El valor inicial de gamma no está especificado en el enunciado. Por eso, el programa utiliza 6,25° como valor predeterminado de ejemplo y permite modificarlo. 

La simulación es una representación didáctica del escenario. Los valores intermedios de altura y velocidad se obtienen mediante interpolación, por lo que no constituyen un modelo aerodinámico real. 

Detalles del funcionamiento 

El programa funciona mediante un menú interactivo por consola, desde el cual el usuario puede seleccionar las diferentes opciones disponibles. 

Sus principales funcionalidades son: 

Cargar los valores originales del enunciado o ingresar parámetros propios. 

Resolver los cuatro incisos de la situación planteada. 

Consultar los parámetros utilizados en la simulación. 

Recorrer las distintas etapas del reingreso mediante una simulación por eventos. 

Consultar los reportes generados durante la ejecución. 

Revisar el historial de eventos y operaciones realizadas. 

La simulación interactiva está dividida en cinco eventos que permiten observar los cambios de altura y velocidad durante las distintas etapas del proceso. 

 Instrucciones de compilación y ejecución  

Para compilar y ejecutar el proyecto se necesita tener instalado GCC. También se puede utilizar Make para facilitar la compilación. 

Primero, se debe abrir una terminal dentro de la carpeta del proyecto. 

Compilación utilizando Make  

make 

Para ejecutar el programa: make run 

Compilación directa con GCC 

También se puede compilar utilizando el siguiente comando: 

gcc -std=c11 -Wall -Wextra -Wpedantic -pedantic-errors -O2 main.c simulador.c validaciones.c -lm -o simulador_artemis 

Una vez compilado, ejecutar según el sistema operativo: 

Linux / macOS: ./simulador_artemis 

Windows (MinGW): simulador_artemis.exe 

Para eliminar el ejecutable generado: make clean 

Registro del uso de Inteligencia Artificial 

Durante el desarrollo del proyecto se utilizaron herramientas de inteligencia artificial como apoyo para resolver dudas, revisar propuestas y comprender distintos aspectos de la implementación, las herramientas consultadas fueron: 

ChatGPT: Se utilizó para organizar la estructura modular del programa, resolver dudas sobre las validaciones y el funcionamiento del simulador, y para consultar sobre errores de compilación e integración de archivos. 

Las respuestas obtenidas se utilizaron como orientación durante el desarrollo y fueron revisadas antes de ser aplicadas al proyecto.