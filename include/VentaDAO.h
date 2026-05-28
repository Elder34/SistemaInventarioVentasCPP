#pragma once

#include <string>
#include <vector>
#include "Venta.h"

using namespace std;

class VentaDAO {
public:
    bool registrarVenta(
        string cliente,
        string descripcion,
        string vendedor,
        float total,
        string metodoPago
    );
    vector<Venta> obtenerVentas();
};