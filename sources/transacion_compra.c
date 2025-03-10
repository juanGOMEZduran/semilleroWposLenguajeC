#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctype.h> // Agregado para usar isdigit
#include "../headers/guardar_transacion.h"




void hacer_compra(float precio) {
    int contador = cantidad_de_lineas_archivo();
    char pan[17]; // Se cambia a 17 para permitir el '\0'
    char fecha_expiracion[6];
    char cvv[4];
    int h;
    
    system("cls");

    // Validar límite de transacciones
    if (contador >= 20) {
        printf("-------------------------------------------------\n");
        printf("\n Ojo, ya no puedes agregar más transacciones. Has alcanzado tu límite de 20 transacciones. \n \n Pulsa cualquier tecla para volver al menu.");
        printf("-------------------------------------------------\n");
        getch();
        return;
    }

    system("cls");
    printf("Ingresa el numero de tarjeta bancaria (PAN): \n");
    scanf("%s", pan);
    fflush(stdin);

    int panAcept = validar_pan(pan);
    if (panAcept == 0) {
        system("cls");
        printf("Escribiste mal el pan, por favor pulsa una tecla \n para volver al menu,\n");
        getch();
        system("cls");
        return;
    }

    // Leer CVV
    system("cls");
    printf("Ingresa el CVV de la tarjeta: \n");
    scanf("%s", cvv);
    fflush(stdin);
    system("cls");

    int cvvAcept = validar_cvv(cvv);
    if (cvvAcept == 0) {
        system("cls");

        printf("Escribiste mal el cvv. \n \n Por favor pulsa una tecla para volver al menu,\n");
        getch();
        system("cls");
        return;
    }

    // Leer fecha de expiración
    system("cls");
    printf("Escribe la fecha de expiracion de la tarjeta (MM/YY): \n");
    scanf("%s", fecha_expiracion);
    fflush(stdin);
    int fecha_exp_acept = validar_fecha_exp(fecha_expiracion);
    if (!fecha_exp_acept) {
        system("cls");
        printf("Error!, escribiste mal la fecha de expiracion o ya expiro\n volveras al menu.");
        getch();
        system("cls");
        return;
    }

    h = contador;
    guardar_archivo(h, pan, precio, cvv, fecha_expiracion, 1);
    contador++;
    system("cls");
    printf("\nTransaccion agregada (Total de transacciones: %d) \n", contador);
    printf("Presiona cualquier tecla para continuar");
    getch();
    system("cls");
}

int validar_pan(const char *pan) {
    int longi = strlen(pan);
    if (longi < 13 || longi > 16) {
        return 0;
    }
    for (int i = 0; i < longi; i++) {
        if (!isdigit(pan[i])) {
            return 0;
        }
    }
    return 1;
}

int validar_fecha_exp(const char *fecha_expiracion) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    if (strlen(fecha_expiracion) != 5) {
        return 0;
    }
    if (!isdigit(fecha_expiracion[0]) || !isdigit(fecha_expiracion[1]) ||
        fecha_expiracion[2] != '/' ||
        !isdigit(fecha_expiracion[3]) || !isdigit(fecha_expiracion[4])) {
        return 0;
    }

    int mes = (fecha_expiracion[0] - '0') * 10 + (fecha_expiracion[1] - '0');
    int anio = 2000 + (fecha_expiracion[3] - '0') * 10 + (fecha_expiracion[4] - '0');
    if (mes < 1 || mes > 12) {
        return 0;
    }
    if (mes < (tm_info->tm_mon + 1)) {
        return 0;
    }
    if (anio < (tm_info->tm_year + 1900)) {
        return 0;
    }
    return 1;
}

int validar_cvv(const char *cvv) {
    if (strlen(cvv) != 3) {
        return 0;
    }
    for (int i = 0; i < strlen(cvv); i++) {
        if (!isdigit(cvv[i])) {
            return 0;
        }
    }
    return 1;
}


int cantidad_de_lineas_archivo(){
    FILE *archivo;
    archivo = fopen("archivos/transferenciad.txt", "r");
    if (archivo == NULL)
    {
        printf("No se encontraron transacciones para cerrar.\n");
        return 0;
    }
    int cantidad_transacciones = 0;
    char linea[80];


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
        }
    }
    return cantidad_transacciones;
    fclose(archivo);

}