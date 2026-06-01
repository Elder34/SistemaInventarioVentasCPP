#include "Producto.h"

// Constructor vacío
Producto::Producto() {
    id = 0;
    codigo = "";
    nombre = "";
    precio = 0.0f;
    stock = 0;
    categoria = "";
}

// Constructor con parámetros
Producto::Producto(
    int id,
    string codigo,
    string nombre,
    float precio,
    int stock,
    string categoria
) {
    this->id = id;
    this->codigo = codigo;
    this->nombre = nombre;
    this->precio = precio;
    this->stock = stock;
    this->categoria = categoria;
}

// GET
int Producto::getId() {
    return id;
}

string Producto::getCodigo() {
    return codigo;
}

string Producto::getNombre() {
    return nombre;
}

float Producto::getPrecio() {
    return precio;
}

int Producto::getStock() {
    return stock;
}

string Producto::getCategoria() {
    return categoria;
}

// SET
void Producto::setCodigo(string codigo) {
    this->codigo = codigo;
}

void Producto::setNombre(string nombre) {
    this->nombre = nombre;
}

void Producto::setPrecio(float precio) {
    this->precio = precio;
}

void Producto::setStock(int stock) {
    this->stock = stock;
}

void Producto::setCategoria(string categoria) {
    this->categoria = categoria;
}