#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "csv_reader.h"

// Variables globales
Order *aOrders = NULL;
int iOrders = 0;
char *sCabecera = NULL;

//
// Rutina para contar cantidad de registros de un archivo de texto
//
int CuentaRegistros(const char *filename) {
    int iOrders = 0;
    FILE *file = fopen(filename, "r");
    struct stat stStatusFile;
    stat(filename, &stStatusFile);
    char *sRegistro = malloc(stStatusFile.st_size);
    
    while (fscanf(file, "%[^\n] ", sRegistro) != EOF) {
        iOrders++;
    }
    fclose(file);
    iOrders--;  // Restar 1 para no contar los encabezados
    free(sRegistro);
    return iOrders;
}

//
// Rutina para cargar el archivo en el puntero de estructura Order
//
void CargaRegistros(const char *filename, int iOrders) {
    aOrders = (Order*)malloc(iOrders * sizeof(Order));
    FILE* file = fopen(filename, "r");
    struct stat stStatusFile;
    stat(filename, &stStatusFile);
    char *sRegistro = malloc(stStatusFile.st_size);
    int iPosRegistro = 0;

    // Salvamos el primer registro de cabecera
    sCabecera = malloc(stStatusFile.st_size);
    fscanf(file, "%[^\n] ", sCabecera);
    
    // Se recorre hasta EOF para cargar los registros
    while (fscanf(file, "%[^\n] ", sRegistro) != EOF) {
        char *token;

        // pizza_id
        token = strtok(sRegistro, ",");
        aOrders[iPosRegistro].pizza_id = atoi(token);

        // order_id
        token = strtok(NULL, ",");
        aOrders[iPosRegistro].order_id = atoi(token);

        // pizza_name_id
        token = strtok(NULL, ",");
        strcpy(aOrders[iPosRegistro].pizza_name_id, token);

        // quantity
        token = strtok(NULL, ",");
        aOrders[iPosRegistro].quantity = atoi(token);

        // order_date
        token = strtok(NULL, ",");
        strcpy(aOrders[iPosRegistro].order_date, token);

        // order_time
        token = strtok(NULL, ",");
        strcpy(aOrders[iPosRegistro].order_time, token);

        // unit_price
        token = strtok(NULL, ",");
        aOrders[iPosRegistro].unit_price = atof(token);

        // total_price
        token = strtok(NULL, ",");
        aOrders[iPosRegistro].total_price = atof(token);

        // pizza_size
        token = strtok(NULL, ",");
        strcpy(aOrders[iPosRegistro].pizza_size, token);

        // pizza_category
        token = strtok(NULL, ",");
        strcpy(aOrders[iPosRegistro].pizza_category, token);

        // pizza_ingredients
        token = strtok(NULL, ",");
        strcpy(aOrders[iPosRegistro].pizza_ingredients, token);

        // pizza_name
        token = strtok(NULL, "\"");
        strcpy(aOrders[iPosRegistro].pizza_name, token);
        
        iPosRegistro++;
    }
    fclose(file);
}

// Función para liberar memoria de las órdenes
void free_orders(Order *orders) { // Reintroduced 'size' parameter to match the header
    if (orders) {
        free(orders);
    }
}
