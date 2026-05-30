#include "ProductoDAO.h"
#include "ConexionBD.h"

#include <pqxx/pqxx>
#include <iostream>

using namespace std;

// Agrega un nuevo producto a la base de datos
void ProductoDAO::agregarProducto(
    string nombre,
    float precio,
    int stock,
    string categoria
) {
    try {
        // Crear conexión con PostgreSQL
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        // Iniciar transacción
        pqxx::work transaccion(conexion);

        // Insertar producto en la tabla productos
        transaccion.exec_params(
            "INSERT INTO productos(nombre, descripcion, precio, stock, categoria) "
            "VALUES($1, $2, $3, $4, $5)",
            nombre,
            "Producto registrado desde sistema",
            precio,
            stock,
            categoria
        );

        // Guardar cambios
        transaccion.commit();
    }
    catch (const exception& e) {

        // Mostrar error si ocurre
        cout << "Error al agregar producto: "
            << e.what() << endl;
    }
}

// Elimina un producto usando su ID
bool ProductoDAO::eliminarProducto(int id) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        // Eliminar producto de la base de datos
        transaccion.exec_params(
            "DELETE FROM productos WHERE id_producto = $1",
            id
        );

        transaccion.commit();

        return true;
    }
    catch (const exception& e) {
        cout << "Error al eliminar producto: "
            << e.what() << endl;
        return false;
    }
}

// Obtiene todos los productos registrados
vector<Producto> ProductoDAO::obtenerProductos() {

    // Vector para almacenar productos
    vector<Producto> productos;

    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        // Consulta SQL para obtener productos
        pqxx::result resultado = transaccion.exec(
            "SELECT id_producto, nombre, precio, stock, categoria "
            "FROM productos "
            "ORDER BY id_producto ASC"
        );

        // Recorrer resultados obtenidos
        for (auto fila : resultado) {

            Producto producto(
                fila["id_producto"].as<int>(),
                fila["nombre"].as<string>(),
                fila["precio"].as<float>(),
                fila["stock"].as<int>(),
                fila["categoria"].as<string>()
            );

            // Guardar producto en vector
            productos.push_back(producto);
        }

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error al obtener productos: "
            << e.what() << endl;
    }

    return productos;
}

// Actualiza los datos de un producto existente
bool ProductoDAO::actualizarProducto(
    int id,
    string nombre,
    float precio,
    int stock,
    string categoria
) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        // Actualizar información del producto
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
        cout << "Error al actualizar producto: "
            << e.what() << endl;
        return false;
    }
}

// Busca un producto usando su ID
Producto ProductoDAO::buscarProductoPorId(int id) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        // Buscar producto específico
        pqxx::result resultado = transaccion.exec_params(
            "SELECT id_producto, nombre, precio, stock, categoria "
            "FROM productos "
            "WHERE id_producto = $1",
            id
        );

        // Si existe, retornarlo
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
        cout << "Error al buscar producto por ID: "
            << e.what() << endl;
    }

    // Retorna producto vacío si no existe
    return Producto();
}

// Busca productos por coincidencia de nombre
vector<Producto> ProductoDAO::buscarProductosPorNombre(
    string nombre
) {
    vector<Producto> productos;

    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        // Búsqueda flexible usando LIKE
        pqxx::result resultado = transaccion.exec_params(
            "SELECT id_producto, nombre, precio, stock, categoria "
            "FROM productos "
            "WHERE LOWER(nombre) LIKE LOWER($1) "
            "ORDER BY id_producto ASC",
            "%" + nombre + "%"
        );

        // Recorrer coincidencias
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
        cout << "Error al buscar productos por nombre: "
            << e.what() << endl;
    }

    return productos;
}

// Actualiza únicamente el stock de un producto
bool ProductoDAO::actualizarStockProducto(
    int idProducto,
    int nuevoStock
) {
    try {

        ConexionBD conexionBD;
        pqxx::connection conexion =
            conexionBD.conectar();

        pqxx::work transaccion(conexion);

        // Modificar cantidad disponible
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