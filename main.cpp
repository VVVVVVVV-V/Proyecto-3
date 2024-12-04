#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <fstream>
#include <sstream>
#include "Usuario.h"
#include "Libro.h"
#include "text_management.h"

// Se define un "pass" que no hace nada, lo necesitamos para las estructuras de tipo
// (condicion) ? (si es verdadero) : (si es falso) y como no necesitamos hacer nada
// en alguno de los dos casos, se utiliza para que no se haga nada.
#define pass (void)0

using namespace std;

void limpiarPantalla()
{
    //Si el sistema operativo es windows usara "cls", si es linux usara "clear".
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux y macOS
    #endif
}

void pulsaEnter()
{
    
    cout << "Pulsa enter para continuar..." << endl;
    cin.clear(); //Limpia el buffer de entrada
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Para que funcione el cin.get(), limpia el buffer de entrada
    cin.get();

}

void mostrarBiblioteca(vector<Libro> nombreVector)
{
    if(!nombreVector.empty())
    {

        for (int i = 0; i < nombreVector.size(); i++)
        {
            cout << i+1 << ") " << nombreVector[i].getTitulo() << endl;
        }
    }
    else cout << "No hay elementos que mostrar..." << endl;
}

void mostrarBibliotecaConStock(vector<Libro> nombreVector)
{
    if(!nombreVector.empty())
    {

        for (int i = 0; i < nombreVector.size(); i++)
        {
            if(nombreVector[i].getStock() > 0) cout << i+1 << ") " << nombreVector[i].getTitulo() << " ; Id: "<< nombreVector[i].getId() <<endl;
        }
    }
    else cout << "No hay elementos que mostrar..." << endl;
};

void mostrarUsuarios(vector<Usuario> nombreVector)
{
    if(!nombreVector.empty())
    {
        for (int i = 0; i < nombreVector.size(); i++)
        {
            cout << i+1 << ") " << nombreVector[i].getNombre() << endl;
        }
    }
    else cout << "No hay elementos que mostrar..." << endl;
}

void mostrarUsuariosPrestados(vector<Usuario> nombreVector)
{
    bool aux=false;
    if(!nombreVector.empty())
    {
        for (int i = 0; i < nombreVector.size(); i++)
        {
            if(!nombreVector[i].getLibroSolicitadoEmpty())
            {
                cout << "- " << nombreVector[i].getNombre() << endl;
                aux=true;
            }
            
        }
    }
    else if(aux == false) cout << "No hay elementos que mostrar..." << endl;
}

void editarLibro(Libro libro, string nTitulo, string nAutor, string nEditorial, int nAnioDePublicacion, string nGenero, string nIdioma, int nId, int nNumeroPaginas, int nStock)
{
    libro.setTitulo(nTitulo);
    libro.setAutor(nAutor);
    libro.setEditorial(nEditorial);
    libro.setAnioDePublicacion(nAnioDePublicacion);
    libro.setGenero(nGenero);
    libro.setIdioma(nIdioma);
    libro.setId(nId);
    libro.setNumeroPaginas(nNumeroPaginas);
    libro.setStock(nStock);
}

