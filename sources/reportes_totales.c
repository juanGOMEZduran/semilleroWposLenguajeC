#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include "../headers/reportes_totales.h"

void reporte() {
    FILE *archivo = fopen("archivos/transferenciad.txt", "r");
    if (archivo == NULL) {
        printf("No se encontraron transacciones.\n");
        return;
    }

    int cantidad_transacciones = 0;
    int compras = 0, anuladas = 0;
    float monto_total = 0;
    char linea[200];

    system("cls");
    printf("\n------ REPORTE GENERAL ------\n\n");

    while (fgets(linea, sizeof(linea), archivo)) {
        int id, seguridad;
        float monto;
        char fecha[15], tipo[15], codigo[20], franquicia[20];

        int resultado = sscanf(linea, " | %d | %19s | %19s | %f | %d | %14s | %14s |", 
                               &id, codigo, franquicia, &monto, &seguridad, fecha, tipo);
        
        if (resultado == 7) {
            cantidad_transacciones++;
            monto_total += monto;

            if (strcmp(tipo, "COMPRA") == 0)
                compras++;
            else if (strcmp(tipo, "ANULADA") == 0)
                anuladas++;
        }
    }

    fclose(archivo);

    if (cantidad_transacciones == 0) {
        system("cls");
        printf("No se encontraron registros.\n\nPresiona cualquier tecla para volver al menú.");
    } else {
        printf("Total de transacciones: %d\n", cantidad_transacciones);
        printf("Monto total acumulado: %.2f\n", monto_total);
        printf("Total de COMPRAS: %d\n", compras);
        printf("Total de ANULADAS: %d\n", anuladas);
        printf("\n------------------------------\n\n");
        printf("Presiona cualquier tecla para salir.");
    }

    getch();
}
