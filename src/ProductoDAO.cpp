#include "ProductoDAO.h"
#include "ConexionBD.h"

#include <pqxx/pqxx>
#include <iostream>

using namespace std;

void ProductoDAO::agregarProducto(string nombre, float precio, int stock, string categoria) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        transaccion.exec_params(
            "INSERT INTO productos(nombre, descripcion, precio, stock, categoria) "
            "VALUES($1, $2, $3, $4, $5)",
            nombre,
            "Producto registrado desde sistema",
            precio,
            stock,
            categoria
        );

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error al agregar producto: " << e.what() << endl;
    }
}

bool ProductoDAO::eliminarProducto(int id) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado = transaccion.exec_params(
            "DELETE FROM productos WHERE id_producto = $1",
            id
        );

        transaccion.commit();

        return true;
    }
    catch (const exception& e) {
        cout << "Error al eliminar producto: " << e.what() << endl;
        return false;
    }
}

vector<Producto> ProductoDAO::obtenerProductos() {
    vector<Producto> productos;

    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado = transaccion.exec(
            "SELECT id_producto, nombre, precio, stock, categoria "
            "FROM productos "
            "ORDER BY id_producto ASC"
        );

        for (auto fila : resultado) {
            Producto producto(
                fila["id_producto"].as<int>(),
                fila["nombre"].as<string>(),
                fila["precio"].as<float>(),
                fila["stock"].as<int>(),
                fila["categoria"].as<string>()
            );

            productos.push_back(producto);
        }

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error al obtener productos: " << e.what() << endl;
    }

    return productos;
}
bool ProductoDAO::actualizarProducto(int id, string nombre, float precio, int stock, string categoria) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        transaccion.exec_params(
            "UPDATE productos "
            "SET nombre = $1, precio = $2, stock = $3, categoria = $4 "
            "WHERE id_producto = $5",
            nombre,
            precio,
            stock,
            categoria,
            id
        );

        transaccion.commit();

        return true;
    }
    catch (const exception& e) {
        cout << "Error al actualizar producto: " << e.what() << endl;
        return false;
    }
}

Producto ProductoDAO::buscarProductoPorId(int id) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado = transaccion.exec_params(
            "SELECT id_producto, nombre, precio, stock, categoria "
            "FROM productos "
            "WHERE id_producto = $1",
            id
        );

        if (!resultado.empty()) {
            auto fila = resultado[0];

            Producto producto(
                fila["id_producto"].as<int>(),
                fila["nombre"].as<string>(),
                fila["precio"].as<float>(),
                fila["stock"].as<int>(),
                fila["categoria"].as<string>()
            );

            transaccion.commit();
            return producto;
        }

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error al buscar producto por ID: " << e.what() << endl;
    }

    return Producto();
}

vector<Producto> ProductoDAO::buscarProductosPorNombre(string nombre) {
    vector<Producto> productos;

    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado = transaccion.exec_params(
            "SELECT id_producto, nombre, precio, stock, categoria "
            "FROM productos "
            "WHERE LOWER(nombre) LIKE LOWER($1) "
            "ORDER BY id_producto ASC",
            "%" + nombre + "%"
        );

        for (auto fila : resultado) {
            Producto producto(
                fila["id_producto"].as<int>(),
                fila["nombre"].as<string>(),
                fila["precio"].as<float>(),
                fila["stock"].as<int>(),
                fila["categoria"].as<string>()
            );

            productos.push_back(producto);
        }

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error al buscar productos por nombre: " << e.what() << endl;
    }

    return productos;
}
bool ProductoDAO::actualizarStockProducto(
    int idProducto,
    int nuevoStock
) {
    try {

        ConexionBD conexionBD;
        pqxx::connection conexion =
            conexionBD.conectar();

        pqxx::work transaccion(conexion);

        transaccion.exec_params(
            "UPDATE productos "
            "SET stock=$1 "
            "WHERE id_producto=$2",
            nuevoStock,
            idProducto
        );

        transaccion.commit();
        return true;
    }
    catch (const exception& e) {
        cout << "Error stock: "
            << e.what() << endl;
        return false;
    }
}