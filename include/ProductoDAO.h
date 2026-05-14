#pragma once
#include <vector>
#include "Producto.h"

class ProductoDAO {
public:
    void agregarProducto(string nombre, float precio, int stock, string categoria);
    bool eliminarProducto(int id);
    vector<Producto> obtenerProductos();
};