#include "Venta.h"

Venta::Venta() {
    id = 0;
    fecha = "";
    cliente = "";
    descripcion = "";
    vendedor = "";
    total = 0.0f;
}

int Venta::getId() { return id; }
string Venta::getFecha() { return fecha; }
string Venta::getCliente() { return cliente; }
string Venta::getDescripcion() { return descripcion; }
string Venta::getVendedor() { return vendedor; }
float Venta::getTotal() { return total; }

void Venta::setId(int id) { this->id = id; }
void Venta::setFecha(string fecha) { this->fecha = fecha; }
void Venta::setCliente(string cliente) { this->cliente = cliente; }
void Venta::setDescripcion(string descripcion) { this->descripcion = descripcion; }
void Venta::setVendedor(string vendedor) { this->vendedor = vendedor; }
void Venta::setTotal(float total) { this->total = total; }