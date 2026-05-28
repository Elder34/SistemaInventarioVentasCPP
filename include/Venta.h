#pragma once
#include <string>
using namespace std;

class Venta {
private:
    int id;
    string fecha;
    string cliente;
    string descripcion;
    string vendedor;
    float total;

public:
    Venta();

    int getId();
    string getFecha();
    string getCliente();
    string getDescripcion();
    string getVendedor();
    float getTotal();

    void setId(int id);
    void setFecha(string fecha);
    void setCliente(string cliente);
    void setDescripcion(string descripcion);
    void setVendedor(string vendedor);
    void setTotal(float total);
};