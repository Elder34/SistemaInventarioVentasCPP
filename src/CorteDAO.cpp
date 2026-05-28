#include "CorteDAO.h"
#include "ConexionBD.h"

#include <pqxx/pqxx>
#include <iostream>

using namespace std;

vector<Corte> CorteDAO::obtenerCortes() {
    vector<Corte> cortes;

    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado = transaccion.exec(
            "SELECT id_venta, fecha, descripcion, vendedor, total, metodo_pago "
            "FROM ventas "
            "ORDER BY id_venta DESC"
        );

        for (auto fila : resultado) {
            Corte corte;

            corte.id = fila["id_venta"].as<int>();
            corte.fecha = fila["fecha"].is_null() ? "" : fila["fecha"].as<string>();

            corte.descripcion = fila["descripcion"].is_null()
                ? "Sin descripcion"
                : fila["descripcion"].as<string>();

            corte.metodoPago = fila["metodo_pago"].is_null()
                ? "Sin metodo"
                : fila["metodo_pago"].as<string>();

            corte.vendedor = fila["vendedor"].is_null()
                ? "Sin vendedor"
                : fila["vendedor"].as<string>();
            corte.total = fila["total"].as<float>();

            cortes.push_back(corte);
        }

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error al obtener cortes: " << e.what() << endl;
    }

    return cortes;
}