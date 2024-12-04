#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

#include "Libro.h"

using namespace std;

//CONSTRUCTOR
/*--------------------------------------------*/

Libro::Libro(string nTitulo, string nAutor, string nEditorial, int nAnioDePublicacion, string nGenero, string nIdioma, int nId, int nNumeroPaginas, int nStock, bool nDisponibilidad, int nLibrosPrestados, vector<string> nNombrePrestado): titulo(nTitulo), autor(nAutor), editorial(nEditorial), anioDePublicacion(nAnioDePublicacion), genero(nGenero), idioma(nIdioma), id(nId), numeroPaginas(nNumeroPaginas), stock(nStock), disponibilidad(nDisponibilidad), librosPrestados(nLibrosPrestados), nombrePrestado(nNombrePrestado){}

//SETTERS
/*--------------------------------------------*/

void Libro::setTitulo(string nTitulo)
{
    if(nTitulo.length() > 0) titulo=nTitulo;
    else cout << "Título Inválido." << endl;
};

void Libro::setAutor(string nAutor)
{
    if(nAutor.length() > 0) autor=nAutor;
    else cout << "Autor Inválido." << endl;
};

void Libro::setEditorial(string nEditorial)
{
    if(nEditorial.length() > 0) editorial=nEditorial;
    else cout << "Editorial Inválida." << endl;
};

void Libro::setAnioDePublicacion(int nAnioDePublicacion)
{
    if(nAnioDePublicacion > 0) anioDePublicacion=nAnioDePublicacion;
    else cout << "Año de publicacion Inválido." << endl;  
};

void Libro::setGenero(string nGenero)
{
    if(nGenero.length() > 0) genero=nGenero;
    else cout << "Género Inválido." << endl;  
};

void Libro::setIdioma(string nIdioma)
{
    if(nIdioma.length() > 0) idioma=nIdioma;
    else cout << "Idioma Inválido." << endl;
};

void Libro::setId(int nId)
{
    if(nId > 0) id=nId;
    else cout << "Id Inválido."  << endl;
};

void Libro::setNumeroPaginas(int nNumeroPaginas)
{
    if(nNumeroPaginas > 0) numeroPaginas=nNumeroPaginas;
    else cout << "Número de páginas Inválido." << endl;
};

void Libro::setStock(int nStock)
{
    if(nStock > 0) stock=nStock;
    else
    {
        stock=0;
        setDisponibilidad(false);
    }    
};

void Libro::setDisponibilidad(bool nDisponibilidad)
{
    disponibilidad=nDisponibilidad;
};

//GETTERS
/*--------------------------------------------*/
string Libro::getTitulo()
{
    return(titulo);
};

string Libro::getAutor()
{
    return(autor);
};

string Libro::getEditorial()
{
    return(editorial);
}

int Libro::getAnioDePublicacion()
{
    return(anioDePublicacion);
};

string Libro::getGenero()
{
    return(genero);
};

string Libro::getIdioma()
{
    return(idioma);
};

int Libro::getId()
{
    return(id);
};

int Libro::getNumeroPaginas()
{
    return(numeroPaginas);
};

int Libro::getStock()
{
    return(stock);
};

bool Libro::getDisponibilidad()
{
    return(disponibilidad);
};

int Libro::getLibrosPrestados()
{
    return(librosPrestados);
};

//FUNCIONES DEL VECTOR NOMBREPRESTADO
/*--------------------------------------------*/

int Libro::getNombrePrestadoSize()
{
    return(nombrePrestado.size()); //Retorna el tamaño del vector como un numero entero
};

string Libro::getNombrePrestadoPorIndex(int index)
{
    return(nombrePrestado[index]); //Retorna la string contenida en un index x
};

bool Libro::nombrePrestadoEmpty()
{
    return(nombrePrestado.empty()); //Devuelve un true si la lista esta vacia
}

void Libro::añadirNombrePrestado(string nombre)
{
    nombrePrestado.push_back(nombre); //Añade al final del vector el nombre de la persona a la que fue prestado el libro
};


//FUNCIONES PROPIAS
/*--------------------------------------------*/

string Libro::disponibleOno()
{
    if(getDisponibilidad() == true) return("Si.");
    else return("No.");
};

void Libro::mostrarInformacion()
{
    cout << "Titulo: " << getTitulo() << endl << "Autor: " << getAutor() << endl << "Editorial: " << getEditorial() << endl << "Anio de Publicacion: " << getAnioDePublicacion() << endl << "Genero: " << getGenero() << endl << "Idioma: " << getIdioma() << endl << "Numero de Paginas: " << getNumeroPaginas() << endl << "Stock: " << getStock() << endl << "Disponibilidad: " << disponibleOno() << endl << "Disponibilidad Virtual: Si." << endl;
    //Si se ha prestado un libro y la lista no esta vacia.
    if( getLibrosPrestados() > 0 && !nombrePrestadoEmpty())
    {
        //Imprime una lista de las personas a las que ha sido prestado este libro.
        cout << "Libros prestados: " << getLibrosPrestados() << endl << "Personas a las que se les ha prestado este libro: " << endl;
        for (int i = 0; i < nombrePrestado.size(); i++)
        {
            cout << i+1 << ") " << nombrePrestado[i] << "." << endl;
        }
        
    }
};

void Libro::modificarStock(int modificador)
{
    stock+=modificador;
    if(stock <= 0)
    {
        stock = 0;
        setDisponibilidad(false);
    }
    else setDisponibilidad(true);
};

void Libro::prestarLibro(string nombrePersona)
{
    //Si el stock es 1 o mas resta uno al stock y añade el nombre de la persona a la que fue prestado el libro al vector que guarda quienes han rentado este libro.
    if(getStock() > 0)
    {
        modificarStock(-1);
        cout << "El libro " << getTitulo() << " ha sido prestado con exito a " << nombrePersona << "."<< endl;
        añadirNombrePrestado(nombrePersona);
        librosPrestados+=1;
    }
    else cout << "No quedan existencias de este libro." << endl;
};

void Libro::devolverLibro(string nombrePersona)
{
    //Si es que la lista de personas que han pedido el libro prestado no tiene elementos no deja devolver el libro, si en cambio la lista tiene al menos un elemento si deja.
    if(nombrePrestado.size() > 0)
    {
        modificarStock(1);
        cout << "El libro " << getTitulo() << " ha sido devuelto con exito por parte de " << nombrePersona << "."<< endl;
        nombrePrestado.erase(find(nombrePrestado.begin(), nombrePrestado.end(), nombrePersona));
        librosPrestados-=1;
    }
    else cout << "No se puede devolver un libro que no ha sido prestado." << endl;
};