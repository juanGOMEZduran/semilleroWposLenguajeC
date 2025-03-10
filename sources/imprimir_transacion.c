#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "../headers/imprimir_transacion.h"

void imprimir_transacciones() {
    const char *archivo_path = "archivos/transferenciad.txt";
    int total_lineas = cantidad_de_lineas(archivo_path);

    if (total_lineas <= 0) {
        printf("Error: No hay registros todavía.\n");
        return;
    }

    FILE *archivo = fopen(archivo_path, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo.\n");
        return;
    }

    // Reservar memoria para almacenar las líneas
    char **lineas_array = (char **)malloc(total_lineas * sizeof(char *));
    if (lineas_array == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        fclose(archivo);
        return;
    }

    char buffer[256]; 
    int index = 0;

    while (fgets(buffer, sizeof(buffer), archivo) && index < total_lineas) {
        lineas_array[index] = strdup(buffer);
        if (lineas_array[index] == NULL) {
            printf("Error: No se pudo asignar memoria para la línea %d.\n", index);
            break;
        }
        index++;
    }

    fclose(archivo);

    // Imprimir desde la última línea hasta la primera
    for (int i = index-1; i >= 0; i--) {
        system("cls");
        printf("| ID | NUMERO DE CUENTA | FRANQUICIA | MONTO | CVV | FECHA DE EXPEDICION | TIPO DE COMPRA |\n");
        printf("%s", lineas_array[i]);
        printf("\n\nPresiona cualquier tecla para ver el siguiente --->");

        getch();
        free(lineas_array[i]); // Liberar la memoria de cada línea
    }

    free(lineas_array); // Liberar el array de punteros
}

int cantidad_de_lineas(const char *archivo_path) {
    FILE *archivo = fopen(archivo_path, "r");
    if (archivo == NULL) {
        printf("Error: No se encontró el archivo.\n");
        return -1;
    }

    int count = 0;
    char c;
    while ((c = fgetc(archivo)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }

    fclose(archivo);
    return count;
}
