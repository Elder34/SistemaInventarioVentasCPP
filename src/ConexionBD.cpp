#include "ConexionBD.h"

// Constructor de la clase ConexionBD
ConexionBD::ConexionBD() {

    // Cadena de conexión utilizada para acceder a PostgreSQL
    // Contiene los datos necesarios para conectarse a la base de datos
    cadenaConexion =
        "host=localhost "      // Dirección del servidor de base de datos
        "port=5432 "           // Puerto por defecto de PostgreSQL
        "dbname=inventario_ventas " // Nombre de la base de datos
        "user=postgres "       // Usuario de PostgreSQL
        "password=41820589";   // Contraseña del usuario
}

// Método encargado de crear y devolver una conexión
pqxx::connection ConexionBD::conectar() {

    // Retorna una nueva conexión usando la cadena definida
    return pqxx::connection(cadenaConexion);
}