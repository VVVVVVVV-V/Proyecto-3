#if !defined(_USUARIO_H_)
#define _USUARIO_H_

#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

class Usuario{
    private:
        std::string nombre, rut;
        std::vector<std::string> libroSolicitado;
    
    public:
        //constructor
        Usuario(std::string nNombre="null", std::string nRut="null", std::vector<std::string> nLibroSolicitado={});

        //setters
        void setRut(std::string nRut);
        void setNombre(std::string nNombre);
        
        //getters
        std::string getRut();
        std::string getNombre();
        
        //funciones del vector libroSolicitado
        int getLibroSolicitadoSize();
        std::string getLibroSolicitadoPorIndex(int index);
        bool getLibroSolicitadoEmpty();

        //metodos propios
        void añadirLibros(std::string nLibroSolicitado);
        void eliminarLibros(std::string nLibroSolicitado);
        void mostrarInformacion();

};

#endif