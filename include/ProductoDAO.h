#pragma once
#include <vector>
#include "Producto.h"

class ProductoDAO {
public:
    void agregarProducto(string nombre, float precio, int stock, string categoria);
    bool eliminarProducto(int id);
    vector<Producto> obtenerProductos();

    bool actualizarProducto(int id, string nombre, float precio, int stock, string categoria);
    Producto buscarProductoPorId(int id);
    vector<Producto> buscarProductosPorNombre(string nombre);
};