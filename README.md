# Sistema de Domicilios 🛒

Una aplicación en C simple pero funcional para gestionar un carrito de compras y procesar pedidos de domicilio.

## ¿Qué hace?

Es un sistema interactivo donde puedes:
- Explorar un menú de productos con precios
- Agregar artículos al carrito (sin límite de cantidad, solo 6 productos diferentes)
- Ver el carrito con el desglose de costos (subtotal, impuestos y domicilio)
- Confirmar o cancelar tu pedido

## Características

- **Menú intuitivo**: Navegación simple con opciones numeradas
- **Gestión de carrito**: Suma automática si repites un producto
- **Cálculo automático**: Impuestos (19%) y costo de domicilio (10%) incluidos
- **Validación de entrada**: Maneja errores de entrada del usuario
- **Productos precargados**: 6 artículos listos para comprar

## Cómo compilar y ejecutar

```bash
gcc trabajo.c -o domicilios
./domicilios
```

## Productos disponibles

- Arroz (kg) - $3.20
- Leche (1L) - $3.00
- Aceite (1L) - $9.50
- Papas - $4.20
- Helado - $5.00
- Empanada - $2.80

## Notas

Este es un proyecto educativo que demuestra el uso de estructuras, arrays y menús en C. Perfecto para aprender lo básico de programación.