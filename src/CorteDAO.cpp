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
            "SELECT id_venta, fecha, descripcion, vendedor, total "
            "FROM ventas "
            "ORDER BY fecha DESC"
        );

        for (auto fila : resultado) {
            Corte corte;

            corte.id = fila["id_venta"].as<int>();
            corte.fecha = fila["fecha"].as<string>();
            corte.descripcion = fila["descripcion"].as<string>();
            corte.vendedor = fila["vendedor"].as<string>();
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