int main(int argc, char const *argv[])
{
    // Verificamos que exista un archivo de texto con la fecha de hoy, si no existe lo creamos.
    check_register();
    
    //Variables auxiliares generales
    bool contr_while = true;
    int controlador_aux=0;
    int controlador_aux_prestamo=0;
    bool controlador_prestamo;
    
    //Vector dinamico para almacenar los libros de la biblioteca
    vector<Libro> biblioteca;
    vector<Usuario> usuarios;
    vector<string> historial;

    //En caso de no existir, instanciamiento de los archivos de texto.
    ifstream file;
    file.open("libros.txt");
    (file) ? pass : rewrite_txt(biblioteca, "libros.txt");
    file.close();
    file.open("usuarios.txt");
    (file) ? pass : rewrite_users(usuarios, "usuarios.txt");
    file.close();
    
    //Controlador que controlara el bucle del menu.
    int controlador = 0;

    //Variables auxiliares para crear libros.
    string nTitulo, nAutor, nEditorial, nGenero, nIdioma;
    int nId, nNumeroPaginas, nStock, nAnioDePublicacion;
    bool nDisponibilidad;

    //Variables auxiliares para crear usuarios.
    string nNombreUsuario, nRutUsuario;

    //Variable auxiliar para los procesos 3, 4, 9 y 10.
    string nombreGenericoParaBuscar;

    //Lectura de los archivos de texto para añadir sus elementos a los vectores dinamicos.
    read_txt(biblioteca, "libros.txt"); 
    read_users(usuarios, "usuarios.txt");

    while (contr_while)
    {
        limpiarPantalla();
        //Imprimir pantalla del menu.
        cout << "Bienvenido!" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "1) Agregar Libros." << endl << "2) Agregar Usuario." << endl << "3) Prestar Libro." << endl << "4) Devolver libro." << endl << "5) Ver la lista de libros." << endl << "6) Ver la lista de usuarios." << endl << "7) Ver detalles de un libro." << endl << "8) Ver detalles de un usuario." << endl << "9) Buscar un libro." << endl << "10) Buscar un usuario." << endl << "11) Editar Libros." << endl << "12) Editar usuarios." << endl << "13) Mostrar el registro de auditoria. " << endl << "14) Guardar y salir." << endl << "> ";
        cin >> controlador;
        //controla si es que en el controlador ingresan texto
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            controlador = 0;
        } 
        limpiarPantalla();
        //Usar un switch tiraba errores al instanciar un objeto, asi que toco usar puro if
        
        //Agregar libros.
        if(controlador == 1)
        {
            //Pedir los parametros para instanciar un objeto Libro.
            cout << "Ingrese el nombre del libro: ";
            //Limpia el buffer tras haber ingresado el valor del controlador.
            cin.ignore(); 
            getline(cin, nTitulo);
            cout << endl << "Ingrese el nombre del Autor del libro: ";
            getline(cin, nAutor);
            cout << endl << "Ingrese la editorial del libro: ";
            getline(cin, nEditorial);
            cout << endl << "Ingrese el genero del libro: ";
            getline(cin, nGenero);
            cout << endl << "Ingrese el idioma del libro: ";
            getline(cin, nIdioma);
            //si la lista tiene elementos entonces mostrara el id del ultimo libro añadido.
            if(!biblioteca.empty()) cout << endl << "Ingrese el Id del libro (ultimo id registrado es [" << biblioteca.back().getId() << "]): ";
            else cout << endl << "Ingrese el Id del libro: ";
            cin >> nId;
            cout << endl << "Ingrese el numero de paginas del libro: ";
            cin >> nNumeroPaginas;
            cout << endl << "Ingrese el stock del libro: ";
            cin >> nStock;
            cout << endl << "Ingrese el anio de publicacion del libro: ";
            cin >> nAnioDePublicacion;

            //instanciacion del libro y añadir a la lista.
            Libro libro(nTitulo, nAutor, nEditorial, nAnioDePublicacion, nGenero, nIdioma, nId, nNumeroPaginas, nStock, true, 0, {});
            biblioteca.push_back(libro);
            register_new_book(historial, biblioteca.back());
            rewrite_txt(biblioteca, "libros.txt");
            pulsaEnter();
        }

        //AGREGAR USUARIOS
        else if(controlador == 2)
        {
            cout << "Ingrese el nombre del usuario: ";
            cin.ignore(); 
            getline(cin, nNombreUsuario);
            cout << endl << "Ingrese el rut del usuario: ";
            getline(cin, nRutUsuario);

            //Intanciacion del usuario y añadir a la lista.
            Usuario nuevousuario(nNombreUsuario, nRutUsuario, {});
            usuarios.push_back(nuevousuario);
            register_new_user(historial, usuarios.back());
            rewrite_users(usuarios, "usuarios.txt");
            pulsaEnter();

        }

        //
        //PRESTAR LIBROS
        else if(controlador == 3)
        {
            //Si hay libros y usuarios instanciados
            if(!biblioteca.empty() && !usuarios.empty())
            {
                //Pide ingresar por texto el nombre del libro.
                cout << "Libros disponibles: " << endl;
                mostrarBibliotecaConStock(biblioteca);
                cout << endl << "Que libro se desea prestar? (Ingrese el nombre)" << endl << "> ";
                cin.ignore(); 
                getline(cin, nombreGenericoParaBuscar);
                
                //Busca el libro en la biblioteca.
                for (int i = 0; i < biblioteca.size(); i++)
                {
                    //Si encuentra el libro en la biblioteca y tiene un stock mayor a 0.
                    if(biblioteca[i].getTitulo() == nombreGenericoParaBuscar && biblioteca[i].getStock() > 0)
                    {
                        
                        limpiarPantalla();
                        //Imprime que el libro esta disponible y muestra una lista de usuarios.
                        cout << "Libro disponible!" << endl << "----------------------------" << endl << "¿Desea pedir el libro de manera virtual o fisica?" << endl << "1) Fisica" << endl << "2) Digital" << endl << "> ";
                        cin >> controlador_aux;
                        //Si es que se quiere pedir prestado un libro fisico
                        if(controlador_aux == 1)
                        {
                            limpiarPantalla();
                            mostrarUsuarios(usuarios);
                            //Pregunta quien quiere pedir prestado el libro
                            cout << endl << "Que usuario desea pedir prestado este libro?" << endl << "> ";
                            cin >> controlador_aux;
                            //Verifica si es que el valor ingresado por el usuario es un index valido en la lista de usuarios.
                            if(controlador_aux <= usuarios.size() && controlador_aux > 0)
                            {
                                //Verifica que la lista de nombres del libro no tenga elementos
                                if(biblioteca[i].nombrePrestadoEmpty())
                                {
                                    //Cuando pasa esto, el programa pasa directamente a realizar el prestamo del libro
                                    controlador_prestamo=true;
                                }
                                
                                else
                                {
                                    //Verifica que la persona que quiera pedir no lo tenga prestado
                                    for (int j = 0; j < biblioteca[i].getNombrePrestadoSize(); j++)
                                    {
                                        //Si es que el usuario esta registrado en las personas que han alquilado el libro
                                        if(usuarios[controlador_aux-1].getNombre() == biblioteca[i].getNombrePrestadoPorIndex(j))
                                        {
                                        //Pasa por pantalla que el usuario no puede pedir el prestamo y hace la variable controlador_prestamo falsa.
                                            cout << "Este usuario no puede pedir prestado este libro puesto que ya tiene una copia en su poder." << endl;
                                            controlador_prestamo=false;
                                        }
                                        //Si el usuaro no esta registrado en las personas que han alquilado el libro, controlador_prestamo es verdadero.
                                        else controlador_prestamo=true;    
                                    }
                                    //Si el controlador prestamo es verdadero
                                    
                                }
                                if(controlador_prestamo)
                                {
                                    //El libro registra que fue prestado al usuario, y el usuario registra que tiene el libro.
                                    biblioteca[i].prestarLibro(usuarios[controlador_aux-1].getNombre());
                                    usuarios[controlador_aux-1].añadirLibros(biblioteca[i].getTitulo());
                                    cout << "Prestamo realizado con exito!" << endl;
                                    pulsaEnter();
                                }
                            }
                            //Si el valor ingresado el el controlador_aux no es valido como index entonces el prestamo pasa a ser falso.
                            else controlador_prestamo=false;
                        }
                        //Si es que el libro es virtual
                        else if(controlador_aux==2)
                        {
                            mostrarUsuarios(usuarios);
                            //Pregunta quien quiere pedir prestado el libro
                            cout << endl << "Que usuario desea pedir prestado este libro?" << endl << "> ";
                            cin >> controlador_aux;
                            
                            if(controlador_aux <= usuarios.size() && controlador_aux > 0)
                            {
                                //Si el libro no ha sido prestado a nadie automaticamente sera verdadero el prestamo
                                if(biblioteca[i].nombrePrestadoEmpty())
                                {
                                    controlador_prestamo=true;
                                }
                                else
                                {

                                }
                            }

                        }
                        //Si no es una opcion valida
                        else
                        {

                        }        
                    //Si no se encuentra el libro en la biblioteca.
                    }
                
                }
                //Si el controlador del prestamo es falso, retorna que el usuario o libro no se encontraban disponibles.
                if(controlador_prestamo==false)
                {
                    cout << "----------------------------------------" << endl << "Prestamo no realizado." << endl;
                    
                }    
            }
            //Lo que pasa si es que la bibloteca o usuarios estan vacios
            else
            {
                cout << "No hay libros o no hay usuarios...";
            }
            pulsaEnter();
        }

        //DEVOLVER LIBROS
        else if(controlador == 4)
        {
            controlador_prestamo=false;
            controlador_aux=0;
            //int revisor = 0;
            //Si la lista de usuarios no esta vacia.
            if(!usuarios.empty())
            {
                //Muestra los usuarios que han pedido prestado algun libro.
                mostrarUsuariosPrestados(usuarios);
                cout << "Que usuario desea devolver un libro? (Ingrese el nombre del usuario)" << endl << "> ";
                cin.ignore();
                getline(cin, nombreGenericoParaBuscar);
                //Busca el nombre del usuario en la lista de usuarios.
                for (int i = 0; i < usuarios.size(); i++)
                {
                    //Si el usuario se encuentra en la lista y tiene algun libro prestado
                    if(usuarios[i].getNombre() == nombreGenericoParaBuscar && !usuarios[i].getLibroSolicitadoEmpty())
                    {
                        limpiarPantalla();
                        //Imprime la lista de libros que ha pedido prestado el usuario.
                        for (int j= 0; j < usuarios[i].getLibroSolicitadoSize(); j++)
                        {
                            cout << j+1 << ") " << usuarios[i].getLibroSolicitadoPorIndex(j) << endl;
                        }
                        //Pregunta que libro de la lista se desea devolver 
                        cout << "Que libro desea devolver? Seleccione una opcion." << endl << "> ";
                        cin >> controlador_aux;
                        //Si la opcion ingresada esta en la lista
                        if(controlador_aux <= usuarios[i].getLibroSolicitadoSize() && controlador_aux > 0)
                        {
                            //Recorre la lista de la biblioteca buscando el libro que tenga el mismo nombre.
                            for (int j = 0; j < biblioteca.size(); j++)
                            {
                               //Si es que el titulo en la biblioteca coincide con el nombre del libro solicitado
                                if(biblioteca[j].getTitulo() == usuarios[i].getLibroSolicitadoPorIndex(controlador_aux-1))
                                {
                                    //Si encuentra el libro vuelve el controlador de prestamo verdadero
                                    controlador_prestamo=true;
                                    //Guarda el index del titulo del libro que se quiere devolver
                                    controlador_aux_prestamo=j;
                                    //Se define el revisor en 1, asi el prestamo sera efectivo.
                                    //revisor=1;
                                }
                            }
                        }
                    }
                    //Si el controlador de prestamo es verdadero va a devolver el libro usando el nombre del usuario que lo devuelve como parametro, y el usuario va a eliminar el libro usando el titulo del libro como parametro
                    if(controlador_prestamo)
                    {
                        biblioteca[controlador_aux_prestamo].devolverLibro(usuarios[i].getNombre());
                        usuarios[i].eliminarLibros(biblioteca[controlador_aux_prestamo].getTitulo());
                        pulsaEnter();
                        //Revisor se define en 0 para que el bucle no vuelva a esta parte
                        break;
                    }
                }
                //Si el prestamo es falso dira que no se ha podido realizar la devolucion.
                if(!controlador_prestamo)
                {
                    cout << "No se ha podido realizar la devolucion..." << endl;
                    pulsaEnter();
                }
            }
            controlador_aux=0;
            controlador_aux_prestamo=0;
            controlador_prestamo=false;
        }



        //Mostrar libros en biblioteca
        else if(controlador == 5)
        {
            mostrarBiblioteca(biblioteca);
            pulsaEnter();
        }
        

        //Mostrar usuarios registrados.
        else if(controlador == 6)
        {
            mostrarUsuarios(usuarios);
            pulsaEnter();
        }


        //Verificar detalles de un libro en la lista.
        else if(controlador == 7)
        {
            //Si el vector biblioteca tiene algun elemento
            if(!biblioteca.empty())
            {
                //Muestra el vector biblioteca y pregunta al usuario
                mostrarBiblioteca(biblioteca);
                cout << "De que libro desea verificar los detalles?" << endl << "> ";
                cin >> controlador_aux;
                if(controlador_aux <= biblioteca.size() && controlador_aux > 0)
                {
                    biblioteca[controlador_aux-1].mostrarInformacion();
                    controlador_aux=0;
                }
                else cout << "Opcion invalida..." << endl;
            }
            else cout << "No hay libros en la biblioteca." << endl;
            pulsaEnter();
        }


        //Verificar detalles de un usuario en la lista.
        else if(controlador == 8)
        {
            //Si es que la lista de usuarios tiene al menos un elemento.
            if(!usuarios.empty())
            {
                //Muestra una lista con los usuarios y pregunta cual se desea revisar.
                mostrarUsuarios(usuarios);
                cout << "De que usuario desea verificar los detalles?" << endl << "> ";
                cin >> controlador_aux;
                if(controlador_aux <= usuarios.size() && controlador_aux > 0)
                {
                    usuarios[controlador_aux-1].mostrarInformacion();
                    controlador=0;
                }
                else cout << "Opcion invalida..." << endl;
            }
            else
            {
                cout << "No hay usuarios registrados." << endl;
            }
            pulsaEnter();
        }


        //Buscar un libro especifico.
        else if(controlador == 9)
        {
            //Si es que biblioteca tiene algun elemento
            if(!biblioteca.empty())
            {
                cout << "Ingrese el titulo del libro que desea buscar: ";
                cin.ignore(); 
                getline(cin, nombreGenericoParaBuscar);
                //Busca un nombre de un libro especifico.
                controlador_aux=0;
                for (int i = 0; i < biblioteca.size(); i++)
                {
                    //Revisa en la lista si se encuentra en nombre que se desea
                    if (biblioteca[i].getTitulo() == nombreGenericoParaBuscar)
                    {
                    //Si lo encuentra muestra la informacion de ese libro
                    biblioteca[i].mostrarInformacion();
                    controlador_aux = 1;
                    }
                }
                //Si no lo encuentra muestra por pantalla que no hay coincidencias.
                if(controlador_aux != 1) cout << "No se han encontrado coincidencias..." << endl;
                controlador_aux=0;
            }
            else cout << "No hay libros registrados." << endl;
            pulsaEnter();
            
            
        }

        //Buscar detalles de un usuario por nombre
        else if(controlador == 10)
        {
            //Si es que la lista de usuarios tiene algun elemento
            if(!usuarios.empty())
            {
                cout << "Ingrese el nombre del usuario que desea buscar: " << endl << " >";
                cin.get();
                getline(cin, nombreGenericoParaBuscar);
                //Se define un controlador auxiliar a 0, puesto que si no se encuentran coincidencias lo mostara en pantalla.
                controlador_aux=0;
                //Busca en la lista de usuarios coincidencias usando el nombre ingresado.
                for (int i = 0; i < usuarios.size(); i++)
                {
                    if(usuarios[i].getNombre() == nombreGenericoParaBuscar)
                    {
                        //Muestra la informacion y cambia un controlador a 1, si fuese 0 se mostraria en pantalla que no hay coincidencias.
                        usuarios[i].mostrarInformacion();
                        controlador_aux=1;
                    }
                }
                if(controlador_aux != 1)
                {
                    cout << "No se han encontrado coincidencias..." << endl;
                }
            }
            //Si la lista no tiene elementos muestra en pantalla que no hay usuarios registrados.
            else cout << "No hay usuarios registrados." << endl;
            pulsaEnter();
        }

        //EDITAR LIBROS
        else if(controlador == 11)
        {
            //Si es que la biblioteca no esta vacia.
            if(!biblioteca.empty())
            {
                //Recorrer la lista de la biblioteca e imprimir los libros que no han sido prestados a nadie.
                controlador_aux=0;
                for(int i=0; i < biblioteca.size(); i++)
                {
                    //Si es que el libro no ha sido prestado a nadie.
                    if(biblioteca[i].nombrePrestadoEmpty())
                    {
                        
                        cout << i+1 << ") " << biblioteca[i].getTitulo() << endl;
                        //Si hay libros que no han sido prestados controlador aux va a ser 1, si no hay sera 0.
                        controlador_aux=1;
                    }
                }
                //Si hay libros que no han sido prestados se entrara al menu.
                if(controlador_aux=1)
                {
                    cout << "Ingrese el libro que desea editar (ingrese su nombre): " << endl << "> ";
                    cin.get();
                    getline(cin, nombreGenericoParaBuscar);
                    //Verifica que haya coincidencias con el titulo y revisa nuevamente que no haya sido prestado a nadie.
                    for (int i = 0; i < biblioteca.size(); i++)
                    {
                        if(biblioteca[i].getTitulo() == nombreGenericoParaBuscar && biblioteca[i].nombrePrestadoEmpty())
                        {
                            //Inicia un menu para consultar al usuario que desea cambiar del libro.
                            limpiarPantalla();
                            cout << "Libro encontrado!" << endl << "--------------------------" << endl << "1) Editar Titulo" << endl << "2) Editar Autor" << endl << "3) Editar Editorial" << endl << "4) Editar Anio de Publicacion" << endl << "5) Editar Genero" << endl << "6) Editar Idioma" << endl << "7) Editar Id" << endl << "8) Editar Numero de Paginas" << endl << "9) Editar Stock" << endl << "> ";
                            cin >> controlador_aux;
                            //Limpia el input
                            cin.get();
                            limpiarPantalla();
                            switch (controlador_aux)
                            {
                            //Nuevo Titulo
                            case 1:
                                cout << "Ingrese el nuevo titulo: " << endl << "> ";
                                getline(cin, nTitulo);
                                biblioteca[i].setTitulo(nTitulo);
                                break;
                            //Nuevo autor
                            case 2:
                                cout << "Ingrese el nuevo autor: " << endl << "> ";
                                getline(cin, nAutor);
                                biblioteca[i].setAutor(nAutor);
                                break;
                            //Nueva editorial
                            case 3:
                                cout << "Ingrese la nueva Editorial: " << endl << "> ";
                                getline(cin, nEditorial);
                                biblioteca[i].setEditorial(nEditorial);
                                break;
                            //Nuevo Anio de publicacion
                            case 4:
                                cout << "Ingrese el nuevo anio de publicacion: " << endl << "> ";
                                cin >> nAnioDePublicacion;
                                biblioteca[i].setAnioDePublicacion(nAnioDePublicacion);
                                break;
                            //Nuevo genero
                            case 5:
                                cout << "Ingrese el nuevo genero: " << endl << "> ";
                                getline(cin, nGenero);
                                biblioteca[i].setGenero(nGenero);
                                break;
                            //Nuevo idioma
                            case 6:
                                cout << "Ingrese el nuevo idioma: " << endl << "> ";
                                getline(cin, nIdioma);
                                biblioteca[i].setIdioma(nIdioma);
                                break;
                            //Nuevo ID
                            case 7:
                                cout << "Ingrese el nuevo Id: " << endl << "> ";
                                cin >> nId;
                                biblioteca[i].setId(nId);
                                break;
                            //Nuevo numero de paginas
                            case 8:
                                cout << "Ingrese el nuevo numero de paginas: " << endl << "> ";
                                cin >> nNumeroPaginas;
                                biblioteca[i].setNumeroPaginas(nNumeroPaginas);
                                break;
                            //Nueva cantidad de stock
                            case 9:
                                cout << "Ingrese el nuevo numero de Stock: " << endl << "> ";
                                cin >> nStock;
                                biblioteca[i].setStock(nStock);
                                break;
                            //En caso de una opcion invalida
                            default:
                                cout << "Opcion invalida, saliendo del menu." << endl;
                                break;
                            
                            controlador_aux=1;
                            rewrite_txt(biblioteca, "libros.txt");
                            }
                        }
                    }
                }
                else
                {
                    cout << "No hay libros que puedan ser editados..." << endl;
                }
                    
            }
            else
            {
                cout << "No hay elementos en la biblioteca..." << endl;   
            }
            pulsaEnter();
        }

        //MODIFICAR USUARIOS
        else if(controlador == 12)
        {
            //Verifica que la lista de usuarios tenga al menos un elemento.
            if(!usuarios.empty())
            {
                controlador_aux=0;
                //Bucle que recorrerara toda la lista de usuarios e imprimira los usuarios que no tengan libros en su poder.
                for(int i=0; i < usuarios.size(); i++)
                {
                    //Si es que el usuario no tiene libros en su poder
                    if(usuarios[i].getLibroSolicitadoEmpty())
                    {
                        
                        //Muestra
                        cout << i+1 << ") " << usuarios[i].getNombre() << endl;
                        //Si hay usuarios que no tengan libros en su poder controlador aux va a ser 1, si no hay sera 0.
                        controlador_aux=1;
                    }
                }
                if(controlador_aux=1)
                {
                    cout << "Ingrese el usuario que desea editar (ingrese su nombre): " << endl << "> ";
                    cin.get();
                    getline(cin, nombreGenericoParaBuscar);
                    for (int i = 0; i < usuarios.size(); i++)
                    {
                        if(usuarios[i].getNombre() == nombreGenericoParaBuscar && usuarios[i].getLibroSolicitadoEmpty())
                        {
                            //Inicializa el menu para consultar al usuario que desa cambiar:
                            limpiarPantalla();
                            cout << "Usuario encontrado!" << endl << "-------------------------" << endl << "1) Editar nombre" << endl << "2) Editar rut" << endl << "> ";
                            cin >> controlador_aux;
                            switch (controlador_aux)
                            {
                            case 1:
                                cout << "Ingrese el nuevo nombre de usuario: " << endl << "> ";
                                cin.get();
                                getline(cin, nNombreUsuario);
                                usuarios[i].setNombre(nNombreUsuario);
                                break;
                            
                            case 2:
                                cout << "Ingrese el nuevo rut del usuario: " << endl << "> ";
                                cin.get();
                                getline(cin, nRutUsuario);
                                usuarios[i].setRut(nRutUsuario);
                                break;

                            default:
                                cout << "Opcion invalida, saliendo del menu..." << endl;
                                break;
                            controlador_aux=1;
                            rewrite_users(usuarios, "usuarios.txt");
                            }
                        }
                    }
                    

                }
                else
                {
                    cout << "No hay usuarios que puedan ser editados..." << endl;
                }

            }
            else
            {
                cout << "No hay usuarios registrados..." << endl;
            }
            pulsaEnter();
        }
        
        //MOSTRAR REGISTRO DE AUDITORIA
        else if(controlador == 13)
        {
            if(!historial.empty())
            {
                for (int i = 0; i < historial.size(); i++)
                {
                    cout << historial[i] << endl;
                }
            }
            else cout << "No hay registros..." << endl;
            pulsaEnter();
        }

        //GUARDAR Y SALIR DEL PROGRAMA
        else if(controlador == 14)
        {
            rewrite_txt(biblioteca, "libros.txt");
            rewrite_users(usuarios, "usuarios.txt");
            contr_while = false;
        }
    
    }
    
    return(0);
}
