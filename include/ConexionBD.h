#pragma once
//Libreria de conexion
#include <pqxx/pqxx>
#include <string>

using namespace std;

//clase para conexion a base de datos
class ConexionBD {
private:
    //Almacena la configuración de conexión a PostgreSQL.
    string cadenaConexion;

public:
    ConexionBD();
    //Abre y devuelve una conexión activa a PostgreSQL.
    pqxx::connection conectar();
};