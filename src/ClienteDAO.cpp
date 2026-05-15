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
bool ClienteDAO::actualizarCliente(int id, string nombre, string telefono, string correo) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        transaccion.exec_params(
            "UPDATE clientes "
            "SET nombre = $1, telefono = $2, direccion = $3 "
            "WHERE id_cliente = $4",
            nombre,
            telefono,
            correo,
            id
        );

        transaccion.commit();
        return true;
    }
    catch (const exception& e) {
        cout << "Error al actualizar cliente: " << e.what() << endl;
        return false;
    }
}
Cliente ClienteDAO::buscarClientePorId(int id) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado = transaccion.exec_params(
            "SELECT id_cliente, nombre, telefono, direccion "
            "FROM clientes "
            "WHERE id_cliente = $1",
            id
        );

        if (!resultado.empty()) {
            auto fila = resultado[0];

            Cliente cliente(
                fila["id_cliente"].as<int>(),
                fila["nombre"].as<string>(),
                fila["telefono"].as<string>(),
                fila["direccion"].as<string>()
            );

            transaccion.commit();
            return cliente;
        }

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error al buscar cliente por ID: " << e.what() << endl;
    }

    return Cliente();
}

vector<Cliente> ClienteDAO::buscarClientesPorNombre(string nombre) {
    vector<Cliente> clientes;

    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado = transaccion.exec_params(
            "SELECT id_cliente, nombre, telefono, direccion "
            "FROM clientes "
            "WHERE LOWER(nombre) LIKE LOWER($1) "
            "ORDER BY id_cliente ASC",
            "%" + nombre + "%"
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
        cout << "Error al buscar clientes por nombre: " << e.what() << endl;
    }

    return clientes;
}