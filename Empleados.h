#ifndef PROYECTOC_EMPLEADOS_H
#define PROYECTOC_EMPLEADOS_H

#include <stdio.h>

void empleados(void);
void altaEmpleado(void);
void listadoEmpleado(void);
void consultaEmpleado(void);
void modificacionEmpleado(void);
void menuOrdenarEmpleado (void);
void ordenarEmpleadoIdEmp(void);
void ordenarEmpleadoNombre (void);
void bajasEmpleado(void);

FILE *fichero2;

typedef struct {
    char idEmpleado[5];
    char nombreEmpleado[25];
    float sueldo;
    int telefono;
} Empleado;

typedef struct {
    int numRegEmpleado;
} CabeceraEmpleado;

static Empleado regEmpleado;
static CabeceraEmpleado reg0Empleado;

#endif //PROYECTOC_EMPLEADOS_H
