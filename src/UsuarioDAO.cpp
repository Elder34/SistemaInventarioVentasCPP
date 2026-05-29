#include "UsuarioDAO.h"
#include "ConexionBD.h"

#include <pqxx/pqxx>
#include <iostream>

using namespace std;

bool UsuarioDAO::agregarUsuario(
    string nombre,
    string usuario,
    string password,
    string rol
) {
    try {

        ConexionBD conexionBD;
        pqxx::connection conexion =
            conexionBD.conectar();

        pqxx::work transaccion(conexion);

        transaccion.exec_params(
            "INSERT INTO usuarios "
            "(nombre, usuario, password, rol) "
            "VALUES ($1, $2, $3, $4)",
            nombre,
            usuario,
            password,
            rol
        );

        transaccion.commit();
        return true;
    }
    catch (const exception& e) {

        cout
            << "Error agregar usuario: "
            << e.what()
            << endl;

        return false;
    }
}

vector<Usuario> UsuarioDAO::obtenerUsuarios() {

    vector<Usuario> usuarios;

    try {

        ConexionBD conexionBD;
        pqxx::connection conexion =
            conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado =
            transaccion.exec(
                "SELECT "
                "id_usuario, "
                "nombre, "
                "usuario, "
                "password, "
                "rol "
                "FROM usuarios "
                "ORDER BY id_usuario ASC"
            );

        for (auto fila : resultado) {

            Usuario usuario;

            usuario.id =
                fila["id_usuario"].as<int>();

            usuario.nombre =
                fila["nombre"].as<string>();

            usuario.usuario =
                fila["usuario"].as<string>();

            usuario.password =
                fila["password"].as<string>();

            usuario.rol =
                fila["rol"].as<string>();

            usuarios.push_back(usuario);
        }

        transaccion.commit();
    }
    catch (const exception& e) {

        cout
            << "Error obtener usuarios: "
            << e.what()
            << endl;
    }

    return usuarios;
}

bool UsuarioDAO::eliminarUsuario(int id) {

    try {

        ConexionBD conexionBD;
        pqxx::connection conexion =
            conexionBD.conectar();

        pqxx::work transaccion(conexion);

        transaccion.exec_params(
            "DELETE FROM usuarios "
            "WHERE id_usuario = $1",
            id
        );

        transaccion.commit();
        return true;
    }
    catch (const exception& e) {

        cout
            << "Error eliminar usuario: "
            << e.what()
            << endl;

        return false;
    }
}