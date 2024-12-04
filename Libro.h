#if !defined(_LIBRO_H_)
#define _LIBRO_H_

#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <string>

//Creacion de la clase libro.

class Libro
{
    // Definicion de atributos privados.
    private:
        std::string titulo, autor, editorial, genero, idioma;
        int id, numeroPaginas, stock, anioDePublicacion, librosPrestados=0;
        bool disponibilidad;
        std::vector<std::string> nombrePrestado; //Vector dinamico de nombres a los que se les ha prestado el libro.
        //Por disponibilidad entiendo si es que el libro se encuentra disponible, por ende pienso que debe ser un booleano.

    //Definicion de metodos publicos.
    public:
        //Definicion del constructor.
        Libro(std::string nTitulo="null", std::string nAutor="null", std::string nEditorial="null", int nAnioDePublicacion=0, std::string nGenero="null", std::string nIdioma="null", int nId=0, int nNumeroPaginas=0, int nStock=0, bool nDisponibilidad=true, int nLibrosPrestados=0, std::vector<std::string> nNombrePrestado= {});

        //setters
        void setTitulo(std::string nTitulo);
        void setAutor(std::string nAutor);
        void setEditorial(std::string nEditorial);
        void setAnioDePublicacion(int nAnioDePublicacion);
        void setGenero(std::string nGenero);
        void setIdioma(std::string nIdioma);
        void setId(int nId);
        void setNumeroPaginas(int nNumeroPaginas);
        void setStock(int nStock);
        void setDisponibilidad(bool nDisponibilidad);


        //getters
        std::string getTitulo();
        std::string getAutor();
        std::string getEditorial();
        int getAnioDePublicacion();
        std::string getGenero();
        std::string getIdioma();
        int getId();
        int getNumeroPaginas();
        int getStock();
        bool getDisponibilidad();
        int getLibrosPrestados();

        //Funciones del Vector nombrePrestado;
        int getNombrePrestadoSize(); //Devuelve el tamaño del vector
        std::string getNombrePrestadoPorIndex(int index); //Devuelve la string que se encuentra contenida en un index
        bool nombrePrestadoEmpty(); //Si el vector esta vacio devuelve un true
        void añadirNombrePrestado(std::string nombre); //Añade un nombre al vector nombrePrestado

        //funciones propias
        std::string disponibleOno();
        void mostrarInformacion();
        void prestarLibro(std::string nombrePersona); //Estas funciones tienen que quedar registradas en algun lado, tiene que haber un registro de cuando se presta o devuelve un libro, o bien eso se pude hacer en el programa principal para simplificar las cosas.
        void devolverLibro(std::string nombrePersona); 
        void modificarStock(int modificador); //Usando numeros positivos o negativos para alterar el stock.
        

};

#endif