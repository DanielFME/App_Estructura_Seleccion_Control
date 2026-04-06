#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX_PRODUCTOS 9
#define PRODUCTOS 6
#define MAX_CARRITO 6
#define COSTO_DOMICILIO 0.10f
#define IMPUESTO 0.19f


typedef struct {
    int id;
    char nombre[50];
    float precio;
} Producto;


typedef struct {
    int idProducto;
    int cantidad;
} ProduCarrito; 


Producto productos[MAX_PRODUCTOS];
int numProductos = 0;


ProduCarrito  carrito[MAX_CARRITO];
int numItemsCarrito = 0;


void limpiarBufferEntrada(void) {
    int c;
    
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}


void Productosdis(void) {
    productos[0] = (Producto){1, "Arroz(kg)",3.200f};
    productos[1] = (Producto){2, "Leche(1L)", 3.000f};
    productos[2] = (Producto){3, "Aceite(1L)", 9.500f};
    productos[3] = (Producto){4, "Papas", 4.20f};
    productos[4] = (Producto){5, "Helado", 5.00f};
    productos[5] = (Producto){6, "Empanada", 2.80f};
    
    numProductos = PRODUCTOS;
}


void mostrarProductos(void) {
    int i;

    
    if (numProductos == 0) {
        printf("No hay productos disponibles.\n");
        return;
    }

    printf("\nProductos disponibles:\n");
    
    for (i = 0; i < numProductos; i++) {
        printf("%d. %s - $%.2f\n", productos[i].id, productos[i].nombre, productos[i].precio);
    }
}


int buscarProducto(int idProducto) {
    int i;

    for (i = 0; i < numProductos; i++) {
        if (productos[i].id == idProducto) {
            return i;
        }
    }

    
    return -1;
}


int norep(int idProducto) {
    int i;

    for (i = 0; i < numItemsCarrito; i++) {
        if (carrito[i].idProducto == idProducto) {
            return i;
        }
    }

    return -1;
}


void agregarProductoAlCarrito(void) {
    int idProducto;
    int cantidad;
    int indiceProducto;
    int indiceCarrito;

    
    if (numItemsCarrito >= MAX_CARRITO) {
        printf("El carrito esta lleno.\n");
        return;
    }

    mostrarProductos();

    printf("\nIngrese el ID del producto: ");
    
    if (scanf("%d", &idProducto) != 1) {
        printf("Entrada invalida para ID.\n");
        limpiarBufferEntrada();
        return;
    }

    
    indiceProducto = buscarProducto(idProducto);
    if (indiceProducto == -1) {
        printf("No existe un producto con ese ID.\n");
        return;
    }

    printf("Ingrese la cantidad: ");
    if (scanf("%d", &cantidad) != 1) {
        printf("Entrada invalida para cantidad.\n");
        limpiarBufferEntrada();
        return;
    }

    
    if (cantidad <= 0) {
        printf("La cantidad debe ser mayor a 0.\n");
        return;
    }

    
    indiceCarrito = norep(idProducto);
    if (indiceCarrito == -1) {
        carrito[numItemsCarrito].idProducto = idProducto;
        carrito[numItemsCarrito].cantidad = cantidad;
        numItemsCarrito++;
    } else {
        carrito[indiceCarrito].cantidad += cantidad;
    }

    printf("Producto agregado al carrito correctamente.\n");
}


void verCarritoYTotal(void) {
    int i;
    float subtotal = 0.0f;
    float impuestos;
    float total;

    
    if (numItemsCarrito == 0) {
        printf("El carrito esta vacio.\n");
        return;
    }

    printf("\nCarrito:\n");
    for (i = 0; i < numItemsCarrito; i++) {
        
        int indiceProducto = buscarProducto(carrito[i].idProducto);
        float subtotalItem;

        
        if (indiceProducto == -1) {
            continue;
        }

        
        subtotalItem = productos[indiceProducto].precio * carrito[i].cantidad;
        subtotal += subtotalItem;

        printf("- %s | Cantidad: %d | Precio: $%.2f | Subtotal: $%.2f\n",
               productos[indiceProducto].nombre,
               carrito[i].cantidad,
               productos[indiceProducto].precio,
               subtotalItem);
    }

    
    impuestos = subtotal * IMPUESTO;
    total = subtotal + impuestos + (subtotal * COSTO_DOMICILIO);

    printf("\nResumen:\n");
    printf("Subtotal: $%.2f\n", subtotal);
    printf("Impuestos (19%%): $%.2f\n", impuestos);
    printf("Domicilio: $%.2f\n", subtotal * COSTO_DOMICILIO);
    printf("Total: $%.2f\n", total);
}


void confirmarPedido(void) {
    
    char confirmacion[10];
    int i;

    
    if (numItemsCarrito == 0) {
        printf("No puede confirmar un pedido con carrito vacio.\n");
        return;
    }

    
    verCarritoYTotal();
    printf("\nConfirmar pedido? (si/no): ");

    
    if (scanf("%9s", confirmacion) != 1) {
        printf("Confirmacion invalida.\n");
        limpiarBufferEntrada();
        return;
    }

    
    for (i = 0; confirmacion[i] != '\0'; i++) {
        confirmacion[i] = (char)tolower((unsigned char)confirmacion[i]);
    }

    
    if (strcmp(confirmacion, "si") == 0 || strcmp(confirmacion, "s") == 0) {
        
        numItemsCarrito = 0;
        printf("Pedido confirmado. Gracias por su compra.\n");
    } else if (strcmp(confirmacion, "no") == 0 || strcmp(confirmacion, "n") == 0) {
        printf("Pedido no confirmado.\n");
    } else {
        printf("Confirmacion invalida. Responda si o no.\n");
    }
}


void Menu(void) {
    printf("\nBienvenido al sistema de domicilios\n");
    printf("1. Ver menu de productos\n");
    printf("2. Agregar producto al carrito\n");
    printf("3. Ver carrito y total\n");
    printf("4. Confirmar pedido\n");
    printf("5. Salir\n");
    printf("Seleccione una opcion: ");
}

int main(void) {
    
    int opcion;

    
    Productosdis();

    
    do {
        Menu();

        
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada no valida. Ingrese un numero.\n");
            limpiarBufferEntrada();
            continue;
        }

        
        switch (opcion) {
            case 1:
                mostrarProductos();
                break;
            case 2:
                agregarProductoAlCarrito();
                break;
            case 3:
                verCarritoYTotal();
                break;
            case 4:
                confirmarPedido();
                break;
            case 5:
                printf("Saliendo del programa. Gracias por su visita.\n");
                break;
            default:
                printf("Opcion no valida.\n");
                break;
        }
    } while (opcion != 5);

    
    return 0;
}


