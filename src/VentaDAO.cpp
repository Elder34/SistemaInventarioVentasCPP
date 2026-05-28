#include "VentaDAO.h"
#include "ConexionBD.h"

#include <pqxx/pqxx>
#include <iostream>

using namespace std;

bool VentaDAO::registrarVenta(string cliente, string descripcion, string vendedor, float total, string metodoPago) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        transaccion.exec_params(
            "INSERT INTO ventas(fecha, cliente, descripcion, vendedor, total, metodo_pago) "
            "VALUES(NOW(), $1, $2, $3, $4, $5)",
            cliente,
            descripcion,
            vendedor,
            total,
            metodoPago
        );

        transaccion.commit();
        return true;
    }
    catch (const exception& e) {
        cout << "Error registrar venta: " << e.what() << endl;
        return false;
    }
}

vector<Venta> VentaDAO::obtenerVentas() {
    vector<Venta> ventas;

    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado = transaccion.exec(
            "SELECT id_venta, fecha, cliente, descripcion, vendedor, total "
            "FROM ventas "
            "ORDER BY id_venta DESC"
        );

        for (auto fila : resultado) {
            Venta venta;

            venta.setId(fila["id_venta"].as<int>());
            venta.setFecha(fila["fecha"].as<string>());
            venta.setCliente(fila["cliente"].as<string>());
            venta.setDescripcion(fila["descripcion"].as<string>());
            venta.setVendedor(fila["vendedor"].as<string>());
            venta.setTotal(fila["total"].as<float>());

            ventas.push_back(venta);
        }

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error obtener ventas: " << e.what() << endl;
    }

    return ventas;
}