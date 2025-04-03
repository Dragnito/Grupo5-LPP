#ifndef READER_CSV_H
#define READER_CSV_H

// Estructura Order (o como la tengas en tu código)
typedef struct {
    int pizza_id;
    int order_id;
    char pizza_name_id[50];
    int quantity;
    char order_date[20];
    char order_time[10];
    float unit_price;
    float total_price;
    char pizza_size[5];
    char pizza_category[20];
    char pizza_ingredients[200];
    char pizza_name[100];
} Order;

// Variables globales
extern Order *aOrders;
extern int iOrders;
extern char *sCabecera;

// Declaración de funciones
int CuentaRegistros(const char *filename);
void CargaRegistros(const char *filename, int iOrders);
void MuestraDatos(void);
void free_orders(Order *orders);

#endif // READER_CSV_H