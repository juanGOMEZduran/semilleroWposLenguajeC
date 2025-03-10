#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "../headers/cierre.h"


void realizar_cierre()

{
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
    char linea[256];
    system("cls");
    printf("\n------ REPORTE GENERAL ------\n");

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
        printf("No se econtraron registros \n\n Pulsa una tecla para volver al menu ");
        getch();
    }else{
        printf("Total de transacciones: %d\n", cantidad_transacciones);
        printf("Monto total acumulado: %.2f\n", monto_total);
        printf("Total de COMPRA: %d\n", compras);
        printf("Total de ANULADA: %d\n", anuladas);
        printf("\n\nPulsa cualquier tecla para cerrar y borrar la informacion ");
        getch();
    }
    

    archivo = fopen("archivos/transferenciad.txt", "w"); // Abrir en modo escritura para borrar contenido
    fclose(archivo);

    return;
}
