#pragma once

#include <vector>
#include <string>

using namespace std;

struct Corte {
    int id;
    string fecha;
    string descripcion;
    string vendedor;
    float total;
};

class CorteDAO {
public:
    vector<Corte> obtenerCortes();
};