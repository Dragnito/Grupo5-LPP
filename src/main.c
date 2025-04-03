#include <stdio.h>
#include <stdlib.h>
#include "../include/csv_reader.h"
#include "../include/metrics.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <ventas_pizzas.csv>\n", argv[0]);
        return 1;
    }

    // Contar los registros del archivo
    iOrders = CuentaRegistros(argv[1]);
    if (iOrders == 0) {
        printf("No se encontraron ordenes en el archivo.\n");
        return 1;
    }

    // Cargar las órdenes del archivo
    CargaRegistros(argv[1], iOrders);
    if (aOrders == NULL) {
        printf("Error al cargar las ordenes.\n");
        return 1;
    }

    printf("Se cargaron %d ordenes.\n", iOrders);
    
    // Selección de categorías para demostrar datos
    char categorias[4];
    char *mas_vendida = NULL;
    char *menos_vendida = NULL;
    while (1){ // Ciclo While infinito que pregunta la categoría hasta que se encuentre un "exit" o el "safe net" que rompa el ciclo
        printf("Que datos desea conocer?: (pms, pls, dms, dls, dmsp, dlsp, apo, apd, ims, hp, exit)\n");
        scanf("%s", categorias);
        if (strcmp(categorias, "pms") == 0) { // Pizza más vendida
            if (mas_vendida) free(mas_vendida); // Liberar memoria previa si existe
            mas_vendida = pizza_mas_vendida(iOrders, aOrders);
            printf("La pizza mas vendida fue: %s\n", mas_vendida);
        }
        else if (strcmp(categorias, "pls") == 0) { // Pizza menos vendida
            if (menos_vendida) free(menos_vendida);
            menos_vendida = pizza_menos_vendida(iOrders, aOrders);
            printf("La pizza menos vendida fue: %s\n", menos_vendida);
        }
        else if (strcmp(categorias, "dms") == 0) { // Día con más ventas
            float ventas_mas = 0; // Variable para almacenar el total de ventas
            char *fecha_mas = dia_mas_dinero(iOrders, aOrders, &ventas_mas);
            printf("El dia con mas ventas fue: %s con un total de $%.2f\n", fecha_mas, ventas_mas);
            free(fecha_mas); // Liberar la memoria devuelta por strdup
        }
        else if (strcmp(categorias, "dls") == 0) { // Día con menos ventas
            float ventas_menos = 0; // Variable para almacenar el total de ventas
            char *fecha_menos = dia_menos_dinero(iOrders, aOrders, &ventas_menos);
            printf("El dia con menos ventas fue: %s con un total de $%.2f\n", fecha_menos, ventas_menos);
            free(fecha_menos); // Liberar la memoria devuelta por strdup
        }
        else if (strcmp(categorias, "dmsp") == 0) { // Día donde se vendieron más pizzas
            int total_pizzas_mas;
            char* fecha_mas = dia_mas_pizzas_vendidas(iOrders, aOrders, &total_pizzas_mas);
            printf("El dia con mas pizzas vendidas fue: %s con %d pizzas vendidas.\n", fecha_mas, total_pizzas_mas);
            free(fecha_mas); // Liberar memoria de la fecha
        }
        else if (strcmp(categorias, "dlsp") == 0) { // Día donde se vendieron menos pizzas
            int total_pizzas_menos;
            char* fecha_menos = dia_menos_pizzas_vendidas(iOrders, aOrders, &total_pizzas_menos);
            printf("El dia con menos pizzas vendidas fue: %s con %d pizzas vendidas.\n", fecha_menos, total_pizzas_menos);
            free(fecha_menos); // Liberar memoria de la fecha
        }
        else if (strcmp(categorias, "apo") == 0) { // Promedio de pizzas pedidas por orden
            float promedio = promedio_pizzas_orden(iOrders, aOrders);
            printf("El promedio de pizzas por orden es: %.2f\n", promedio);
        }
        else if (strcmp(categorias, "apd") == 0) { // Promedio de pizzas vendidas por día
            float promedio = promedio_pizzas_dia(iOrders, aOrders);
            printf("El promedio de pizzas vendidas por dia es: %.2f\n", promedio);
        }        
        else if (strcmp(categorias, "ims") == 0){ // Ingrediente más vendido
            char* mensaje = ingrediente_mas_vendido(iOrders, aOrders);  // Llamar la función con los parámetros adecuados
            printf("%s\n", mensaje);  // Imprimir el mensaje generado por la función
        }
        else if (strcmp(categorias, "hp") == 0){ // Categoría más vendida de pizzas
            categoria_pizzas();
        }
        else if (strcmp(categorias, "exit") == 0){ // Exit del código sin tener que pasar por el "safe net"
            printf("Proceso finalizado exitosamente.\n");
            break;
        }
        else { // "Safe net" en caso de que se registre una métrica errónea y/o mal redactada
            char respuesta[2];
            printf("Se pidio una metrica que no existe, Desea continuar?: (S/N)\n ");
            scanf(" %1s", respuesta);
            if (strcmp(respuesta, "N") == 0 || strcmp(respuesta, "n") == 0) {
                break;
            }
        }

        // Limpiar el búfer de entrada para evitar problemas en la siguiente iteración
        while (getchar() != '\n');
    }

    // Liberar memorias asignadas
    free(sCabecera);
    free_orders(aOrders); // Removed the second argument 'iOrders'
    if (mas_vendida) free(mas_vendida);
    if (menos_vendida) free(menos_vendida);

    return 0;
}
