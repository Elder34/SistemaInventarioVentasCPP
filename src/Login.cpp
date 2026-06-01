#include "Login.h"
#include "ConexionBD.h"

#include <pqxx/pqxx>
#include <iostream>

using namespace std;

bool Login::validarUsuario(string usuario, string password)
{
    try
    {
        ConexionBD conexionBD;
        pqxx::connection conexion = conexionBD.conectar();

        pqxx::work transaccion(conexion);

        pqxx::result resultado = transaccion.exec_params(
            "SELECT rol FROM usuarios WHERE usuario=$1 AND password=$2",
            usuario,
            password
        );

        transaccion.commit();

        if (!resultado.empty())
        {
            rolUsuario = resultado[0]["rol"].c_str();
            return true;
        }

        rolUsuario = "";
        return false;
    }
    catch (const exception& e)
    {
        cout << "Error login: " << e.what() << endl;
        return false;
    }
}

string Login::getRolUsuario()
{
    return rolUsuario;
}