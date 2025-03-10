#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include "../headers/reportes_totales.h"

void reporte(){
    FILE *archivo;
    archivo = fopen("archivos/transferenciad.txt", "r");
    if (archivo == NULL)
    {
        printf("No se encontraron transacciones para cerrar.\n");
        return;
    }

    int cantidad_transacciones = 0;
    int compras = 0, anuladas = 0;
    float monto_total = 0;
    char linea[80];
    system("cls");
    printf("\n------ REPORTE GENERAL ------\n\n");

    while (fgets(linea, sizeof(linea), archivo))
    {
        int id, seguridad;
        float monto;
        char fecha[10], tipo[10], codigo[20];

        int resultado = sscanf(linea, " | %d | %s | %f | %d | %9s | %10s |", 
                               &id, codigo, &monto, &seguridad, fecha, tipo);
        
        if (resultado == 6)
        {
            cantidad_transacciones++;
            monto_total += monto;

            if (strcmp(tipo, "COMPRA") == 0)
                compras++;
            else if (strcmp(tipo, "ANULADA") == 0)
                anuladas++;
        }
    }

    fclose(archivo);

    if(cantidad_transacciones==0){
        system("cls");
        printf("No se encotraron registros\n\nHunde una tecla y vuelve al menu. ");
        getch();

    }else{
        printf("Total de transacciones: %d\n", cantidad_transacciones);
        printf("Monto total acumulado: %.2f\n", monto_total);
        printf("Total de COMPRA: %d\n", compras);
        printf("Total de ANULADA: %d\n", anuladas);
        printf("\n------------------------------\n\n");
        printf("Pulsa cualquier tecla para salir ");
    }

    
}
