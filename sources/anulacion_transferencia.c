#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h> // Agregado para usar isdigit
#include "../headers/anulacion_tranferencia.h"

void anulacion(char id[]) {  

    const char *archivo_path = "archivos/transferenciad.dat";
    int total_lineas = cantidad_de_linea_anulacion(archivo_path);

    if(total_lineas==0){
        system("cls");
        printf("no hay registros en el archivo");
        getch();
    }else{
        FILE *archivo = fopen("archivos/transferenciad.dat", "r");
        if (archivo == NULL) {
            printf("No se encontraron transacciones para buscar.\n");
            return;
        }
        short opAnulacion;
        char utimos_digitos_pan[5];
        char digitos_cvv[4];
        int validacion_id=validad_id_buscando(id);
        if(validacion_id == 0){
            system("cls");
            printf("escribiste mal el id a buscar\n\n");
            printf("Pulsa una tecla para volver al menu\n");
            getch();
            system("cls");
            return;
        }

        
        
        FILE *tempArchivo = fopen("archivos/temp_transferenciad.dat", "w");
        if (tempArchivo == NULL) {
            printf("No se pudo crear el archivo temporal.\n");
            fclose(archivo);
            return;
        }
        
        char linea[200];
        int encontrado = 0;
        while (fgets(linea, sizeof(linea), archivo)) {
            int idarchivo;
            float monto;
            char fecha[10], tipo[10], codigo[18], seguridad[6], franquicia[20];

            int resultado = sscanf(linea, "| %d | %s | %s | %f | %s | %9s | %10s |", 
                                &idarchivo, codigo, &franquicia,  &monto, seguridad, fecha, tipo);
            
            if (resultado == 7) {
                if (idarchivo == strtol(id, NULL, 10)) {
                    encontrado = 1;
                    system("cls");
                    printf("Se encontro la transaccion %d.\n\nOprime cualquier tecla para continuar.", idarchivo);
                    getch();
                    system("cls");
                    printf("Seguro que quieres anular la compra? Oprime tu opcion. \n\n(1). Anular la compra. \n(2). No anular la compra.  \n"); 
                    scanf("%hd", &opAnulacion);
                    system("cls");
                    if (opAnulacion == 1) {
                        printf("Ingresa los ultimos 4 digitos del PAN: ");
                        scanf("%s", utimos_digitos_pan);
                        if (validar_utimos_digitos_pan(utimos_digitos_pan) == 0) {
                            system("cls");
                            printf("Ingresaste mal los ultimos 4 digitos.\nPulsa una tecla para salir al menu");
                            getch();
                            system("cls");
                            fclose(archivo);
                            fclose(tempArchivo);
                            remove("archivos/temp_transferenciad.dat");
                            return;
                        }else{
                            system("cls");
                            printf("Ingresaste Bien los valores \n\nOprime una tecla para continuar");
                            getch();
                        }
                        system("cls");

                        printf("Ingresa el codigo de seguridad CVV: ");
                        scanf("%s", digitos_cvv);
                        if (validar_digitos_cvv(digitos_cvv, franquicia) == 0) {
                            system("cls");
                            printf("Ingresaste mal el código de seguridad.\nPulsa una tecla para salir al menu");
                            getch();
                            fclose(archivo);
                            fclose(tempArchivo);
                            remove("archivos/temp_transferenciad.dat");
                            return;
                        }
                        system("cls");

                        fprintf(tempArchivo, "| %d | %s | %s | %.2f | %s | %s | ANULADA |\n", idarchivo, codigo, franquicia, monto, seguridad, fecha);
                        printf("La transaccion ha sido anulada correctamente.\n\nOprime una tecla para volver al menu ");
                        getch();
                    } else {
                        fprintf(tempArchivo, "%s", linea);
                        printf("Oprime cualquier tecla para regresar al menu.");
                        getch();
                    }
                } else {
                    fprintf(tempArchivo, "%s", linea);
                }
            } else {
                fprintf(tempArchivo, "%s", linea);
            }
        }

        fclose(archivo);
        fclose(tempArchivo);
        remove("archivos/transferenciad.dat");
        rename("archivos/temp_transferenciad.dat", "archivos/transferenciad.dat");

        if (!encontrado) {
            system("cls");
            printf("No se encontro la transaccion con el ID especificado.\n\n Oprime un tecla para regresar al menu \n");
            getch();
        }
    }
    
}

int validad_id_buscando(const char *id) {
    for (int i = 0; i < strlen(id); i++) {
        if (!isdigit(id[i])) {
            return 0;
        }
    }
    return 1;
}

int validar_utimos_digitos_pan(const char *utimos_digitos_pan) {
    if (strlen(utimos_digitos_pan) != 4) {
        return 0;
    }
    for (int i = 0; i < strlen(utimos_digitos_pan); i++) {
        if (!isdigit(utimos_digitos_pan[i])) {
            return 0;
        }
    }
    return 1;
}

int validar_digitos_cvv(const char *digitos_cvv, const char *franquicia) {

    if(franquicia=="AMERICA-EXPRESS"){
        if (strlen(digitos_cvv) != 4) {
            return 0;
        }
        for (int i = 0; i < strlen(digitos_cvv); i++) {
            if (!isdigit(digitos_cvv[i])) {
                return 0;
            }
        }
    }else{
        if (strlen(digitos_cvv) != 3) {
            return 0;
        }
        for (int i = 0; i < strlen(digitos_cvv); i++) {
            if (!isdigit(digitos_cvv[i])) {
                return 0;
            }
        }
    }
    
    return 1;
}

int cantidad_de_linea_anulacion(const char *archivo_path){
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