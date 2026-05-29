#include "Login.h"
#include "ConexionBD.h"

#include <pqxx/pqxx>
#include <iostream>

using namespace std;

bool Login::validarUsuario(string usuario, string password) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado = transaccion.exec_params(
            "SELECT id_usuario "
            "FROM usuarios "
            "WHERE usuario = $1 AND password = $2 "
            "LIMIT 1",
            usuario,
            password
        );

        transaccion.commit();

        return !resultado.empty();
    }
    catch (const exception& e) {
        cout << "Error login: " << e.what() << endl;
        return false;
    }
}
string Login::obtenerRolUsuario(string usuario) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado = transaccion.exec_params(
            "SELECT rol FROM usuarios WHERE usuario = $1 LIMIT 1",
            usuario
        );

        transaccion.commit();

        if (!resultado.empty()) {
            return resultado[0]["rol"].is_null()
                ? "vendedor"
                : resultado[0]["rol"].as<string>();
        }
    }
    catch (const exception& e) {
        cout << "Error obtener rol: " << e.what() << endl;
    }

    return "vendedor";
}