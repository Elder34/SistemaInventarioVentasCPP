//Gestión el Historial de Cortes de Venta

#pragma once
//Librerias
#include <vector>
#include <string>

using namespace std;

struct Corte {
    int id;
    string fecha;
    string descripcion;
    string vendedor;
    float total;
    string metodoPago;
};
//clase
class CorteDAO {
public:

    //Se usa para almacenar múltiples cortes
    vector<Corte> obtenerCortes();
    
};