
#ifndef PROYECTOC_PRODUCTOS_H
#define PROYECTOC_PRODUCTOS_H

#include <stdio.h>
#include "Empleados.h"
#include "Pedido.h"

void productos(void);
void altaProducto (void);
void listadoProducto (void);
void consultaProducto (void);
void modificacionProducto (void);
void menuOrdenarProducto (void);
void ordenarProductoIdProducto (void);
void ordenarProductoNombreProd (void);
void bajasProducto (void);

FILE *fichero1;

typedef struct {
    char idProducto[5];
    char idEmpleado[5];
    char nombreProducto[25];
    float precio;
    int stock;
    int sinGluten;
} Producto;

typedef struct {
    int numRegProd;
} CabeceraProductos;

static Producto regProducto;
static CabeceraProductos reg0Productos;


#endif //PROYECTOC_PRODUCTOS_H
