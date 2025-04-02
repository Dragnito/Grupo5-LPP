#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "../include/metrics.h"
#include "../include/csv_reader.h"

#define MAX_PIZZAS 50

//Evitar Errores (Temporal para poder correr el codigo)

void ingrediente_mas_vendido() {
    printf("Función ingrediente_mas_vendido aún no implementada.\n");
}

void categoria_pizzas() {
    printf("Función categoria_pizzas aún no implementada.\n");
}



typedef struct {
    char pizza_name[50];
    int total_sold;
} PizzaCount;


// Funcion para las pizzas mas vendidas
char* pizza_mas_vendida(int size, Order *orders) {
    PizzaCount pizzas[MAX_PIZZAS] = {0}; 
    int pizza_count = 0;
//ciclo para contar cuantas veces fue pedida la pizza
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < pizza_count; j++) {
            if (strcmp(pizzas[j].pizza_name, orders[i].pizza_name) == 0) {
                pizzas[j].total_sold += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && pizza_count < MAX_PIZZAS) { //
            strcpy(pizzas[pizza_count].pizza_name, orders[i].pizza_name);
            pizzas[pizza_count].total_sold = orders[i].quantity;
            pizza_count++;
        }
    }

    int max_index = 0;
    for (int i = 1; i < pizza_count; i++) {
        if (pizzas[i].total_sold > pizzas[max_index].total_sold) {
            max_index = i;
        }
    }

    return strdup(pizzas[max_index].pizza_name); // Copia dinámica del string
}


//Funcion para la contar la pizza menos vendida
char* pizza_menos_vendida(int size, Order *orders) {
    PizzaCount pizzas[MAX_PIZZAS] = {0}; 
    int pizza_count = 0;
//ciclo para contar la pizza menos solicitada
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < pizza_count; j++) {
            if (strcmp(pizzas[j].pizza_name, orders[i].pizza_name) == 0) {
                pizzas[j].total_sold += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && pizza_count < MAX_PIZZAS) {
            strcpy(pizzas[pizza_count].pizza_name, orders[i].pizza_name);
            pizzas[pizza_count].total_sold = orders[i].quantity;
            pizza_count++;
        }
    }

    int min_index = 0;
    for (int i = 1; i < pizza_count; i++) {
        if (pizzas[i].total_sold < pizzas[min_index].total_sold) {
            min_index = i;
        }
    }

    return strdup(pizzas[min_index].pizza_name); // Copia dinámica del string
}



// Función para encontrar el día con más ventas en términos de dinero
char* dia_mas_dinero(int size, Order *orders, float *total_ventas) {
    float max_sales = 0.0f;
    char max_day[20] = {0};

    // Usamos un arreglo temporal para sumar ventas por fecha
    float sales_by_day[MAX_PIZZAS] = {0};
    char dates[MAX_PIZZAS][20];  // Array de fechas únicas

    int date_count = 0;  // Para llevar el registro de cuántas fechas hemos encontrado

    for (int i = 0; i < iOrders; i++) {
        int found = 0;
        for (int j = 0; j < date_count; j++) {
            if (strcmp(dates[j], aOrders[i].order_date) == 0) {
                sales_by_day[j] += aOrders[i].total_price;
                found = 1;
                break;
            }
        }

        if (!found) {
            // Si no encontramos la fecha, agregamos una nueva entrada para esta fecha
            strcpy(dates[date_count], aOrders[i].order_date);
            sales_by_day[date_count] = aOrders[i].total_price;
            date_count++;
        }
    }

    // Buscar la fecha con el máximo total de ventas
    for (int i = 0; i < date_count; i++) {
        if (sales_by_day[i] > max_sales) {
            max_sales = sales_by_day[i];
            strcpy(max_day, dates[i]);
        }
    }

    *total_ventas = max_sales;  // Asignar el total de ventas

    return strdup(max_day);  // Devolver la fecha con más ventas
}



