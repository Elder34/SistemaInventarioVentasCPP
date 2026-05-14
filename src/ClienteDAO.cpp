#include "ClienteDAO.h"
#include "ConexionBD.h"

#include <pqxx/pqxx>
#include <iostream>

using namespace std;

void ClienteDAO::agregarCliente(string nombre, string telefono, string correo) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        transaccion.exec_params(
            "INSERT INTO clientes(nombre, telefono, direccion, nit) "
            "VALUES($1, $2, $3, $4)",
            nombre,
            telefono,
            correo,
            "CF"
        );

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error al agregar cliente: " << e.what() << endl;
    }
}

bool ClienteDAO::eliminarCliente(int id) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        transaccion.exec_params(
            "DELETE FROM clientes WHERE id_cliente = $1",
            id
        );

        transaccion.commit();

        return true;
    }
    catch (const exception& e) {
        cout << "Error al eliminar cliente: " << e.what() << endl;
        return false;
    }
}

vector<Cliente> ClienteDAO::obtenerClientes() {
    vector<Cliente> clientes;

    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado = transaccion.exec(
            "SELECT id_cliente, nombre, telefono, direccion "
            "FROM clientes "
            "ORDER BY id_cliente ASC"
        );

        for (auto fila : resultado) {
            Cliente cliente(
                fila["id_cliente"].as<int>(),
                fila["nombre"].as<string>(),
                fila["telefono"].as<string>(),
                fila["direccion"].as<string>()
            );

            clientes.push_back(cliente);
        }

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error al obtener clientes: " << e.what() << endl;
    }

    return clientes;
}