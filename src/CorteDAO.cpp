#include "CorteDAO.h"
#include "ConexionBD.h"

#include <pqxx/pqxx>
#include <iostream>

using namespace std;

// Obtiene el historial de ventas o cortes registrados
vector<Corte> CorteDAO::obtenerCortes() {

    // Vector donde se almacenarán los cortes obtenidos
    vector<Corte> cortes;

    try {
        // Crear conexión con la base de datos
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        // Iniciar transacción SQL
        pqxx::work transaccion(conexion);

        // Consulta para obtener la información de ventas
        pqxx::result resultado = transaccion.exec(
            "SELECT id_venta, fecha, descripcion, vendedor, total, metodo_pago "
            "FROM ventas "
            "ORDER BY id_venta DESC"
        );

        // Recorrer cada fila obtenida de la consulta
        for (auto fila : resultado) {

            // Crear objeto corte temporal
            Corte corte;

            // Asignar datos del registro al objeto corte
            corte.id = fila["id_venta"].as<int>();

            // Validar si la fecha es nula
            corte.fecha = fila["fecha"].is_null()
                ? ""
                : fila["fecha"].as<string>();

            // Validar descripción vacía o nula
            corte.descripcion = fila["descripcion"].is_null()
                ? "Sin descripcion"
                : fila["descripcion"].as<string>();

            // Validar método de pago
            corte.metodoPago = fila["metodo_pago"].is_null()
                ? "Sin metodo"
                : fila["metodo_pago"].as<string>();

            // Validar vendedor
            corte.vendedor = fila["vendedor"].is_null()
                ? "Sin vendedor"
                : fila["vendedor"].as<string>();

            // Obtener total de la venta
            corte.total = fila["total"].as<float>();

            // Guardar el corte en el vector
            cortes.push_back(corte);
        }

        // Confirmar transacción
        transaccion.commit();
    }
    catch (const exception& e) {

        // Mostrar mensaje si ocurre un error
        cout << "Error al obtener cortes: " << e.what() << endl;
    }

    // Retornar lista de cortes obtenidos
    return cortes;
}