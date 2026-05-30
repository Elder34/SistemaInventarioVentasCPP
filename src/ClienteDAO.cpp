#include "ClienteDAO.h"
#include "ConexionBD.h"

#include <pqxx/pqxx>
#include <iostream>

using namespace std;

// Agrega un nuevo cliente a la base de datos
void ClienteDAO::agregarCliente(string nombre, string telefono, string correo, string nit) {
    try {
        // Se crea la conexión con la base de datos
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        // Se inicia una transacción
        pqxx::work transaccion(conexion);

        // Inserta los datos del cliente en la tabla clientes
        transaccion.exec_params(
            "INSERT INTO clientes(nombre, telefono, correo, nit) "
            "VALUES($1, $2, $3, $4)",
            nombre,
            telefono,
            correo,
            nit
        );

        // Guarda los cambios en la base de datos
        transaccion.commit();
    }
    catch (const exception& e) {
        // Muestra un mensaje si ocurre un error
        cout << "Error al agregar cliente: " << e.what() << endl;
    }
}

// Obtiene todos los clientes registrados
vector<Cliente> ClienteDAO::obtenerClientes() {
    vector<Cliente> clientes;

    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();
        pqxx::work transaccion(conexion);

        // Consulta todos los clientes ordenados por ID
        pqxx::result resultado = transaccion.exec(
            "SELECT id_cliente, nombre, telefono, correo, nit "
            "FROM clientes "
            "ORDER BY id_cliente ASC"
        );

        // Recorre cada fila obtenida de la base de datos
        for (auto fila : resultado) {
            Cliente cliente(
                fila["id_cliente"].as<int>(),
                fila["nombre"].is_null() ? "" : fila["nombre"].as<string>(),
                fila["telefono"].is_null() ? "" : fila["telefono"].as<string>(),
                fila["correo"].is_null() ? "" : fila["correo"].as<string>(),
                fila["nit"].is_null() ? "CF" : fila["nit"].as<string>()
            );

            // Agrega el cliente al vector
            clientes.push_back(cliente);
        }

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error al obtener clientes: " << e.what() << endl;
    }

    return clientes;
}

// Actualiza los datos de un cliente existente
bool ClienteDAO::actualizarCliente(int id, string nombre, string telefono, string correo, string nit) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();
        pqxx::work transaccion(conexion);

        // Modifica los datos del cliente según su ID
        transaccion.exec_params(
            "UPDATE clientes "
            "SET nombre = $1, telefono = $2, correo = $3, nit = $4 "
            "WHERE id_cliente = $5",
            nombre,
            telefono,
            correo,
            nit,
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

// Busca un cliente por su ID
Cliente ClienteDAO::buscarClientePorId(int id) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();
        pqxx::work transaccion(conexion);

        // Busca un cliente específico por id_cliente
        pqxx::result resultado = transaccion.exec_params(
            "SELECT id_cliente, nombre, telefono, correo, nit "
            "FROM clientes "
            "WHERE id_cliente = $1",
            id
        );

        // Si encontró el cliente, lo retorna
        if (!resultado.empty()) {
            auto fila = resultado[0];

            Cliente cliente(
                fila["id_cliente"].as<int>(),
                fila["nombre"].is_null() ? "" : fila["nombre"].as<string>(),
                fila["telefono"].is_null() ? "" : fila["telefono"].as<string>(),
                fila["correo"].is_null() ? "" : fila["correo"].as<string>(),
                fila["nit"].is_null() ? "CF" : fila["nit"].as<string>()
            );

            transaccion.commit();
            return cliente;
        }

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error al buscar cliente por ID: " << e.what() << endl;
    }

    // Retorna un cliente vacío si no lo encuentra
    return Cliente();
}

// Busca clientes por nombre
vector<Cliente> ClienteDAO::buscarClientesPorNombre(string nombre) {
    vector<Cliente> clientes;

    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();
        pqxx::work transaccion(conexion);

        // Busca coincidencias aunque el nombre esté incompleto
        pqxx::result resultado = transaccion.exec_params(
            "SELECT id_cliente, nombre, telefono, correo, nit "
            "FROM clientes "
            "WHERE LOWER(nombre) LIKE LOWER($1) "
            "ORDER BY id_cliente ASC",
            "%" + nombre + "%"
        );

        for (auto fila : resultado) {
            Cliente cliente(
                fila["id_cliente"].as<int>(),
                fila["nombre"].is_null() ? "" : fila["nombre"].as<string>(),
                fila["telefono"].is_null() ? "" : fila["telefono"].as<string>(),
                fila["correo"].is_null() ? "" : fila["correo"].as<string>(),
                fila["nit"].is_null() ? "CF" : fila["nit"].as<string>()
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

// Elimina un cliente por su ID
bool ClienteDAO::eliminarCliente(int id) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();
        pqxx::work transaccion(conexion);

        // Elimina el registro del cliente
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

// Busca clientes por NIT
vector<Cliente> ClienteDAO::buscarClientesPorNit(string nit) {
    vector<Cliente> clientes;

    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();
        pqxx::work transaccion(conexion);

        // Busca coincidencias del NIT ingresado
        pqxx::result resultado = transaccion.exec_params(
            "SELECT id_cliente, nombre, telefono, correo, nit "
            "FROM clientes "
            "WHERE LOWER(nit) LIKE LOWER($1)",
            "%" + nit + "%"
        );

        for (auto fila : resultado) {
            Cliente cliente(
                fila["id_cliente"].as<int>(),
                fila["nombre"].as<string>(),
                fila["telefono"].as<string>(),
                fila["correo"].as<string>(),
                fila["nit"].as<string>()
            );

            clientes.push_back(cliente);
        }

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error buscar NIT: " << e.what() << endl;
    }

    return clientes;
}