#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

#include "headers/transacion_compra.h"
#include "headers/imprimir_transacion.h"
#include "headers/cierre.h"
#include "headers/anulacion_tranferencia.h"
#include "headers/reportes_totales.h"

int validar_float(const char *entrada);

int main()
{
  

    int ESTAR = 1;
    short op;
    float precio;
    short salir;
    char id_buscar[4];
    char entrada[8];

    do
    {
        printf("---- Bienvenido a TU Tienda ------- \n\n"
            "Oprime (1): Para comprar.\n"
            "Oprime (2): Imprimir las compras.\n"
            "Oprime (3): Anular una transferencia.\n"
            "Oprime (4): Reportes totales.\n"
            "Oprime (5): Hacer un cierre\n"
            "Oprime (6): Salir del programa\n\n"

            "----------------------------------------\n\n");
            if(scanf("%hd", &op) != 1){
                printf("Entrada no válida. Inténtelo de nuevo.\n");
                while (getchar() != '\n'); 
                op = -1;
            }
        
        fflush(stdin);
        switch (op)
        {
        case 1:
            system("cls");
            printf("Escribe el precio a pagar\n");
            scanf("%s", entrada);
            fflush(stdin);

            if (validar_float(entrada)) {
                precio = atof(entrada);
                hacer_compra(precio); 
            } else {
                system("cls");
                printf("Entrada invalida.\n\nOprime una tecla para salir al menu");
                getch();
                

            }
            system("cls");
            
            break;

        case 2:
            system("cls");
            imprimir_transacciones();
            getch();
            system("cls");
            break;

        case 3:
            system("cls");
            printf("vas a anular una tranferencia: ingresa el id o codigo ");
            scanf("%s", id_buscar);
            anulacion(id_buscar);
            system("cls");
        break;

        case 4:
            reporte();
            system("cls");
        break;
        case 5:
            system("cls");
            do
            {
                printf("Seguro que deseas eliminar los datos? \n");

                printf("Escribe (1) Para hacer el cierre \nEscribe (2) Para no hacer el cierre. \n");
                scanf("%hd", &salir);

                if (salir == 1)
                {
                    system("cls");
                    printf("Vas a borrar los datos \n\n Oprime cualquier tecla para continuar");
                    getch();
                    realizar_cierre();
                }
                else if (salir == 2)
                {
                    printf("Bien hecho, sigue utilizando el programa. \n");
                }
                else
                {
                    printf("Colocaste un carácter incorrecto, intenta de nuevo.\n");
                }

                system("cls");
            } while (salir != 1 && salir != 2);
            break;

            case 6:
                ESTAR = 0;
                system("cls");
                printf("-------------------------\n");
                printf("La opcion es salir.\n\n Pulsa una tecla para salir de la aplicacion.\n", op);
                printf("-------------------------\n");
                getch();
            break;

        default:
            system("cls");
            printf("-------------------------\n");
            printf("La opcion no existe. (Por favor vuelve a introducir tu opcion) \n\n Pulsa una tecla para continuar.\n", op);
            printf("-------------------------\n");
            getch();

            system("cls");
            break;
        }
    } while (ESTAR == 1);

    return 0;
}

int validar_float(const char *entrada) {
    int i = 0, punto = 0;
    for (; entrada[i] != '\0'; i++) {
        if (entrada[i] == '.') {
            punto++; 
            if (punto > 1) return 0; 
        } else if (!isdigit(entrada[i])) {
            return 0; 
        }
        
    }
    

    return 1;

    return (i > 7 && punto <= 1); 
}