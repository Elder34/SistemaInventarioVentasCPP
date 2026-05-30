#include "VentaDAO.h"
#include "ConexionBD.h"

#include <pqxx/pqxx>
#include <iostream>

using namespace std;

// =============================================
// REGISTRAR VENTA
// Guarda una nueva venta en la base de datos
// =============================================
bool VentaDAO::registrarVenta(
    string cliente,
    string descripcion,
    string vendedor,
    float total,
    string metodoPago
) {
    try {
        // Crear conexión con PostgreSQL
        ConexionBD conexionBD;
        pqxx::connection conexion =
            conexionBD.conectar();

        // Iniciar transacción SQL
        pqxx::work transaccion(conexion);

        // Insertar nueva venta
        // NOW() registra automáticamente fecha y hora
        transaccion.exec_params(
            "INSERT INTO ventas(fecha, cliente, descripcion, vendedor, total, metodo_pago) "
            "VALUES(NOW(), $1, $2, $3, $4, $5)",
            cliente,
            descripcion,
            vendedor,
            total,
            metodoPago
        );

        // Confirmar cambios
        transaccion.commit();
        return true;
    }
    catch (const exception& e) {

        // Mostrar error si ocurre un problema
        cout << "Error registrar venta: "
            << e.what() << endl;

        return false;
    }
}

// =============================================
// OBTENER VENTAS
// Consulta todas las ventas registradas
// =============================================
vector<Venta> VentaDAO::obtenerVentas() {

    // Vector donde se almacenarán ventas
    vector<Venta> ventas;

    try {
        // Crear conexión
        ConexionBD conexionBD;
        pqxx::connection conexion =
            conexionBD.conectar();

        // Iniciar transacción
        pqxx::work transaccion(conexion);

        // Consulta SQL
        pqxx::result resultado =
            transaccion.exec(
                "SELECT id_venta, fecha, cliente, descripcion, vendedor, total "
                "FROM ventas "
                "ORDER BY id_venta DESC"
            );

        // Recorrer ventas encontradas
        for (auto fila : resultado) {

            // Crear objeto temporal Venta
            Venta venta;

            // Asignar datos obtenidos
            venta.setId(
                fila["id_venta"].as<int>()
            );

            venta.setFecha(
                fila["fecha"].as<string>()
            );

            venta.setCliente(
                fila["cliente"].as<string>()
            );

            venta.setDescripcion(
                fila["descripcion"].as<string>()
            );

            venta.setVendedor(
                fila["vendedor"].as<string>()
            );

            venta.setTotal(
                fila["total"].as<float>()
            );

            // Guardar venta en vector
            ventas.push_back(venta);
        }

        // Confirmar transacción
        transaccion.commit();
    }
    catch (const exception& e) {

        // Mostrar error
        cout << "Error obtener ventas: "
            << e.what() << endl;
    }

    return ventas;
}