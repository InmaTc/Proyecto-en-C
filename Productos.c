#include "Empleados.h"
#include "Pedido.h"
#include "Productos.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

void menu (void);
int comprobarId (char id[5]);


void productos(void) {

    //system("cls");

    fichero1 = fopen("PRODUCTOS.dat", "r+b");

    if (fichero1 == NULL) {
        fichero1 = fopen("PRODUCTOS.dat", "w+b");

        reg0Productos.numRegProd = 0;

        memset(&regProducto, '*', sizeof(regProducto));

        fseek(fichero1, 0, SEEK_SET);
        fwrite(&regProducto, sizeof(regProducto), 1, fichero1);
        fseek(fichero1, 0, SEEK_SET);
        fwrite(&reg0Productos, sizeof(reg0Productos), 1, fichero1);
    }

    fclose(fichero1);
}

void altaProducto (void)
{
    int i, j, desplazamiento, encontrado = 0, comprobar = 0;

    productos();
    //system("cls");
    getchar();

    fichero1 = fopen ("PRODUCTOS.dat", "r+b");
    fichero2 = fopen ("EMPLEADOS.dat", "r+b");

    fseek(fichero1, 0, SEEK_SET);
    fread(&reg0Productos, sizeof(reg0Productos), 1, fichero1);

    fseek(fichero2, 0, SEEK_SET);
    fread(&reg0Empleado, sizeof(reg0Empleado), 1, fichero2);

    for (i = 1; i <= reg0Productos.numRegProd; i++) {
        desplazamiento = i * sizeof(Producto);
        fseek(fichero1, desplazamiento, SEEK_SET);
        fread(&regProducto, sizeof(regProducto), 1, fichero1);

        if (strcmp("*", regProducto.idProducto) == 0) {
            fflush(stdin);
            printf("Introduce el codigo del producto: ");
            gets(regProducto.idProducto);
            comprobar = comprobarId(regProducto.idProducto);
            if (comprobar == 0) {
                printf("\nCodigo incorrecto. Pulsa ENTER para volver al menu principal.");
                getch();
                menu();
            }
            printf("Introduce el codigo del empleado que lo ha elaborado: ");
            gets(regProducto.idEmpleado);
            printf("%s", regProducto.idEmpleado);
            printf("Introduce el nombre del producto: ");
            gets(regProducto.nombreProducto);
            printf("Introduce el precio del producto: ");
            scanf("%f", &regProducto.precio);
            printf("Introduce las stock del producto: ");
            scanf("\n%d", &regProducto.stock);
            printf("Introduce '0' si es con gluten o '1' si es sin gluten: ");
            scanf("\n%d", &regProducto.sinGluten);
            getchar();

            for (j = 1; j <= reg0Empleado.numRegEmpleado; j++) {
                desplazamiento = j * sizeof(Empleado);
                fseek(fichero2, desplazamiento, SEEK_SET);
                fread(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

                if (strcmp(regProducto.idEmpleado, regEmpleado.idEmpleado) == 0) {
                    fseek(fichero1, desplazamiento, SEEK_SET);
                    fwrite(&regProducto, sizeof(regProducto), 1, fichero1);
                } else {
                    printf("No existe el empleado que ha introducido. \nOperacion cancelada.\nPulsa una tecla para volver al menu principal.");
                    getchar();
                    menu();
                }
            }

            encontrado = 1;
        }
    }
    if (!encontrado) {
        fflush(stdin);
        printf("Introduce el codigo del producto: ");
        gets(regProducto.idProducto);
        comprobar = comprobarId(regProducto.idProducto);
        if (comprobar == 0) {
            printf("\nCodigo incorrecto. Pulsa ENTER para volver al menu principal.");
            getch();
            menu();
        }
        printf("Introduce el codigo del empleado que lo ha elaborado: ");
        gets(regProducto.idEmpleado);
        printf("Introduce el nombre del producto: ");
        gets(regProducto.nombreProducto);
        printf("Introduce el precio del producto: ");
        scanf("%f", &regProducto.precio);
        printf("Introduce las stock del producto: ");
        scanf("\n%d", &regProducto.stock);
        printf("Introduce '0' si es con gluten o '1' si es sin gluten: ");
        scanf("\n%d", &regProducto.sinGluten);
        getchar();

        for (j = 1; j <= reg0Empleado.numRegEmpleado; j++) {
            desplazamiento = j * sizeof(regEmpleado);
            fseek(fichero2, desplazamiento, SEEK_SET);
            fread(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

            if (strcmp(regProducto.idEmpleado, regEmpleado.idEmpleado) == 0) {
                desplazamiento = (reg0Productos.numRegProd + 1) * sizeof(regProducto);
                fseek(fichero1, desplazamiento, SEEK_SET);
                fwrite(&regProducto, sizeof(regProducto), 1, fichero1);

                reg0Productos.numRegProd++;
                fseek(fichero1, 0, SEEK_SET);
                fwrite(&reg0Productos, sizeof(reg0Productos), 1, fichero1);

            } else {
                printf("No existe el empleado que ha introducido. \nOperacion cancelada.\nPulsa una tecla para volver al menu principal.");
                getchar();
                menu();
            }
        }
    }

    fclose(fichero1);
    fclose(fichero2);

    fflush(stdin);
    puts("Se ha aniadido el producto con exito. Pulsa ENTER para volver al menu principal.");
    getchar();

    menu();
}

void listadoProducto (void)
{
    int i, desplazamiento;

    //productos();

    //system("cls");

    fichero1 = fopen("PRODUCTOS.dat", "rb");

    fseek(fichero1, 0, SEEK_SET);
    fread(&reg0Productos, sizeof(reg0Productos), 1, fichero1);


    for (i = 1; i <= reg0Productos.numRegProd; i++) {
        desplazamiento = i * sizeof(regProducto);
        fseek(fichero1, desplazamiento, SEEK_SET);
        fread(&regProducto, sizeof(regProducto), 1, fichero1);
        if (strcmp("*", regProducto.idProducto) != 0) {
            printf("Codigo producto: %s", regProducto.idProducto);
            printf("\nCodigo empleado: %s", regProducto.idEmpleado);
            printf("\nNombre: %s", regProducto.nombreProducto);
            printf("\nPrecio: %.2f", regProducto.precio);
            printf("\nStock: %d", regProducto.stock);
            if (regProducto.sinGluten == 1)
                printf("\nProducto sin gluten");
            printf("\n\n");
        }
    }

    fclose(fichero1);
    fflush(stdin);
    puts("Pulsa ENTER para volver al menu principal");
    getchar();
    menu();
}

void consultaProducto (void) {
    int i, encontrado = 0, desplazamiento;
    char codigo[5];

    productos();

    //system("cls");

    fichero1 = fopen("PRODUCTOS.dat", "rb");

    fseek(fichero1, 0, SEEK_SET);
    fread(&reg0Productos, sizeof(reg0Productos), 1, fichero1);

    printf("Introduce el codigo del producto que buscas: ");
    gets(codigo);
    getchar();

    for (i = 1; i <= reg0Productos.numRegProd; i++) {
        desplazamiento = i * sizeof(regProducto);
        fseek(fichero1, desplazamiento, SEEK_SET);
        fread(&regProducto, sizeof(regProducto), 1, fichero1);

        if (strcmp(codigo, regProducto.idProducto) == 0) {
            printf("Codigo producto: %s", regProducto.idProducto);
            printf("Codigo empleado: %s", regProducto.idEmpleado);
            printf("\nNombre: %s", regProducto.nombreProducto);
            printf("\nPrecio: %.2f", regProducto.precio);
            printf("\nStock: %d", regProducto.stock);
            if (regProducto.sinGluten == 1)
                printf("\nProducto sin gluten");
            printf("\n\n");

            encontrado = 1;
        }
    }

    fclose(fichero1);

    if (!encontrado)
        puts("No se ha encontrado ningun producto con ese codigo. Pulsa ENTER para volver al menu principal.");

    else
        puts("Pulsa ENTER para volver al menu principal.");

    getchar();
    menu();
}

void modificacionProducto (void) {
    int i, desplazamiento, encontrado = 0;
    char codigo[5];

    productos();

    //system("cls");

    fichero1 = fopen("PRODUCTOS.dat", "r+b");

    fseek(fichero1, 0, SEEK_SET);
    fread(&reg0Productos, sizeof(reg0Productos), 1, fichero1);

    printf("Introduce el codigo del producto que deseas modificar: ");
    gets(codigo);
    getchar();

    for (i = 1; i <= reg0Productos.numRegProd; i++) {
        desplazamiento = i * sizeof(regProducto);
        fseek(fichero1, desplazamiento, SEEK_SET);
        fread(&regProducto, sizeof(regProducto), 1, fichero1);

        if (strcmp(codigo, regProducto.idProducto) == 0) {
            printf("Codigo producto: %s", regProducto.idProducto);
            printf("Codigo empleado: %s", regProducto.idEmpleado);
            printf("\nPrecio: %.2f", regProducto.precio);
            printf("\nExistencias: %d", regProducto.stock);
            if (regProducto.sinGluten == 1)
                printf("\nProducto sin gluten");
            printf("\n\n");

            encontrado = 1;

            printf("\n\t**Modificando datos del producto - %s**", codigo);
            fflush(stdin);
            puts("Por favor, introduce los nuevos datos sobre el producto: ");
            printf("\nIntroduce el nuevo codigo del producto: ");
            gets(regProducto.idProducto);
            printf("Introduce el codigo del empleado que lo ha elaborado: ");
            gets(regProducto.idEmpleado);
            printf("Introduce el nuevo nombre del producto: ");
            gets(regProducto.nombreProducto);
            printf("Introduce el nuevo precio del producto: ");
            scanf("%f", &regProducto.precio);
            printf("Introduce el nuevo numero de stock del producto: ");
            scanf("\n%d", &regProducto.stock);
            printf("Introduce '0' si es con gluten o '1' si es sin gluten: ");
            scanf("\n%d", &regProducto.sinGluten);

            fseek(fichero1, desplazamiento, SEEK_SET);
            fwrite(&regProducto, sizeof(regProducto), 1, fichero1);

        }
    }

    fclose(fichero1);

    if (!encontrado)
        puts("No se ha encontrado ningun producto con ese codigo. Pulsa ENTER para volver al menu.");
    else
        puts("La informacion se ha modificado correctamente. Pulsa ENTER para volver al menu principal.");

    getchar();
    menu();
}

//ORDENAR
void menuOrdenarProducto (void) {
    int eleccion;

    printf("\n\t**FORMAS DE ORDENAR LOS PRODUCTOS**");
    printf("\n1.- Producto segun su codigo.");
    printf("2.- Producto segun su nombre.");
    printf("3.- Cancelar.");

    printf("\nSelecciona una opcion: ");
    scanf("%d", &eleccion);

    switch (eleccion) {
        case 1:
            ordenarProductoIdProducto();
            break;
        case 2:
            ordenarProductoNombreProd();
            break;
        default:
            menu();
    }
}

void ordenarProductoIdProducto (void)
{
    Producto aux;
    int i, desplazamiento;
    int n , d, hayCambios;

    productos();

    fichero1 = fopen("PRODUCTOS.dat","r+b");
    fseek(fichero1,0L,0);
    fread(&reg0Productos, sizeof(reg0Productos), 1, fichero1);

    n = reg0Productos.numRegProd;
    d = n;

    do {
        d = d / 2;

        do {
            hayCambios = 0;

            for (i = 1; i <= n - d; i++) {
                desplazamiento = i * sizeof(regProducto);
                fseek(fichero1,desplazamiento,0);
                fread(&regProducto,sizeof(regProducto),1,fichero1);

                desplazamiento = (i + d) * sizeof(aux);
                fseek(fichero1,desplazamiento,0);
                fread(&aux,sizeof(aux),1,fichero1);
                if (strcmp(aux.idProducto,regProducto.idProducto) < 0) {
                    desplazamiento = i * sizeof(aux);
                    fseek(fichero1,desplazamiento,0);
                    fwrite(&aux,sizeof(aux),1,fichero1);

                    desplazamiento = (i + d) * sizeof(regProducto);
                    fseek(fichero1,desplazamiento,0);
                    fwrite(&regProducto,sizeof(regProducto),1,fichero1);

                    printf ("\n\nFichero ordenado");
                }
            }

        } while(hayCambios == 1);

    } while(d != 1);

    fflush(fichero1);
    fclose(fichero1);

    fflush(stdin);
    puts("Los productos se ha ordenado correctamente segun su codigo. Pulsa ENTER para volver al menu principal.");
    getchar();
    menu();
}

void ordenarProductoNombreProd (void)
{
    Producto aux;
    int i, desplazamiento;
    int n , d, hayCambios;

    productos();

    fichero1 = fopen("PRODUCTOS.dat","r+b");
    fseek(fichero1,0L,0);
    fread(&reg0Productos, sizeof(reg0Productos), 1, fichero1);

    n = reg0Productos.numRegProd;
    d = n;

    do {
        d = d / 2;

        do {
            hayCambios = 0;

            for (i = 1; i <= n - d; i++) {
                desplazamiento = i * sizeof(regProducto);
                fseek(fichero1,desplazamiento,0);
                fread(&regProducto,sizeof(regProducto),1,fichero1);

                desplazamiento = (i + d) * sizeof(aux);
                fseek(fichero1,desplazamiento,0);
                fread(&aux,sizeof(aux),1,fichero1);
                if (strcmp(aux.nombreProducto,regProducto.nombreProducto) < 0) {
                    desplazamiento = i * sizeof(aux);
                    fseek(fichero1,desplazamiento,0);
                    fwrite(&aux,sizeof(aux),1,fichero1);

                    desplazamiento = (i + d) * sizeof(regProducto);
                    fseek(fichero1,desplazamiento,0);
                    fwrite(&regProducto,sizeof(regProducto),1,fichero1);

                    printf ("\n\nFichero ordenado");
                }
            }

        } while(hayCambios == 1);

    } while(d != 1);
    fflush(fichero1);
    fclose(fichero1);
    fflush(stdin);
    puts("Los productos se ha ordenado correctamente segun su nombre. Pulsa ENTER para volver al menu principal.");

    getchar();
    menu();
}

void bajasProducto (void) {
    int i, desplazamiento, encontrado = 0;
    char codigo[5];

    productos();

    //system("cls");

    fichero1 = fopen("PRODUCTOS.dat", "r+b");

    fseek(fichero1, 0, SEEK_SET);
    fread(&reg0Productos, sizeof(reg0Productos), 1, fichero1);

    printf("Introduce el codigo del producto que quieres dar de baja: ");
    gets(codigo);
    getchar();

    for (i = 1; i <= reg0Productos.numRegProd; i++) {
        desplazamiento = i * sizeof(regProducto);
        fseek(fichero1, desplazamiento, SEEK_SET);
        fread(&regProducto, sizeof(regProducto), 1, fichero1);

        if (strcmp(codigo, regProducto.idProducto) == 0) {
            puts("Se van a dar de baja los datos del siguiente producto: ");
            printf("Codigo producto: %s", regProducto.idProducto);
            printf("Codigo empleado: %s", regProducto.idEmpleado);
            printf("\nPrecio: %.2f", regProducto.precio);
            printf("\nStock: %d", regProducto.stock);
            if (regProducto.sinGluten == 1)
                printf("\nProducto sin gluten");
            printf("\n\n");

            encontrado = 1;

            strcpy(regProducto.idProducto, "*");

            fseek(fichero1, desplazamiento, SEEK_SET);
            fwrite(&regProducto, sizeof(regProducto), 1, fichero1);
        }
    }

    if (!encontrado)
        puts("No se ha encontrado ningun producto con el codigo especificado. Pulsa ENTER para volver al menu.");
    else
        puts("Se ha dado de baja el producto correctamente. Pulsa ENTER para volver al menu principal.");

    fclose(fichero1);

    getchar();
    menu();
}
