#include "Empleados.h"
#include "Productos.h"
#include "Pedido.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>


void menu (void);
int comprobarId (char id[5]);

void empleados(void) {

    //system("cls");

    fichero2 = fopen("EMPLEADOS.dat", "r+b");

    if (fichero2 == NULL) {
        fichero2 = fopen("EMPLEADOS.dat", "w+b");

        reg0Empleado.numRegEmpleado = 0;

        memset(&regEmpleado, '*', sizeof(regEmpleado));

        fseek(fichero2, 0, SEEK_SET);
        fwrite(&regEmpleado, sizeof(regEmpleado), 1, fichero2);
        fseek(fichero2, 0, SEEK_SET);
        fwrite(&reg0Empleado, sizeof(reg0Empleado), 1, fichero2);
    }

    fclose(fichero2);

}

void altaEmpleado (void)
{
    int i, desplazamiento, encontrado = 0, comprobar = 0;

    empleados();
    //system("cls");

    fichero2 = fopen ("EMPLEADOS.dat", "r+b");

    fseek(fichero2, 0, SEEK_SET);
    fread(&reg0Empleado, sizeof(reg0Empleado), 1, fichero2);


    for (i = 1; i <= reg0Empleado.numRegEmpleado; i++) {
        desplazamiento = i * sizeof(regEmpleado);
        fseek(fichero2, desplazamiento, SEEK_SET);
        fread(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

        if (strcmp("*", regEmpleado.idEmpleado) == 0) {
            fflush(stdin);
            printf("Introduce el codigo identificativo del empleado: ");
            gets(regEmpleado.idEmpleado);
            comprobar = comprobarId(regEmpleado.idEmpleado);
            if (comprobar == 0) {
                printf("\nCodigo incorrecto. Pulsa ENTER para volver al menu principal.");
                getch();
                menu();
            }
            printf("Introduce el nombre del empleado: ");
            gets(regEmpleado.nombreEmpleado);
            printf("Introduce el sueldo del empleado: ");
            scanf("%f", &regEmpleado.sueldo);
            printf("Introduce el numero de telefono del empleado: ");
            scanf("\n%d", &regEmpleado.telefono);
            getchar();

            fseek(fichero2, desplazamiento, SEEK_SET);
            fwrite(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

            encontrado = 1;
        }
    }
    if (!encontrado) {
        fflush(stdin);

        printf("Introduce el codigo identificativo del empleado: ");
        gets(regEmpleado.idEmpleado);
        comprobar = comprobarId(regEmpleado.idEmpleado);
        if (comprobar == 0) {
            printf("\nCodigo incorrecto. Pulsa ENTER para volver al menu principal.");
            getch();
            menu();
        }
        printf("Introduce el nombre del empleado: ");
        gets(regEmpleado.nombreEmpleado);
        printf("Introduce el sueldo del empleado: ");
        scanf("%f", &regEmpleado.sueldo);
        printf("Introduce el numero de telefono del empleado: ");
        scanf("\n%d", &regEmpleado.telefono);
        getchar();

        desplazamiento = (reg0Empleado.numRegEmpleado + 1) * sizeof(regEmpleado);
        fseek(fichero2, desplazamiento, SEEK_SET);
        fwrite(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

        reg0Empleado.numRegEmpleado++;
        fseek(fichero2, 0, SEEK_SET);
        fwrite(&reg0Empleado, sizeof(reg0Empleado), 1, fichero2);
    }

    fclose(fichero2);

    puts("Se ha aniadido el empleado con exito. Pulsa ENTER para volver al menu principal.");
    getchar();
    menu();
}

void listadoEmpleado (void)
{
    int i, desplazamiento;

    empleados();
    //system("cls");

    fichero2 = fopen("EMPLEADOS.dat", "rb");

    fseek(fichero2, 0, SEEK_SET);
    fread(&reg0Empleado, sizeof(reg0Empleado), 1, fichero2);


    for (i = 1; i <= reg0Empleado.numRegEmpleado; i++) {
        desplazamiento = i * sizeof(regEmpleado);
        fseek(fichero2, desplazamiento, SEEK_SET);
        fread(&regEmpleado, sizeof(regEmpleado), 1, fichero2);
        if (strcmp("*", regEmpleado.idEmpleado) != 0) {
            printf("Codigo empleado: %s", regEmpleado.idEmpleado);
            printf("\nNombre: %s", regEmpleado.nombreEmpleado);
            printf("\nSueldo: %.2f", regEmpleado.sueldo);
            printf("\nTelefono: %d", regEmpleado.telefono);
            printf("\n\n");
        }
    }
    fflush(stdin);

    fclose(fichero2);

    puts("Pulsa ENTER para volver al menu principal");
    getchar();

    menu();
}

void consultaEmpleado (void) {
    int i, encontrado = 0, desplazamiento;
    char codigo[5];

    empleados();

    //system("cls");

    fichero2 = fopen("EMPLEADOS.dat", "rb");

    fseek(fichero2, 0, SEEK_SET);
    fread(&reg0Empleado, sizeof(reg0Empleado), 1, fichero2);

    printf("Introduce el codigo del producto que buscas: ");
    gets(codigo);
    fflush(stdin);

    for (i = 1; i <= reg0Empleado.numRegEmpleado; i++) {
        desplazamiento = i * sizeof(regEmpleado);
        fseek(fichero2, desplazamiento, SEEK_SET);
        fread(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

        if (strcmp(codigo, regEmpleado.idEmpleado) == 0) {
            printf("Codigo empleado: %s", regEmpleado.idEmpleado);
            printf("\nNombre: %s", regEmpleado.nombreEmpleado);
            printf("\nSueldo: %.2f", regEmpleado.sueldo);
            printf("\nTelefono: %d", regEmpleado.telefono);
            printf("\n\n");

            encontrado = 1;
        }
    }

    fclose(fichero2);

    if (!encontrado)
        puts("No se ha encontrado ningun producto con ese codigo. Pulsa ENTER para volver al menu principal.");
    else
        puts("Pulsa ENTER para volver al menu principal.");

    fflush(stdin);
    menu();
}

void modificacionEmpleado (void) {
    int i, desplazamiento, encontrado = 0;
    char codigo[5];

    empleados();

    //system("cls");

    fichero2 = fopen("EMPLEADOS.dat", "r+b");

    fseek(fichero2, 0, SEEK_SET);
    fread(&reg0Empleado, sizeof(reg0Empleado), 1, fichero2);

    printf("Introduce el codigo del empleado que deseas modificar: ");
    gets(codigo);
    fflush(stdin);

    for (i = 1; i <= reg0Empleado.numRegEmpleado; i++) {
        desplazamiento = i * sizeof(regEmpleado);
        fseek(fichero2, desplazamiento, SEEK_SET);
        fread(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

        if (strcmp(codigo, regEmpleado.idEmpleado) == 0) {
            printf("Codigo empleado: %s", regEmpleado.idEmpleado);
            printf("\nNombre: %s", regEmpleado.nombreEmpleado);
            printf("\nSueldo: %.2f", regEmpleado.sueldo);
            printf("\nTelefono: %d", regEmpleado.telefono);
            printf("\n\n");

            encontrado = 1;

            fflush(stdin);
            printf("Modificando datos del empleado - %s", regEmpleado.idEmpleado);
            printf("Introduce el codigo identificativo del empleado: ");
            gets(regEmpleado.idEmpleado);
            printf("Introduce el nombre del empleado: ");
            gets(regEmpleado.nombreEmpleado);
            printf("Introduce el sueldo del empleado: ");
            scanf("%f", &regEmpleado.sueldo);
            printf("Introduce el numero de telefono del empleado: ");
            scanf("\n%d", &regEmpleado.telefono);
            fflush(stdin);

            fseek(fichero2, desplazamiento, SEEK_SET);
            fwrite(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

        }
    }

    fclose(fichero2);

    if (!encontrado)
        puts("No se ha encontrado ningun empleado con ese codigo. Pulsa ENTER para volver al menu.");
    else
        puts("La informacion se ha modificado correctamente. Pulsa ENTER para volver al menu principal.");

    fflush(stdin);
    menu();
}

//ORDENAR
void menuOrdenarEmpleado (void) {
    int eleccion;

    fflush(stdin);
    puts("\n\t**FORMAS DE ORDENAR A LOS EMPLEADOS**");
    puts("\n1.- Empleado segun su codigo.");
    puts("2.- Empleado segun su nombre.");
    puts("3.- Cancelar.");

    printf("\nSelecciona una opcion: ");
    scanf("%d", &eleccion);
    fflush(stdin);

    switch (eleccion) {
        case 1:
            ordenarEmpleadoIdEmp();
            break;
        case 2:
            ordenarEmpleadoNombre();
            break;
        default:
            menu();
    }
}

void ordenarEmpleadoIdEmp (void)
{
    Empleado aux;
    int i, desplazamiento;
    int n , d, hayCambios;

    empleados();

    fichero2 = fopen("EMPLEADOS.dat", "r+b");
    fseek(fichero2, 0L, 0);
    fread(&reg0Empleado, sizeof(reg0Empleado), 1, fichero2);

    n = reg0Empleado.numRegEmpleado;
    d = n;

    do {
        d = d / 2;

        do {
            hayCambios = 0;

            for (i = 1; i <= n - d; i++) {
                desplazamiento = i * sizeof(regEmpleado);
                fseek(fichero2, desplazamiento, 0);
                fread(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

                desplazamiento = (i + d) * sizeof(aux);
                fseek(fichero2, desplazamiento, 0);
                fread(&aux, sizeof(aux), 1, fichero2);
                if (strcmp(aux.idEmpleado, regEmpleado.idEmpleado) < 0) {
                    desplazamiento = i * sizeof(aux);
                    fseek(fichero2, desplazamiento, 0);
                    fwrite(&aux, sizeof(aux), 1, fichero2);

                    desplazamiento = (i + d) * sizeof(regEmpleado);
                    fseek(fichero2, desplazamiento, 0);
                    fwrite(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

                    printf ("\n\nFichero ordenado");
                    fflush(stdin);
                }
            }

        } while(hayCambios == 1);

    } while(d != 1);
    fflush(fichero2);
    fclose(fichero2);

    puts("Los empleados se han ordenado correctamente segun su codigo. Pulsa ENTER para volver al menu principal.");

    fflush(stdin);
    menu();
}

void ordenarEmpleadoNombre (void)
{
    Empleado aux;
    int i, desplazamiento;
    int n , d, hayCambios;

    empleados();

    fichero2 = fopen("EMPLEADOS.dat", "r+b");
    fseek(fichero2, 0L, 0);
    fread(&reg0Empleado, sizeof(reg0Empleado), 1, fichero2);
    n = reg0Empleado.numRegEmpleado;
    d = n;

    do {
        d = d / 2;

        do {
            hayCambios = 0;

            for (i = 1; i <= n - d; i++) {
                desplazamiento = i * sizeof(regEmpleado);
                fseek(fichero2, desplazamiento, 0);
                fread(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

                desplazamiento = (i + d) * sizeof(aux);
                fseek(fichero2, desplazamiento, 0);
                fread(&aux, sizeof(aux), 1, fichero2);
                if (strcmp(aux.nombreEmpleado, regEmpleado.nombreEmpleado) < 0) {
                    desplazamiento = i * sizeof(aux);
                    fseek(fichero2, desplazamiento, 0);
                    fwrite(&aux, sizeof(aux), 1, fichero2);

                    desplazamiento = (i + d) * sizeof(regEmpleado);
                    fseek(fichero2, desplazamiento, 0);
                    fwrite(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

                    printf ("\n\nFichero ordenado");
                    fflush(stdin);
                }
            }

        } while(hayCambios == 1);

    } while(d != 1);
    fflush(fichero2);
    fclose(fichero2);

    puts("Los empleados se han ordenado correctamente segun su nombre. Pulsa ENTER para volver al menu principal.");

    fflush(stdin);
    menu();
}

void bajasEmpleado (void) {
    int i, desplazamiento, encontrado = 0;
    char codigo[5];

    empleados();

    //system("cls");

    fichero2 = fopen("EMPLEADOS.dat", "r+b");

    fseek(fichero2, 0, SEEK_SET);
    fread(&reg0Empleado, sizeof(reg0Empleado), 1, fichero2);

    printf("Introduce el codigo del empleado que quieres dar de baja: ");
    gets(codigo);
    fflush(stdin);

    for (i = 1; i <= reg0Empleado.numRegEmpleado; i++) {
        desplazamiento = i * sizeof(regEmpleado);
        fseek(fichero2, desplazamiento, SEEK_SET);
        fread(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

        if (strcmp(codigo, regEmpleado.idEmpleado) == 0) {
            puts("Se van a dar de baja los datos del siguiente empleado: ");
            printf("Codigo empleado: %s", regEmpleado.idEmpleado);
            printf("Nombre empleado: %s", regEmpleado.nombreEmpleado);
            printf("\nSueldo: %.2f", regEmpleado.sueldo);
            printf("\nTelefono: %d", regEmpleado.telefono);
            printf("\n\n");

            encontrado = 1;

            strcpy(regEmpleado.idEmpleado, "*");

            fseek(fichero2, desplazamiento, SEEK_SET);
            fwrite(&regEmpleado, sizeof(regEmpleado), 1, fichero2);
        }
    }

    if (!encontrado)
        puts("No se ha encontrado ningun empleado con el codigo especificado. Pulsa ENTER para volver al menu.");
    else
        puts("Se ha dado de baja al empleado correctamente. Pulsa ENTER para volver al menu principal.");
    fflush(stdin);

    fclose(fichero2);

    menu();
}
