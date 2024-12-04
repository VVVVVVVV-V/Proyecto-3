#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <vector>
#include "Usuario.h"

using namespace std;

Usuario::Usuario(string nNombre, string nRut, vector<string> nLibroSolicitado): nombre(nNombre), rut(nRut), libroSolicitado(nLibroSolicitado){}

void Usuario::setRut(string nRut)
{
    if(nRut.length() > 0) rut=nRut;
    else cout << "Rut Inválido" << endl;
};

void Usuario::setNombre(string nNombre)
{
    if(nNombre.length() > 0) nombre=nNombre;
    else cout << "Nombre Inválido" <<endl;
};

string Usuario::getNombre()
{
    return nombre;
};

string Usuario::getRut()
{
    return rut;
};

int Usuario::getLibroSolicitadoSize()
{
    return(libroSolicitado.size());
};

string Usuario::getLibroSolicitadoPorIndex(int index)
{
    return(libroSolicitado[index]);
};

void Usuario::añadirLibros(string nLibroSolicitado)
{
    libroSolicitado.push_back(nLibroSolicitado);
};

bool Usuario::getLibroSolicitadoEmpty()
{
    return(libroSolicitado.empty()); //Devuelve un true si la lista esta vacia. 
};

void Usuario::eliminarLibros(string nLibroSolicitado)
{
    libroSolicitado.erase(find(libroSolicitado.begin(), libroSolicitado.end(), nLibroSolicitado));
};


void Usuario::mostrarInformacion()
{
    cout << "Nombre: "<< getNombre() << endl <<  "Rut: "<< getRut() << endl;
    
    if(!libroSolicitado.empty())
    {
        cout << "Libros que han sido prestados a " << getNombre() << ": " << endl;
        for (int i = 0; i < libroSolicitado.size(); i++)
        {
            cout << i+1 << ") " << libroSolicitado[i] << endl;
        }
        
    }
    else cout << getNombre() << " no ha pedido prestado ningun libro." << endl;
};