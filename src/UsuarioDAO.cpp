#include "UsuarioDAO.h"
#include "ConexionBD.h"

#include <pqxx/pqxx>
#include <iostream>

using namespace std;

// Agrega un nuevo usuario al sistema
bool UsuarioDAO::agregarUsuario(
    string nombre,
    string usuario,
    string password,
    string rol
) {
    try {
        // Crear conexión con la base de datos
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        // Iniciar transacción SQL
        pqxx::work transaccion(conexion);

        // Insertar nuevo usuario en la tabla usuarios
        transaccion.exec_params(
            "INSERT INTO usuarios(nombre, usuario, password, rol) "
            "VALUES($1, $2, $3, $4)",
            nombre,
            usuario,
            password,
            rol
        );

        // Guardar cambios
        transaccion.commit();
        return true;
    }
    catch (const exception& e) {

        // Mostrar error si ocurre un problema
        cout << "Error agregar usuario: "
            << e.what() << endl;
        return false;
    }
}

// Obtiene todos los usuarios registrados
vector<Usuario> UsuarioDAO::obtenerUsuarios() {

    // Vector para almacenar usuarios
    vector<Usuario> usuarios;

    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        // Consulta SQL para obtener usuarios
        pqxx::result resultado = transaccion.exec(
            "SELECT id_usuario, nombre, usuario, password, rol "
            "FROM usuarios "
            "ORDER BY id_usuario ASC"
        );

        // Recorrer resultados obtenidos
        for (auto fila : resultado) {

            // Crear objeto usuario temporal
            Usuario usuario;

            // Asignar datos obtenidos
            usuario.id = fila["id_usuario"].as<int>();

            usuario.nombre = fila["nombre"].is_null()
                ? ""
                : fila["nombre"].as<string>();

            usuario.usuario = fila["usuario"].is_null()
                ? ""
                : fila["usuario"].as<string>();

            usuario.password = fila["password"].is_null()
                ? ""
                : fila["password"].as<string>();

            usuario.rol = fila["rol"].is_null()
                ? ""
                : fila["rol"].as<string>();

            // Guardar usuario en el vector
            usuarios.push_back(usuario);
        }

        transaccion.commit();
    }
    catch (const exception& e) {
        cout << "Error obtener usuarios: "
            << e.what() << endl;
    }

    return usuarios;
}

// Actualiza los datos de un usuario existente
bool UsuarioDAO::actualizarUsuario(
    int id,
    string nombre,
    string usuario,
    string password,
    string rol
) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        // Modificar información del usuario
        transaccion.exec_params(
            "UPDATE usuarios "
            "SET nombre = $1, usuario = $2, password = $3, rol = $4 "
            "WHERE id_usuario = $5",
            nombre,
            usuario,
            password,
            rol,
            id
        );

        transaccion.commit();
        return true;
    }
    catch (const exception& e) {
        cout << "Error actualizar usuario: "
            << e.what() << endl;
        return false;
    }
}

// Elimina un usuario usando su ID
bool UsuarioDAO::eliminarUsuario(int id) {
    try {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        // Eliminar usuario de la tabla
        transaccion.exec_params(
            "DELETE FROM usuarios WHERE id_usuario = $1",
            id
        );

        transaccion.commit();
        return true;
    }
    catch (const exception& e) {
        cout << "Error eliminar usuario: "
            << e.what() << endl;
        return false;
    }
}