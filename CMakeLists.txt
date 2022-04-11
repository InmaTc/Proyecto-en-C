cmake_minimum_required(VERSION 3.17)
project(Proyecto C)

set(CMAKE_C_STANDARD 99)

add_executable(ProyectoC main.c Empleados.c Empleados.h Productos.c Productos.h Pedido.c Pedido.h)