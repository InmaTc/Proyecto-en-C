
#ifndef PROYECTOC_PEDIDO_H
#define PROYECTOC_PEDIDO_H

#include <stdio.h>

void pedidos(void);
void altaPedido (void);
void listadoPedido (void);
void consultaPedido (void);
void modificacionPedido (void);
void menuOrdenarPedido (void);
void ordenarPedidoId (void);
void ordenarPedidoFecha (void);
void bajasPedido (void);

FILE *fichero3;

typedef struct {
    char idPedido[5];
    char idProducto[5];
    char idEmpleado[5];
    int cantidadProductos;
    char direccion[35];
    char fecha[11];
    int telefonoContacto;
    float precioTotalPedido;
} Pedido;

typedef struct {
    int numRegPedido;
} CabeceraPedido;

static Pedido regPedido;
static CabeceraPedido reg0Pedido;


#endif //PROYECTOC_PEDIDO_H
