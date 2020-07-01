# Human Machine Interface for garbage truck
HMI used to show information about truck status and collection plan.

## El proyecto
Descripción general del proyecto

### Especificaciones

* Pantalla a color RGB LCD de resolución 240x320.
* Procesador de 32 bits (VexRiscV).
* Frecuencia del reloj: 100MHz.
* Memoria ROM integrada de 8Kb.
* Memoria RAM de 4Kb.

## Soc

### VexRiscV

A nivel técnico el proyecto se compone de una implementación de un System On Chip (SoC), con el procesador SoftCore VexRiscV y los correspondientes periféricos. La comunicación entre el procesador y los periféricos es mediante la implementación del bus Wishbone.

La pantalla de visualización es el chip ILI9341 que se comunica en paralelo con el soc. Para controlar la pantalla se diseñó desde el hardware un periférico que escribe en los registros de la pantalla, para comunicar el soc con un un computador se usan dos perifericos: UART y UART_PHY. 

![HMI Soc](Docs/Soc/SOC.png)

## Hardware

### Mapa de memoria general del SOC 

El mapa de memoria general del SoC es el siguiente

![Mem map ](Docs/MemoryMap/general_map.png)

### LCD Paralelo

El periferico diseñado en este proyecto fue un controlador del chip de la pantalla ILI9341. Para realizar este diseño se tuvieron en cuenta dos cosas:

* Registros de control y direcciones de comandos del chip ILI9341.
* Diagrama de tiempos del chip.

Para controlar la pantalla se disponen del los pines:

La shield del chip tiene los siguientes pines:
* DB[7:0]
* RS
* WR
* RST
* CS
* RD

Como se trata de un solo esclavo (la pantalla LCD) que manejará el periférico, el pin CS se deja permanentemente en nivel bajo; de la misma manera el periférico solo escribirá datos en el esclavo, mas no leerá registros de este, por lo que también el pin RD (que habilita lectura/escritura de los registros del chip) se dejará constantemente en nivel bajo.

El diagrama de tiempos que provee el fabricante de la pantalla se muestra a continuación.

![ILI9341 time diag](Docs/ili9341/Timed_lcd.png)

Tener en cuenta los tiempos mínimos y máximos establecidos en la hoja de datos del chip ILI9341.

El periférico diseñado realiza la tarea descrita en el diagrama de tiempos; hace dos tareas diferenciadas:
* Escribir un dato en la salida a modo de instrucción (seleccionar una dirección de registro, RS nivel bajo).
* Escribir un dato en la salida a modo de argumento (guardar un dato en el registro seleccionado, RS nivel alto).

El módulo está diseñado con la herramienta LiteX mediante el uso del submódulo FSM (ver documentación de creación de máquinas de estado finitas en litex).

El mapa de memoria se relaciona a continuación.

![ILI9341 memory map](Docs/MemoryMap/lcd_map.png)

Las señales de control START y BUSY respectivamente da inicio al ciclo de escritura y asegura que no se realice un ciclo mientras se este realizando otro en ese momento. Para efectos de generalidad, se deja como registro el valor que se escribe en el pin CS, para casos en los que se necesite manejar más de una pantalla. Queda pendiente realizar la generalidad para el caso en que se necesite leer datos de los registros del chip.

![ILI9341 FSM ](Docs/ili9341/FSM_lcd.png)
