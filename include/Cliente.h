#pragma once //Evita que el archivo de encabezado (.h) se cargue varias veces durante la compilación.


#include <string> //Libreria

using namespace std;

//Clase privada
class Cliente {
private:
    int id;
    string nombre;
    string telefono;
    string correo;
    string nit;

    //clase cliente
public:

    //constructor
    Cliente();

    //constructor con parametros
    Cliente(int id, string nombre, string telefono, string correo, string nit);

    int getId();
    string getNombre();
    string getTelefono();
    string getCorreo();
    string getNit();


    //metodos set permiten modificar la información del cliente.
    void setId(int id);
    void setNombre(string nombre);
    void setTelefono(string telefono);
    void setCorreo(string correo);
    void setNit(string nit);
};