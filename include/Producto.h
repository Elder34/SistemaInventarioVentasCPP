#pragma once
#include <string>

using namespace std;

class Producto {
private:
    int id;
    string nombre;
    float precio;
    int stock;
    string categoria;

public:
    Producto();
    Producto(int id, string nombre, float precio, int stock, string categoria);

    int getId();
    string getNombre();
    float getPrecio();
    int getStock();
    string getCategoria();

    void setNombre(string nombre);
    void setPrecio(float precio);
    void setStock(int stock);
    void setCategoria(string categoria);
};