//administra la comunicación entre el sistema y la base de datos para realizar operaciones del módulo productos.
#pragma once

#include <vector>
#include <string>

#include "Producto.h"

using namespace std;

class ProductoDAO {
public:

    //Registra un nuevo producto en la base de datos.
    void agregarProducto(
        string nombre,
        float precio,
        int stock,
        string categoria
    );

    //Elimina un producto utilizando su ID.
    bool eliminarProducto(int id);

    //Obtiene todos los productos registrados.
    vector<Producto> obtenerProductos();

    //Modifica la información de un producto existente.
    bool actualizarProducto(
        int id,
        string nombre,
        float precio,
        int stock,
        string categoria
    );

    //Busca un producto específico mediante su ID.
    Producto buscarProductoPorId(int id);

    vector<Producto> buscarProductosPorNombre(string nombre);


    //Actualiza la cantidad disponible de un producto en inventario.
    bool actualizarStockProducto(
        int idProducto,
        int nuevoStock
    );
};