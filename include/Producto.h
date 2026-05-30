//Permite almacenar y manipular la información de los productos registrados.

#pragma once
#include <string>

using namespace std;

class Producto {
private:

    //Funcion de atributos
    int id;
    string nombre;
    float precio;
    int stock;
    string categoria;

public:
    //Permiten crear objetos producto vacíos o con información completa.
    Producto();
    Producto(int id, string nombre, float precio, int stock, string categoria);

    //Permiten consultar la información del producto.
    int getId();
    string getNombre();
    float getPrecio();
    int getStock();
    string getCategoria();

    //Permiten modificar los datos del producto
    void setNombre(string nombre);
    void setPrecio(float precio);
    void setStock(int stock);
    void setCategoria(string categoria);
};