// Función para encontrar el día con menos ventas en términos de dinero
char* dia_menos_dinero(int size, Order *orders, float *total_ventas) {
    float min_sales = FLT_MAX;
    char min_day[20] = {0};

    // Usamos un arreglo temporal para sumar ventas por fecha
    float sales_by_day[MAX_PIZZAS] = {0};
    char dates[MAX_PIZZAS][20];  // Array de fechas únicas

    int date_count = 0;  // Para llevar el registro de cuántas fechas hemos encontrado

    for (int i = 0; i < iOrders; i++) {
        int found = 0;
        for (int j = 0; j < date_count; j++) {
            if (strcmp(dates[j], aOrders[i].order_date) == 0) {
                sales_by_day[j] += aOrders[i].total_price;
                found = 1;
                break;
            }
        }

        if (!found) {
            // Si no encontramos la fecha, agregamos una nueva entrada para esta fecha
            strcpy(dates[date_count], aOrders[i].order_date);
            sales_by_day[date_count] = aOrders[i].total_price;
            date_count++;
        }
    }

    // Buscar la fecha con el mínimo total de ventas
    for (int i = 0; i < date_count; i++) {
        if (sales_by_day[i] < min_sales) {
            min_sales = sales_by_day[i];
            strcpy(min_day, dates[i]);
        }
    }

    *total_ventas = min_sales;  // Asignar el total de ventas

    return strdup(min_day);  // Devolver la fecha con menos ventas
}



// Función para encontrar el día con más ventas en términos de cantidad de pizzas vendidas
char* dia_mas_pizzas_vendidas(int size, Order *orders, int *total_pizzas) {
    int max_pizzas = 0;
    char max_day[20] = {0};

    int pizzas_by_day[MAX_PIZZAS] = {0};
    char dates[MAX_PIZZAS][20];
    int date_count = 0;
//Ciclo que recorre las fechas del archivo
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < date_count; j++) {
            if (strcmp(dates[j], orders[i].order_date) == 0) {
                pizzas_by_day[j] += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(dates[date_count], orders[i].order_date);
            pizzas_by_day[date_count] = orders[i].quantity;
            date_count++;
        }
    }

    for (int i = 0; i < date_count; i++) {
        if (pizzas_by_day[i] > max_pizzas) {
            max_pizzas = pizzas_by_day[i];
            strcpy(max_day, dates[i]);
        }
    }

    *total_pizzas = max_pizzas;
    return strdup(max_day);
}



// Función para encontrar el día con menos ventas en términos de cantidad de pizzas vendidas
char* dia_menos_pizzas_vendidas(int size, Order *orders, int *total_pizzas) {
    int min_pizzas = INT_MAX;
    char min_day[20] = {0};

    int pizzas_by_day[MAX_PIZZAS] = {0};
    char dates[MAX_PIZZAS][20];
    int date_count = 0;

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < date_count; j++) {
            if (strcmp(dates[j], orders[i].order_date) == 0) {
                pizzas_by_day[j] += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(dates[date_count], orders[i].order_date);
            pizzas_by_day[date_count] = orders[i].quantity;
            date_count++;
        }
    }

    for (int i = 0; i < date_count; i++) {
        if (pizzas_by_day[i] < min_pizzas) {
            min_pizzas = pizzas_by_day[i];
            strcpy(min_day, dates[i]);
        }
    }

    *total_pizzas = min_pizzas;
    return strdup(min_day);
}



//Funcion que determina el promedio de pizzas por orden
float promedio_pizzas_orden(int size, Order *orders) {
    int total_pizzas = 0;

    // Sumar todas las cantidades de pizzas
    for (int i = 0; i < size; i++) {
        total_pizzas += orders[i].quantity;
    }

    // Calcular el promedio
    return (float)total_pizzas / size;
}



// Función para calcular el promedio de pizzas vendidas por día
float promedio_pizzas_dia(int size, Order *orders) {
    int total_pizzas = 0;
    int total_dias = 0;

    // Usamos un arreglo temporal para contar las pizzas vendidas por cada fecha
    int pizzas_by_day[MAX_PIZZAS] = {0};
    char dates[MAX_PIZZAS][20];  // Array de fechas únicas

    int date_count = 0;  // Para llevar el registro de cuántas fechas hemos encontrado

    // Sumar las pizzas vendidas por cada fecha
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < date_count; j++) {
            if (strcmp(dates[j], orders[i].order_date) == 0) {
                pizzas_by_day[j] += orders[i].quantity;
                found = 1;
                break;
            }
        }

        if (!found) {
            // Si no encontramos la fecha, agregamos una nueva entrada para esta fecha
            strcpy(dates[date_count], orders[i].order_date);
            pizzas_by_day[date_count] = orders[i].quantity;
            date_count++;
        }
    }

    // Sumar todas las pizzas vendidas por los días
    for (int i = 0; i < date_count; i++) {
        total_pizzas += pizzas_by_day[i];
    }

    total_dias = date_count; // La cantidad de días únicos

    // Retornar el promedio de pizzas vendidas por día
    return (float)total_pizzas / total_dias;
}
