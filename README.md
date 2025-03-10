# Aplicación financiera que simula un datáfono

## Introducción
Semillero de Wposs por **Juan José Gómez Durán**, desarrollado con el lenguaje C. Este programa simula un datáfono.

![Imagen de referencia](https://cdn.openwebinars.net/media/featured_images/c-programacion.webp)

### 1. Explicación de cómo ejecutar
El repositorio contiene un archivo .exe para ejecutar el programa, pero también se puede hacer por consola. Por ejemplo, usando el comando **gcc main.c sources/* -o transferencia.exe** puedes generar el ejecutable del programa.

#### 1.1 Cómo usar el programa

A. El programa permite realizar transferencias, imprimir las transferencias de forma descendente, anular transferencias, generar un reporte total de transferencias, hacer un cierre que borra todas las transferencias y, por último, salir del programa.

B. **Cómo hacer una transferencia:** Para hacer una transferencia es muy sencillo. El programa te pedirá un monto, el cual se almacena como un valor de tipo *float*. Es decir, el usuario **NO** podrá ingresar letras, dobles puntos ni caracteres no numéricos, solo podrá ingresar números reales como *12* o *12.2*.

C. **Cómo imprimir las transferencias:** Las transferencias se imprimen en orden descendente y se pueden visualizar una por una, avanzando de una en una.

D. **Anular una transferencia:** En un datáfono es importante poder anular transferencias. En mi programa, el estado de la transferencia cambia. Cuando no está anulada, aparecerá como **COMPRA**, pero cuando se anule, aparecerá como **ANULADA**.

E. **Reportes totales:** En esta opción, el programa cuenta cuántas transferencias se realizaron, cuántas fueron anuladas y cuántas están en estado de compra. Además, suma el monto total de todas las transferencias registradas.

F. **Hacer cierre:** El cierre es un método que imprime la misma información que el reporte total, pero con una diferencia: este método también **BORRA** los datos de todas las transferencias realizadas en el programa.

G. **Salir del programa:** Este método solo realiza el **CIERRE** del programa, sin realizar ningún cambio adicional en los datos almacenados.

### 2. Como ejecutar el programa

Si en el caso no tienes el archivo .exe que en mi caso lo llamo como **tranferencia.exe**, puedes utilizar el terminar en sistemas linux o el cmd o poweshell, para ejecutarlo vas a escribir un comando, el cual es el siguiente 

```bash
gcc main.c sources/* -o  tranferencia.exe`

Este comando creeara automaticamente el ejecutable para usar a disposición del usuario.
Una ves puedes ejecutar el exe de la siguiente forma 

En sistemas Unix/linux como: 

```bash
./tranferencia

En sistemas Windows como:

``` bash
tranferencia.exe

### Conclusión
Mi programa cumple con todas las funcionalidades requeridas en el semillero.
