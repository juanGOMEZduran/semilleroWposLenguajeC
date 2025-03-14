#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void imprimir_transacciones();
int cantidad_de_lineas(const char *archivo_path);
void ocultar_numero_cuenta(char *numero_cuenta, char *resultado);
void navegar_transacciones();

void imprimir_transacciones() {
    const char *archivo_path = "archivos/transferenciad.dat";
    int total_lineas = cantidad_de_lineas(archivo_path);

    if (total_lineas <= 0) {
        printf("Error: No hay registros todavia.\n");
        return;
    }

    FILE *archivo = fopen(archivo_path, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo.\n");
        return;
    }

    char lineas[100][256];  
    int num_lineas = 0;

    while (fgets(lineas[num_lineas], sizeof(lineas[num_lineas]), archivo) && num_lineas < 100) {
        num_lineas++;
    }
    fclose(archivo);

    navegar_transacciones(lineas, num_lineas);
}

void navegar_transacciones(char lineas[100][256], int num_lineas) {
    int indice = num_lineas - 1;
    char tecla;
    
    do {
        system("cls");
        printf("+----+----------------------+--------------------+------------+-----+-------------------+------------------+----------\n");
        
        printf("| %-4s | %-18s | %-19s | %-25s | %-9s | %-12s | %-10s |\n",
               " ID ", " NUMERO DE CUENTA ", " FRANQUICIA ", " MONTO ", " CVV ", " FECHA EXP ", " TIPO ");
        
        char copia_linea[256];
        strcpy(copia_linea, lineas[indice]);
        
        char *datos[7];
        char *token = strtok(copia_linea, "|");
        int j = 0;

        while (token != NULL && j < 7) {
            datos[j++] = token;
            token = strtok(NULL, "|");
        }
        printf("+----+----------------------+--------------------+------------+-----+-------------------+------------------+----------\n");

        if (j < 7) {
            printf("| Error al leer la línea: %s |\n", lineas[indice]);
        } else {
            char cuenta_oculta[25];  
            ocultar_numero_cuenta(datos[1], cuenta_oculta);

            printf("| %-4s | %-18s | %-19s | %-25s | %-9s | %-12s | %-10s |\n",
                   datos[0], cuenta_oculta, datos[2], datos[3], datos[4], datos[5], datos[6]);
        }

        printf("+----+----------------------+--------------------+------------+-----+-------------------+------------------+----------\n");
        printf("\n\n");
        printf("[ ");
        if (indice > 0) printf("a o A- Siguiente ");
        if (indice < num_lineas - 1) printf("d o D - Anterior ");
        printf("] (Presiona doblemente 'q' para salir, o 'q' mas cualquier tecla)\n");
        
        tecla = getch();
        if ((tecla == 'a' || tecla == 'A' ) && indice > 0) indice--;
        if ((tecla == 'd' || tecla == 'D') && indice < num_lineas - 1) indice++;
    } while (tecla != 'q' );
}

void ocultar_numero_cuenta(char *numero_cuenta, char *resultado) {
    int len = strlen(numero_cuenta);
    if (len < 13) {  
        strcpy(resultado, numero_cuenta);  
    } else {
        snprintf(resultado, len + 1, "%.5s*******%.5s", numero_cuenta, numero_cuenta + len - 5);
    }
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
