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
    char pan[17];
    char fecha_expiracion[6];
    char cvv[5];
    int h;
    char *franquisia;
    
    system("cls");

    // Validar límite de transacciones
    if (contador >= 20) {
        printf("-------------------------------------------------\n");
        printf("\n Ojo, ya no puedes agregar más transacciones. Has alcanzado tu limite de 20 transacciones. \n \n Pulsa cualquier tecla para volver al menu.");
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

    franquisia =  mirar_franquisia(pan);


    // Leer CVV
    system("cls");
    printf("Ingresa el CVV de la tarjeta: \n");
    scanf("%s", cvv);
    fflush(stdin);
    system("cls");

    int cvvAcept = validar_cvv(cvv, franquisia);
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
    guardar_archivo(h, pan, franquisia, precio, cvv, fecha_expiracion, 1);
    contador++;
    system("cls");
    printf("\nTransaccion agregada (Total de transacciones: %d) \n", contador);
    printf("Presiona cualquier tecla para continuar");
    getch();
    system("cls");
}

int validar_pan(const char *pan) {
    int longi = strlen(pan);
    int suma = 0, digito, doble;
    // system("cls");
    // printf("Longitud: %d", longi);
    // getch();
    
    if (longi < 13 || longi > 16) {
        return 0;
    }

    for (int i = 0; i < longi; i++) {
        if (!isdigit(pan[i])) {
            return 0;
        }
    }
    
    for (int i = 0; i < longi; i++) {
        digito = pan[i] - '0';
        if ((i % 2) == 0) {
            doble = digito * 2;
            if (doble > 9) {
                doble = (doble % 10) + 1; // Sumar los dígitos del resultado
            }
            suma += doble;
        } else {
            suma += digito;
        }
    }
    
    // system("cls");
    // printf("Suma Luhn: %d", suma);
    // getch();
    
    if (suma % 10 == 0) {
        system("cls");
        printf("Tarjeta valida\n\n Oprime una tecla para continuar ");
        getch();
        return 1;
    } else {
        system("cls");
        printf("Tarjeta Rechazada\n\n Oprime una tecla para continuar ");
        getch();
        return 0;
    }
}

char *mirar_franquisia(const char *pan){
    int longi = strlen(pan);
    if(((pan[0] - '0') == 4) && (longi >= 13 || longi <= 16 ) ){
        return "VISA";
    }
    if((((pan[0] - '0') == 5) || ((pan[0] - '0') == 2) ) && (longi >= 13 || longi <= 16 )){
        return "MASTERCARD";

    }
    if((((pan[0] - '0') == 3) ) && (longi >= 13 || longi <= 16 )){
        return "AMERICA-EXPRESS";

    }

    return "sin-franquisia";
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

int validar_cvv(const char *cvv, const char *franquisia) {

    if(franquisia=="AMERICA-EXPRESS"){
        if (strlen(cvv) != 4) {
            return 0;
        }
        for (int i = 0; i < strlen(cvv); i++) {
            if (!isdigit(cvv[i])) {
                return 0;
            }
        }
    }else{
        if (strlen(cvv) != 3) {
            return 0;
        }
        for (int i = 0; i < strlen(cvv); i++) {
            if (!isdigit(cvv[i])) {
                return 0;
            }
        }
    }
    
    return 1;
}

int cantidad_de_lineas_archivo() {
    FILE *archivo = fopen("archivos/transferenciad.txt", "r");
    if (archivo == NULL) {
        printf("No se encontraron transacciones para cerrar.\n");
        return 0;
    }

    int cantidad_transacciones = 0;
    char linea[200]; // Ajusta el tamaño según la longitud máxima esperada

    while (fgets(linea, sizeof(linea), archivo)) {
        int id, seguridad;
        float monto;
        char fecha[10], tipo[10], codigo[20], franquicia[20];

        int resultado = sscanf(linea, "| %d | %19s | %19s | %f | %d | %9s | %9s |", 
                               &id, codigo, franquicia, &monto, &seguridad, fecha, tipo);
        if (resultado == 7) {
            cantidad_transacciones++;
        }
    }

    fclose(archivo);
    return cantidad_transacciones;
}
