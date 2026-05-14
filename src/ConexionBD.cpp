#include "ConexionBD.h"

ConexionBD::ConexionBD() {
    cadenaConexion =
        "host=localhost "
        "port=5432 "
        "dbname=inventario_ventas "
        "user=postgres "
        "password=41820589";
}

pqxx::connection ConexionBD::conectar() {
    return pqxx::connection(cadenaConexion);
}