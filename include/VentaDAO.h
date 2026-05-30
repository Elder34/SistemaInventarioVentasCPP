//administra la comunicación entre el sistema y la base de datos para registrar y consultar ventas.

#pragma once

#include <string>
#include <vector>
#include "Venta.h"

using namespace std;

class VentaDAO {
public:

    //Registra una nueva venta en la base de datos.
    bool registrarVenta(
        string cliente,
        string descripcion,
        string vendedor,
        float total,
        string metodoPago
    );

    //Obtiene el historial de ventas almacenado en el sistema.
    vector<Venta> obtenerVentas();//Lista completa de ventas registradas.
};