#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "../headers/cierre.h"


void realizar_cierre()

{
    FILE *archivo;
    archivo = fopen("archivos/transferenciad.dat", "r");
    if (archivo == NULL)
    {
        printf("No se encontraron transacciones para cerrar.\n");
        return;
    }

    int cantidad_transacciones = 0;
    int compras = 0, anuladas = 0;
    float monto_total = 0;
    char linea[256];
    system("cls");
    

    while (fgets(linea, sizeof(linea), archivo)) {
        int id, seguridad;
        float monto;
        char fecha[15], tipo[15], codigo[20], franquicia[20];

        int resultado = sscanf(linea, " | %d | %19s | %19s | %f | %d | %14s | %14s |", 
                               &id, codigo, franquicia, &monto, &seguridad, fecha, tipo);
        
        if (resultado == 7) {
            cantidad_transacciones++;
            
            if (strcmp(tipo, "COMPRA")==0)
            {
                monto_total += monto;
            }
            
            if (strcmp(tipo, "COMPRA") == 0)
                compras++;
            else if (strcmp(tipo, "ANULADA") == 0)
                anuladas++;
        }
    }

    system("cls");
    printf("\n------ REPORTE GENERAL DEL CIERRE ------\n");
    printf("Total de transacciones: %d\n", cantidad_transacciones);
    printf("Monto total acumulado: %.2f\n", monto_total);
    printf("Total de COMPRA: %d\n", compras);
    printf("Total de ANULADA: %d\n", anuladas);
    printf("\n\nPulsa cualquier tecla para cerrar y borrar la informacion ");
    getch();

    fclose(archivo);
    archivo = fopen("archivos/transferenciad.dat", "w"); // Abrir en modo escritura para borrar contenido
    fclose(archivo);
    

    return;
}
