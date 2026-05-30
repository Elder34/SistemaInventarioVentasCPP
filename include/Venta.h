//Permite almacenar la información principal de cada transacción registrada.

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

    //Inicializa el objeto venta para almacenar información de una transacción.
    Venta();

    //Permiten consultar la información almacenada de una venta.
    int getId();
    string getFecha();
    string getCliente();
    string getDescripcion();
    string getVendedor();
    float getTotal();

    //Permiten modificar los datos de la venta.
    void setId(int id);
    void setFecha(string fecha);
    void setCliente(string cliente);
    void setDescripcion(string descripcion);
    void setVendedor(string vendedor);
    void setTotal(float total);
};