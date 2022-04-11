#include "Empleados.h"
#include "Productos.h"
#include "Pedido.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

void menu (void);
int comprobarId (char id[5]);


void pedidos(void) {

    //system("cls");

    fichero3 = fopen("PEDIDOS.dat", "r+b");

    if (fichero3 == NULL) {
        fichero3 = fopen("PEDIDOS.dat", "w+b");

        reg0Pedido.numRegPedido = 0;

        memset(&regPedido, '*', sizeof(regPedido));

        fseek(fichero3, 0, SEEK_SET);
        fwrite(&regPedido, sizeof(regPedido), 1, fichero3);
        fseek(fichero3, 0, SEEK_SET);
        fwrite(&reg0Pedido, sizeof(reg0Pedido), 1, fichero3);
    }

    fclose(fichero3);

}

void altaPedido (void)
{
    int i, j, k, desplazamiento, encontrado = 0, comprobar = 0;

    pedidos();
    //system("cls");

    fichero1 = fopen ("PRODUCTOS.dat", "r+b");
    fichero2 = fopen ("EMPLEADOS.dat", "r+b");
    fichero3 = fopen ("PEDIDOS.dat", "r+b");

    fseek(fichero1, 0, SEEK_SET);
    fread(&reg0Productos, sizeof(reg0Productos), 1, fichero1);

    fseek(fichero2, 0, SEEK_SET);
    fread(&reg0Empleado, sizeof(reg0Empleado), 1, fichero2);

    fseek(fichero3, 0, SEEK_SET);
    fread(&reg0Pedido, sizeof(reg0Pedido), 1, fichero3);


    for (i = 1; i <= reg0Pedido.numRegPedido; i++) {
        desplazamiento = i * sizeof(regPedido);
        fseek(fichero3, desplazamiento, SEEK_SET);
        fread(&regPedido, sizeof(regPedido), 1, fichero3);

        if (strcmp("*", regPedido.idPedido) == 0) {
            fflush(stdin);
            printf("\n\nIntroduce el codigo del pedido: ");
            gets(regPedido.idPedido);
            comprobar = comprobarId(regPedido.idPedido);
            if (comprobar == 0) {
                printf("\nCodigo incorrecto. Pulsa ENTER para volver al menu principal.");
                getch();
                menu();
            }
            printf("Introduce el codigo del producto para el pedido: ");
            gets(regPedido.idProducto);
            printf("Introduce el codigo del empleado que va a realizar el pedido: ");
            gets(regPedido.idEmpleado);
            printf("Introduce el numero de unidades que desea: ");
            scanf("\n%d", &regPedido.cantidadProductos);
            getchar();
            printf("Introduce la direccion: ");
            gets(regPedido.direccion);
            printf("Introduce la fecha en la que desea su peddido (DIA/MES/ANIO): ");
            gets(regPedido.fecha);
            printf("Introduce el numero de telefonoContacto del empleado: ");
            scanf("\n%d", &regPedido.telefonoContacto);
            printf("El total a pagar es: ");
            regPedido.precioTotalPedido = regPedido.cantidadProductos * regProducto.precio;
            printf("%.2f", regPedido.precioTotalPedido);

            getchar();

            for (j = 1; j <= reg0Empleado.numRegEmpleado; j++) {
                desplazamiento = j * sizeof(regEmpleado);
                fseek(fichero2, desplazamiento, SEEK_SET);
                fread(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

                if (strcmp(regProducto.idEmpleado, regEmpleado.idEmpleado) == 0) {

                    for (k = 1; k <= reg0Productos.numRegProd; k++) {
                        desplazamiento = k * sizeof(regProducto);
                        fseek(fichero1, desplazamiento, SEEK_SET);
                        fread(&regProducto, sizeof(regProducto), 1, fichero1);

                        if (strcmp(regPedido.idProducto, regProducto.idProducto) == 0) {
                            fseek(fichero3, desplazamiento, SEEK_SET);
                            fwrite(&regPedido, sizeof(regPedido), 1, fichero3);
                        } else {
                            printf("No existe el producto que ha introducido. \nOperacion cancelada.\nPulsa ENTER para volver al menu principal.");
                            getchar();
                            menu();
                        }
                    }
                } else {
                    printf("No existe el empleado que ha introducido. \nOperacion cancelada.\nPulsa ENTER para volver al menu principal.");
                    getchar();
                    menu();
                }
            }

            encontrado = 1;
        }
    }
    if (!encontrado) {
        fflush(stdin);
        printf("\n\nIntroduce el codigo del pedido: ");
        gets(regPedido.idPedido);
        comprobar = comprobarId(regPedido.idPedido);
        if (comprobar == 0) {
            printf("\nCodigo incorrecto. Pulsa ENTER para volver al menu principal.");
            getch();
            menu();
        }
        printf("Introduce el codigo del producto para el pedido: ");
        gets(regPedido.idProducto);
        printf("Introduce el codigo del empleado que va a realizar el pedido: ");
        gets(regPedido.idEmpleado);
        printf("Introduce el numero de unidades que desea: ");
        scanf("\n%d", &regPedido.cantidadProductos);
        getchar();
        printf("Introduce la direccion: ");
        gets(regPedido.direccion);
        printf("Introduce la fecha en la que desea su peddido (DIA/MES/ANIO): ");
        gets(regPedido.fecha);
        printf("Introduce el numero de telefonoContacto del empleado: ");
        scanf("\n%d", &regPedido.telefonoContacto);
        printf("El total a pagar es: ");
        regPedido.precioTotalPedido = regPedido.cantidadProductos; //*regProductos.precio
        printf("%.2f", regPedido.precioTotalPedido);
        getchar();

        for (j = 1; j <= reg0Empleado.numRegEmpleado; j++) {
            desplazamiento = j * sizeof(regEmpleado);
            fseek(fichero2, desplazamiento, SEEK_SET);
            fread(&regEmpleado, sizeof(regEmpleado), 1, fichero2);

            if (strcmp(regProducto.idEmpleado, regEmpleado.idEmpleado) == 0) {

                for (k = 1; k <= reg0Productos.numRegProd; k++) {
                    desplazamiento = k * sizeof(regProducto);
                    fseek(fichero1, desplazamiento, SEEK_SET);
                    fread(&regProducto, sizeof(regProducto), 1, fichero1);

                    if (strcmp(regPedido.idProducto, regProducto.idProducto) == 0) {
                        fseek(fichero3, desplazamiento, SEEK_SET);
                        fwrite(&regPedido, sizeof(regPedido), 1, fichero3);

                    } else {
                        printf("\nNo existe el producto que ha introducido. \nOperacion cancelada.\nPulsa ENTER para volver al menu principal.");
                        getchar();
                        menu();
                    }
                }
            } else {
                printf("\nNo existe el empleado que ha introducido. \nOperacion cancelada.\nPulsa ENTER para volver al menu principal.");
                getchar();
                menu();
            }
        }
    }

    fclose(fichero1);
    fclose(fichero2);
    fclose(fichero3);

    puts("\nSe ha realizado correctamente el pedido. Pulsa ENTER para volver al menu principal.");
    getchar();
    menu();
}

void listadoPedido (void)
{
    int i, desplazamiento;

    //pedidos();

    //system("cls");
    fichero1 = fopen ("PRODUCTOS.dat", "r+b");
    fichero2 = fopen("EMPLEADOS.dat", "r+b");
    fichero3 = fopen("PEDIDOS.dat", "rb");

    fseek(fichero3, 0, SEEK_SET);
    fread(&reg0Pedido, sizeof(reg0Pedido), 1, fichero3);


    for (i = 1; i <= reg0Pedido.numRegPedido; i++) {
        desplazamiento = i * sizeof(regPedido);
        fseek(fichero3, desplazamiento, SEEK_SET);
        fread(&regPedido, sizeof(regPedido), 1, fichero3);
        if (strcmp("*", regPedido.idPedido) != 0) {
            printf("\nCodigo pedido: %s", regPedido.idPedido);
            //printf("Nombre producto: %s", regProducto.nombreProducto);
            //printf("Nombre repartidor: %s", regEmpleado.nombreEmpleado);
            printf("\nUnidades pedidas: %d", regPedido.cantidadProductos);
            printf("\nDireccion: %s", regPedido.direccion);
            printf("\nFecha: %s", regPedido.fecha);
            printf("\nTelefono: %d", regPedido.telefonoContacto);
            printf("\nTotal compra: %.2f", regPedido.precioTotalPedido);
            printf("\n\n");
        }
    }

    fclose(fichero1);
    fclose(fichero2);
    fclose(fichero3);

    puts("Pulsa ENTER para volver al menu principal");
    getchar();
    menu();
}

void consultaPedido (void) {
    int i, encontrado = 0, desplazamiento;
    char codigo[5];

    //pedidos();

    //system("cls");
    fichero1 = fopen ("PRODUCTOS.dat", "r+b");
    fichero2 = fopen("EMPLEADOS.dat", "r+b");
    fichero3 = fopen("PEDIDOS.dat", "rb");

    fseek(fichero3, 0, SEEK_SET);
    fread(&reg0Pedido, sizeof(reg0Pedido), 1, fichero3);

    printf("Introduce el codigo del pedido que buscas: ");
    gets(codigo);
    getchar();

    for (i = 1; i <= reg0Pedido.numRegPedido; i++) {
        desplazamiento = i * sizeof(regPedido);
        fseek(fichero3, desplazamiento, SEEK_SET);
        fread(&regPedido, sizeof(regPedido), 1, fichero3);

        if (strcmp(codigo, regPedido.idPedido) == 0) {
            printf("Codigo pedido: %s", regPedido.idPedido);
            //printf("Nombre producto: %s", regProducto.nombreProducto);
            //printf("Nombre repartidor: %s", regEmpleado.nombreEmpleado);
            printf("\nUnidades pedidas: %d", regPedido.cantidadProductos);
            printf("\nDireccion: %s", regPedido.direccion);
            printf("\nFecha: %s", regPedido.fecha);
            printf("\nTelefono: %d", regPedido.telefonoContacto);
            printf("\nTotal compra: %.2f", regPedido.precioTotalPedido);
            printf("\n\n");

            encontrado = 1;
        }
    }

    fclose(fichero1);
    fclose(fichero2);
    fclose(fichero3);

    if (!encontrado)
        puts("No se ha encontrado ningun pedido con ese codigo. Pulsa ENTER para volver al menu principal.");
    else
        puts("Pulsa ENTER para volver al menu principal.");

    getchar();
    menu();
}

void modificacionPedido (void) {
    int i, desplazamiento, encontrado = 0;
    char codigo[5];

    //pedidos();

    //system("cls");
    fichero1 = fopen ("PRODUCTOS.dat", "r+b");
    fichero2 = fopen("EMPLEADOS.dat", "r+b");
    fichero3 = fopen("PEDIDOS.dat", "r+b");

    fseek(fichero3, 0, SEEK_SET);
    fread(&reg0Pedido, sizeof(reg0Pedido), 1, fichero3);

    printf("Introduce el codigo del pedido que deseas modificar: ");
    gets(codigo);
    fflush(stdin);

    for (i = 1; i <= reg0Pedido.numRegPedido; i++) {
        desplazamiento = i * sizeof(regPedido);
        fseek(fichero3, desplazamiento, SEEK_SET);
        fread(&regPedido, sizeof(regPedido), 1, fichero3);

        if (strcmp(codigo, regPedido.idPedido) == 0) {
            printf("Codigo pedido: %s", regPedido.idPedido);
           // printf("Nombre producto: %s", regProducto.nombreProducto);
            //printf("Nombre repartidor: %s", regEmpleado.nombreEmpleado);
            printf("\nUnidades pedidas: %d", regPedido.cantidadProductos);
            printf("\nDireccion: %s", regPedido.direccion);
            printf("\nFecha: %s", regPedido.fecha);
            printf("\nTelefono: %d", regPedido.telefonoContacto);
            printf("\nTotal compra: %.2f", regPedido.precioTotalPedido);
            printf("\n\n");

            encontrado = 1;
            fflush(stdin);
            printf("\n\n\t**Modificando datos del pedido - %s**", regPedido.idPedido);
            printf("Introduce el codigo del pedido: ");
            gets(regPedido.idPedido);
            printf("Introduce el codigo del producto para el pedido: ");
            gets(regPedido.idProducto);
            printf("Introduce el codigo del empleado que va a realizar el pedido: ");
            gets(regPedido.idEmpleado);
            printf("Introduce el numero de unidades que desea: ");
            scanf("\n%d", &regPedido.cantidadProductos);
            printf("Introduce la direccion: ");
            gets(regPedido.direccion);
            printf("Introduce la fecha en la que desea su peddido (DIA/MES/ANIO): ");
            gets(regPedido.fecha);
            printf("Introduce el numero de telefonoContacto del empleado: ");
            scanf("\n%d", &regPedido.telefonoContacto);
            printf("El total a pagar es: ");
            regPedido.precioTotalPedido = regPedido.cantidadProductos;
            printf("%.2f", regPedido.precioTotalPedido);
            getchar();

            fseek(fichero3, desplazamiento, SEEK_SET);
            fwrite(&regPedido, sizeof(regPedido), 1, fichero3);

        }
    }

    fclose(fichero1);
    fclose(fichero2);
    fclose(fichero3);

    if (!encontrado)
        puts("No se ha encontrado ningun pedido con ese codigo. Pulsa ENTER para volver al menu.");
    else
        puts("El pedido se ha modificado correctamente. Pulsa ENTER para volver al menu principal.");

    getchar();
    menu();
}

//ORDENAR
void menuOrdenarPedido (void) {
    int eleccion;

    puts("\n\t**FORMAS DE ORDENAR LOS PEDIDOS**");
    puts("\n1.- Pedido segun su codigo.");
    puts("2.- Pedido segun la fecha.");
    puts("3.- Cancelar.");

    printf("\nSelecciona una opcion: ");
    scanf("%d", &eleccion);

    switch (eleccion) {
        case 1:
            ordenarPedidoId();
            break;
        case 2:
            ordenarPedidoFecha();
            break;
        default:
            menu();
    }
}

void ordenarPedidoId (void)
{
    Pedido aux;
    int i, desplazamiento;
    int n , d, hayCambios;

    //pedidos();

    fichero3 = fopen("PEDIDOS.dat", "r+b");
    fseek(fichero3, 0L, 0);
    fread(&reg0Pedido, sizeof(reg0Pedido), 1, fichero3);

    n = reg0Pedido.numRegPedido;
    d = n;

    do {
        d = d / 2;

        do {
            hayCambios = 0;

            for (i = 1; i <= n - d; i++) {
                desplazamiento = i * sizeof(regPedido);
                fseek(fichero3, desplazamiento, 0);
                fread(&regPedido, sizeof(regPedido), 1, fichero3);

                desplazamiento = (i + d) * sizeof(aux);
                fseek(fichero3, desplazamiento, 0);
                fread(&aux, sizeof(aux), 1, fichero3);
                if (strcmp(aux.idPedido, regPedido.idPedido) < 0) {
                    desplazamiento = i * sizeof(aux);
                    fseek(fichero3, desplazamiento, 0);
                    fwrite(&aux, sizeof(aux), 1, fichero3);

                    desplazamiento = (i + d) * sizeof(regPedido);
                    fseek(fichero3, desplazamiento, 0);
                    fwrite(&regPedido, sizeof(regPedido), 1, fichero3);

                    printf("\n\nFichero ordenado");
                }
            }

        } while(hayCambios == 1);

    } while(d != 1);

    fflush(fichero3);
    fclose(fichero3);

    puts("Los pedidos se han ordenado correctamente segun su codigo. Pulsa ENTER para volver al menu principal.");

    getchar();
    menu();
}

void ordenarPedidoFecha (void)
{
    Pedido aux;
    FILE *fichero3;
    int i, desplazamiento;

    //pedidos();

    fichero3 = fopen("PEDIDOS.dat", "r+b");
    fseek(fichero3, 0L, 0);
    fread(&reg0Pedido, sizeof(reg0Pedido), 1, fichero3);
    int n , d, hayCambios;
    n = reg0Pedido.numRegPedido;
    d = n;

    do {
        d = d / 2;

        do {
            hayCambios = 0;

            for (i = 1; i <= n - d; i++) {
                desplazamiento = i * sizeof(regPedido);
                fseek(fichero3, desplazamiento, 0);
                fread(&regPedido, sizeof(regPedido), 1, fichero3);

                desplazamiento = (i + d) * sizeof(aux);
                fseek(fichero3, desplazamiento, 0);
                fread(&aux, sizeof(aux), 1, fichero3);
                if (strcmp(aux.fecha, regPedido.fecha) < 0) {
                    desplazamiento = i * sizeof(aux);
                    fseek(fichero3, desplazamiento, 0);
                    fwrite(&aux, sizeof(aux), 1, fichero3);

                    desplazamiento = (i + d) * sizeof(regPedido);
                    fseek(fichero3, desplazamiento, 0);
                    fwrite(&regPedido, sizeof(regPedido), 1, fichero3);

                    printf("\n\nFichero ordenado");
                }
            }

        } while(hayCambios == 1);

    } while(d != 1);

    fflush(fichero3);
    fclose(fichero3);

    puts("Los pedidos se han ordenado correctamente segun la fecha de envio. Pulsa ENTER para volver al menu principal.");

    getchar();
    menu();
}

void bajasPedido (void) {
    int i, desplazamiento, encontrado = 0;
    char codigo[5];

    //pedidos();

    //system("cls");

    fichero3 = fopen("PEDIDOS.dat", "r+b");

    fseek(fichero3, 0, SEEK_SET);
    fread(&reg0Pedido, sizeof(reg0Pedido), 1, fichero3);

    printf("Introduce el codigo del pedido que quieres cancelar: ");
    gets(codigo);
    getchar();

    for (i = 1; i <= reg0Pedido.numRegPedido; i++) {
        desplazamiento = i * sizeof(regPedido);
        fseek(fichero3, desplazamiento, SEEK_SET);
        fread(&regPedido, sizeof(regPedido), 1, fichero3);

        if (strcmp(codigo, regPedido.idPedido) == 0) {
            puts("\n**Se van a cancelar los datos del siguiente pedido: ");
            printf("Codigo pedido: %s", regPedido.idPedido);
            printf("Nombre producto: %s", regProducto.nombreProducto);
            printf("Nombre repartidor: %s", regEmpleado.nombreEmpleado);
            printf("\nUnidades pedidas: %d", regPedido.cantidadProductos);
            printf("\nDireccion: %s", regPedido.direccion);
            printf("\nFecha: %s", regPedido.fecha);
            printf("\nTelefono: %d", regPedido.telefonoContacto);
            printf("\nTotal compra: %.2f", regPedido.precioTotalPedido);
            printf("\n\n");

            encontrado = 1;

            strcpy(regPedido.idPedido, "*");

            fseek(fichero3, desplazamiento, SEEK_SET);
            fwrite(&regPedido, sizeof(regPedido), 1, fichero3);
        }
    }

    if (!encontrado)
        puts("No se ha encontrado ningun pedido con el codigo especificado. Pulsa ENTER para volver al menu.");
    else
        puts("Se ha dado cancelado el pedido correctamente. Pulsa ENTER para volver al menu principal.");

    fclose(fichero3);

    getchar();
    menu();
}
