#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Empleados.h"
#include "Productos.h"
#include "Pedido.h"


void menu();
void alta (void);
void listado (void);
void consulta (void);
void modificacion (void);
void ordenar (void);
void bajas (void);
int comprobarId (char id[5]);

int main() {
/*
    printf ("\n\n\tProductos --> %i - %i",sizeof(regProducto),sizeof(reg0Productos));
    printf ("\n\n\tEmpleados -->%i - %i",sizeof(regEmpleado),sizeof(reg0Empleado));
    printf ("\n\n\tPedidos -->%i - %i",sizeof(regPedido),sizeof(reg0Pedido));
*/
   //Menú inicial
    //system("cls");

    printf ("\n\n\t**Proyecto programacion en C**\n\n\t**Realizado por: Inmaculada Talavera Campos** \n\nPulsa una tecla para comenzar => ");
    getchar();
    menu();

    return 0;
}
void menu () {
    int eleccion;

    //Menú principal
   // system("cls");

    puts("\n\t**Bienvenido a la base de datos de nuestra Confiteria**");
    puts("\n\t**MENU**");
    puts("\n1.- Alta.");
    puts("2.- Listado.");
    puts("3.- Consulta.");
    puts("4.- Modificaciones.");
    puts("5.- Ordenar.");
    puts("6.- Baja.");
    puts("7.- Salir de la aplicacion");

    printf("\nSelecciona una opcion: ");
    scanf("%d", &eleccion);
    //fflush(stdin);

    switch (eleccion) {
        case 1:
            alta();
            break;
        case 2:
            listado();
            break;
        case 3:
            consulta();
            break;
        case 4:
            modificacion();
            break;
        case 5:
            ordenar();
            break;
        case 6:
            bajas();
            break;
        default: exit(1);
    }
}
void alta (void){
    int eleccion;

    //system("cls");

    puts("\n\t**MENU ALTAS**");
    puts("\nElige sobre que elemento quieres hacer el alta.");
    puts("1.- Producto.");
    puts("2.- Empleado.");
    puts("3.- Pedido.");
    puts("4.- Cancelar.");

    printf("\nSelecciona una opcion: ");
    scanf("%d", &eleccion);
    //getchar();

    switch (eleccion) {
        case 1: altaProducto();
            break;
        case 2: altaEmpleado();
            break;
        case 3: altaPedido();
            break;
        default: menu();
    }
}

void listado (void){
    int eleccion;

    //system("cls");

    puts("\n\t**MENU LISTADO**");
    puts("\nElige sobre que elemento quieres hacer el listado.");
    puts("1.- Producto.");
    puts("2.- Empleado.");
    puts("3.- Pedido.");
    puts("4.- Cancelar.");

    printf("\nSelecciona una opcion: ");
    scanf("%d", &eleccion);
    //fflush(stdin);

    switch (eleccion) {
        case 1: listadoProducto();
            break;
        case 2: listadoEmpleado();
            break;
        case 3: listadoPedido();
            break;
        default: menu();
    }
}

void consulta (void){
    int eleccion;

    //system("cls");

    printf("\nSelecciona una opcion: ");
    scanf("%d", &eleccion);
    //fflush(stdin);

    puts("\n\t**MENU CONSULTA**");
    puts("\nElige sobre que elemento quieres hacer la consultaProducto.");
    puts("1.- Producto.");
    puts("2.- Empleado.");
    puts("3.- Pedido.");
    puts("4.- Cancelar.");

    switch (eleccion) {
        case 1: consultaProducto();
            break;
        case 2: consultaEmpleado();
            break;
        case 3: consultaPedido();
            break;
        default: menu();
    }
}

void modificacion (void){
    int eleccion;

    //system("cls");
    printf("\nSelecciona una opcion: ");
    scanf("%d", &eleccion);
    //getchar();

    puts("\n\t**MENU MODIFICACIONES**");
    puts("\nElige sobre que elemento quieres hacer la modificacionProducto.");
    puts("1.- Producto.");
    puts("2.- Empleado.");
    puts("3.- Pedido.");
    puts("4.- Cancelar.");

    switch (eleccion) {
        case 1: modificacionProducto();
            break;
        case 2: modificacionEmpleado();
            break;
        case 3: modificacionPedido();
            break;
        default: menu();
    }
}

void ordenar (void){
    int eleccion;

      //system("cls");
      printf("\nSelecciona una opcion: ");
      scanf("%d", &eleccion);
      //getchar();

      puts("\n\t**MENU ORDENAR**");
      puts("\nElige sobre que elemento quieres ordenarProducto.");
      puts("1.- Producto.");
      puts("2.- Empleado.");
      puts("3.- Pedido.");
      puts("4.- Cancelar.");

      switch (eleccion) {
          case 1: menuOrdenarProducto();
              break;
          case 2: menuOrdenarEmpleado();
              break;
          case 3: menuOrdenarPedido();
              break;
          default: menu();
      }
}

void bajas (void) {
    int eleccion;

    //system("cls");
    printf("\nSelecciona una opcion: ");
    scanf("%d", &eleccion);
    //fflush(stdin);

    puts("\n\t**MENU BAJAS**");
    puts("\nElige sobre que elemento quieres hacer la baja o cancelacion.");
    puts("1.- Producto.");
    puts("2.- Empleado.");
    puts("3.- Pedido.");
    puts("4.- Cancelar.");

    switch (eleccion) {
        case 1: bajasProducto();
            break;
        case 2: bajasEmpleado();
            break;
        case 3: bajasPedido();
            break;
        default: menu();
    }
}

int comprobarId (char id[5]) {
    if ((id[0] < 65 || id[0] > 90) || (id[1] < 65 || id[1] > 90) || (id[2] < 48 || id[2] > 57) || (id[3] < 48 ||id[3] > 57) ||
        (id[4] < 48 || id[4] > 57)) {
        return 0;
    } else
        return 1;
}
