#pragma once
#include <pqxx/pqxx>
#include <string>

using namespace std;

class ConexionBD {
private:
    string cadenaConexion;

public:
    ConexionBD();

    pqxx::connection conectar();
};