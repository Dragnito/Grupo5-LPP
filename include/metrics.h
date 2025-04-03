#ifndef METRICS_H
#define METRICS_H

#include "csv_reader.h"

typedef char* (*MetricFunction)(int *size, Order *orders);

//Hay que declarar las funciones para cada metrica aqui
char* pizza_mas_vendida(int size, Order *orders);
char* pizza_menos_vendida(int size, Order *orders);
char* dia_mas_dinero(int size, Order *orders, float *total);
char* dia_menos_dinero(int size, Order *orders, float *total);
char* dia_mas_pizzas_vendidas(int size, Order *orders, int *total);
char* dia_menos_pizzas_vendidas(int size, Order *orders, int *total);
char* promedio_pizzas_orden(int size, Order *orders);
char* promedio_pizzas_dia(int size, Order *orders);
char* ingrediente_mas_vendido(int size, Order *orders);
char* categoria_pizzas(int size, Order *orders);

#endif