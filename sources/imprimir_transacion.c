#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "../headers/imprimir_transacion.h"



void imprimir_transacciones()
{
    const char *archivos = "archivos/transferenciad.txt";
    int lineas = cantidad_de_lineas(archivos);

    if (lineas != 0){
        system("cls");
        //printf("El archivo tiene %d Registros.\n", lineas);

        FILE *archivo = fopen(archivos, "r");
        if (archivo == NULL)
        {
            system("cls");
            printf("Error: No se pudo abrir el archivo.\n");
            return;
        }

        // Almacenar las líneas en un array dinámico
        int max_lineas = cantidad_de_lineas(archivos);
        if (max_lineas <= 0)
        {
            fclose(archivo);
            return;
        }

        char **lineas = (char **)malloc(max_lineas * sizeof(char *));
        if (lineas == NULL)
        {
            printf("Error: No se pudo asignar memoria.\n");
            fclose(archivo);
            return;
        }

        char buffer[256]; // Buffer para leer cada línea
        int index = 0;

        while (fgets(buffer, sizeof(buffer), archivo) && index < max_lineas)
        {
            lineas[index] = strdup(buffer); // Copiar la línea en memoria dinámica
            if (lineas[index] == NULL)
            {
                printf("Error: No se pudo asignar memoria para una línea.\n");
                break;
            }
            index++;
        }

        fclose(archivo);

        for (int i = index - 1; i >= 0; i--)
        {
            system("cls");
            printf("| ID | NUMERO DE CUENTA | MONTO | CVV | FECHA DE EXPEDICION | TIPO DE COMPRA | \n ");
            printf("%s", lineas[i]);
            printf("\n\n hunde cualquier tecla para ver el siguiente --->");

            getch();
            free(lineas[i]); // Liberar memoria de cada línea
        }

        free(lineas);
    }
    else
    {
        printf("Error: No hay registros todavia.\n");
    }
}

int cantidad_de_lineas(const char *archivos)
{
    FILE *archivo = fopen(archivos, "r");
    if (archivo == NULL)
    {
        printf("Error: No se encontró el archivo.\n");
        return -1;
    }
    int count = 0;
    char c;
    while ((c = fgetc(archivo)) != EOF)
    {
        if (c == '\n')
        {
            count++;
        }
    }
    fclose(archivo);
    return count;
}
