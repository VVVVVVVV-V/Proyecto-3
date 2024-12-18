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
            if(nombreVector[i].getStock() > 0) cout << i+1 << ") " << nombreVector[i].getTitulo() << endl;
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
                cout << i+1 << ") " << nombreVector[i].getNombre() << endl;
                aux=true;
            }
            
        }
    }
    else if(aux == false) cout << "No hay elementos que mostrar..." << endl;
}

bool depurarEspacios(string texto)
{
    //Elimina los espacios de una cadena de texto, si esta vacia devuelve un false, si aun asi tiene texto devuelve true.
    string auxiliar = texto;
    if(!texto.empty())
    {
        //Remove mueve todos los espacios hasta el final de la cadena, dejando la "basura" por asi decirlo al final, luego retorna la posicion en la que aun hay texto "no basura", para que despues todo ese texto basura sea eliminado por la funcion erase.
        //El espacio debe ser tratado con ' ' en vez de " " ya que en este caso se busca un caracter definido por ' ', no una cadena de texto definida por " "
        texto.erase(remove(texto.begin(), texto.end(), ' '), texto.end());
        
        if(texto.empty())
        {
            texto=auxiliar;
            return(false);
        }
        
        else
        {
            texto=auxiliar;
            return(true);
        }
    }
    else return(false);
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
        //Controla si es que en el controlador ingresan texto
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            controlador = 0;
        } 
        limpiarPantalla();
        //Usar un switch tiraba errores al instanciar un objeto, asi que toco usar puro if
        
        //AGREGAR LIBROS.
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
            //Si es que algun valor no es valido se le avisara al usuario, de otra forma podrian haber errores en la generacion de los libros.
            if(!depurarEspacios(nTitulo) || !depurarEspacios(nAutor) || !depurarEspacios(nEditorial) || !depurarEspacios(nGenero) || !depurarEspacios(nIdioma) || nId < 0 || nNumeroPaginas < 0 || nStock < 0 || nAnioDePublicacion < 0)
            {
                cout << "Algun valor ingresado es invalido, vuelva a intentarlo." << endl;
            } 
            //instanciacion del libro y añadir a la lista.
            else
            {
                if(nStock == 0) {
                    Libro libro(nTitulo, nAutor, nEditorial, nAnioDePublicacion, nGenero, nIdioma, nId, nNumeroPaginas, nStock, false, 0, {});
                    biblioteca.push_back(libro);
                } 
                else 
                {
                    Libro libro(nTitulo, nAutor, nEditorial, nAnioDePublicacion, nGenero, nIdioma, nId, nNumeroPaginas, nStock, true, 0, {});
                    biblioteca.push_back(libro);
                }
                register_new_book(historial, biblioteca.back());
                rewrite_txt(biblioteca, "libros.txt");
            }
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
            //Si es que algun valor ingresado por el usuario no es valido se le avisara al usuario, de otra forma podria ingresar strings vacios.
            if(!depurarEspacios(nNombreUsuario) || !depurarEspacios(nRutUsuario))
            {
                cout << "Algun valor ingresado no es valido, vuelva a intentarlo." << endl;
            }
            //Intanciacion del usuario y añadir a la lista.
            else
            {
                Usuario nuevousuario(nNombreUsuario, nRutUsuario, {});
                usuarios.push_back(nuevousuario);
                register_new_user(historial, usuarios.back());
                rewrite_users(usuarios, "usuarios.txt");
            }
            
            pulsaEnter();

        }

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
                        cout << "Libro disponible!" << endl << "----------------------------" << endl << "Desea pedir el libro de manera virtual o fisica?" << endl << "1) Fisica" << endl << "2) Digital" << endl << "> ";
                        cin >> controlador_aux;
                        //Si es que se quiere pedir prestado un libro fisico
                        if(controlador_aux == 1)
                        {
                            limpiarPantalla();
                            //Muestra opciones con los respectivos usuarios en pantalla.
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
                                            break;
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
                                    register_lend_book(historial, biblioteca[i], usuarios[controlador_aux-1].getNombre());
                                    cout << "Prestamo realizado con exito!" << endl;
                                    // Guardar en los archivos de texto
                                    rewrite_txt(biblioteca, "libros.txt");
                                    rewrite_users(usuarios, "usuarios.txt");
                                    
                                }
                            }
                            //Si el valor ingresado el el controlador_aux no es valido como index entonces el prestamo pasa a ser falso.
                            else controlador_prestamo=false;
                        }
                        //Si es que el libro es virtual
                        else if(controlador_aux==2)
                        {
                            limpiarPantalla();
                            mostrarUsuarios(usuarios);
                            //Pregunta quien quiere pedir prestado el libro
                            cout << endl << "Que usuario desea pedir prestado este libro?" << endl << "> ";
                            cin >> controlador_aux;
                            
                            if(controlador_aux <= usuarios.size() && controlador_aux > 0)
                            {
                                //Si el libro no ha sido prestado a nadie automaticamente o el usuario no tiene ningun libro sera verdadero el prestamo
                                if(biblioteca[i].nombrePrestadoEmpty() || usuarios[controlador_aux-1].getLibroSolicitadoEmpty())
                                {
                                    controlador_prestamo=true;
                                }
                                
                                //Si tiene por lo menos un libro pedido
                                else
                                {
                                    //Recorre la lista de los libros que ha pedido el usuario.
                                    for(int j=0 ; j < usuarios[controlador_aux-1].getLibroSolicitadoSize(); j++)
                                    {
                                        //Si el usuario tiene registrado en sus prestamos el nombre del libro (virtual) tipo "Cartas en el Asunto (Virtual)" entonces se le pasara por pantalla que no puede alquilarlo y se terminara el for.
                                        if(usuarios[controlador_aux-1].getLibroSolicitadoPorIndex(j) == biblioteca[i].getTitulo()+" (Virtual)")
                                        {
                                            cout << "Este usuario no puede pedir este libro porque ya tiene una copia de este en su poder." << endl;
                                            controlador_prestamo=false;
                                            break;
                                        }
                                        //Si el usuario no tiene una copia de ese libro en su poder el controlador del prestamo se volvera true y se pasara a prestarlo.
                                        else controlador_prestamo=true;
                                    }
                                    
                                }
                                if(controlador_prestamo)
                                {
                                    biblioteca[i].prestarLibro(usuarios[controlador_aux-1].getNombre()+" (Virtual)");
                                    usuarios[controlador_aux-1].añadirLibros(biblioteca[i].getTitulo()+" (Virtual)");
                                    register_virtual_lend_book(historial, biblioteca[i], usuarios[controlador_aux-1].getNombre());
                                    cout << "Prestamo realizado con exito!" << endl;
                                    rewrite_txt(biblioteca, "libros.txt");
                                    rewrite_users(usuarios, "usuarios.txt");
                                    
                                }
                            }
                            else controlador_prestamo=false;

                        }
                        //Si no es una opcion valida
                        else
                        {
                            cout << "Opcion invalida." << endl;
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

        //Ya habiendo terminado el programa, puede ser que esta funcion haya sido mas facil de implementar si es que en vez de buscar un usuario y seleccionarlo de una lista (que en caso de haber registrado muchos usuarios seria realmente incomodo y tedioso de usar) podria haber hecho que se buscara por nombre o rut, y en ese caso tambien podria optimizar ese proceso volviendo eso una funcion ya que lo podria usar aqui y en buscar los detalles, siento que hay mucho que podria haber sido mejor optimizado, pero asi es como quedo y creo que funciona y estoy feliz por eso. 
        
        /* --GNU Terry Pratchett */

        //DEVOLVER LIBROS
        else if(controlador == 4)
        {
            bool controlador_prestamo_virtual=false;
            controlador_prestamo=false;
            controlador_aux=0;
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
                                }
                                //Si es que el titulo en la biblioteca lleva un "(Virtual)" en la lista de libros solicitados por el usuario.
                                else if(biblioteca[j].getTitulo()+" (Virtual)" == usuarios[i].getLibroSolicitadoPorIndex(controlador_aux-1))
                                {
                                    controlador_prestamo=true;
                                    controlador_prestamo_virtual=true;
                                    controlador_aux_prestamo=j;
                                }
                            }
                        }
                    }
                    //Si el controlador de prestamo es verdadero va a devolver el libro usando el nombre del usuario que lo devuelve como parametro, y el usuario va a eliminar el libro usando el titulo del libro como parametro
                    if(controlador_prestamo && !controlador_prestamo_virtual)
                    {
                        biblioteca[controlador_aux_prestamo].devolverLibro(usuarios[i].getNombre());
                        usuarios[i].eliminarLibros(biblioteca[controlador_aux_prestamo].getTitulo());
                        //Registra en el historial que el libro ha sido devuelto y reescribe los archivos de texto.
                        register_return_book(historial, biblioteca[controlador_aux_prestamo], usuarios[i].getNombre());
                        rewrite_txt(biblioteca, "libros.txt");
                        rewrite_users(usuarios, "usuarios.txt");
                        pulsaEnter();
                        break;
                    }
                    else if(controlador_prestamo && controlador_prestamo_virtual)
                    {
                        biblioteca[controlador_aux_prestamo].devolverLibro(usuarios[i].getNombre()+" (Virtual)");
                        usuarios[i].eliminarLibros(biblioteca[controlador_aux_prestamo].getTitulo()+" (Virtual)");
                        //Registra en el historial que el libro ha sido devuelto y reescribe los archivos de texto.
                        register_virtual_return_book(historial, biblioteca[controlador_aux_prestamo], usuarios[i].getNombre());
                        rewrite_txt(biblioteca, "libros.txt");
                        rewrite_users(usuarios, "usuarios.txt");
                        pulsaEnter();
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



        //MOSTRAR LIBROS EN LA BIBLIOTECA
        else if(controlador == 5)
        {
            mostrarBiblioteca(biblioteca);
            pulsaEnter();
        }
        

        //MOSTRAR LOS USUARIOS REGISTRADOS
        else if(controlador == 6)
        {
            mostrarUsuarios(usuarios);
            pulsaEnter();
        }


        //VERIFICAR DETALLES DE UN LIBRO EN LA LISTA
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
                    limpiarPantalla();
                    biblioteca[controlador_aux-1].mostrarInformacion();
                    controlador_aux=0;
                }
                else cout << "Opcion invalida..." << endl;
            }
            else cout << "No hay libros en la biblioteca." << endl;
            pulsaEnter();
        }


        //VERIFICAR DETALLES DE UN USUARIO DE LA LISTA
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
                    limpiarPantalla();
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


        //BUSCAR UN LIBRO ESPECIFICO POR NOMBRE
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

        //BUSCAR DETALLES DE UN USUARIO POR NOMBRE O RUT
        else if(controlador == 10)
        {
            //Si es que la lista de usuarios tiene algun elemento
            if(!usuarios.empty())
            {
                cout << "Seleccione una de las opciones:" << endl << "1) Buscar por nombre." << endl << "2) Buscar por rut." << endl << "> ";
                cin >> controlador_aux;
                //Si se elige buscar por nombre se le pedira al usuario que ingrese el nombre que desea buscar y se inicializara un bucle, dentro de este bucle se revisara cada nombre de cada elemento en la lista usuario, si alguno coincide con este mostrara su informacion.
                if(controlador_aux == 1)
                {
                    limpiarPantalla();
                    cout << "Ingrese el nombre del usuario que desea buscar: " << endl << " > ";
                    cin.get();
                    getline(cin, nombreGenericoParaBuscar);
                    //Se define un controlador auxiliar a 0, puesto que si no se encuentran coincidencias lo mostara en pantalla.
                    controlador_aux=0;
                    limpiarPantalla();
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
                //Si el usuario elige buscar por rut se hara exactamente lo mismo, sin embargo se mostrara un mensaje diferente.
                else if(controlador_aux == 2)
                {
                    limpiarPantalla();
                    cout << "Ingrese el rut del usuario que desea buscar: " << endl << "> ";
                    cin.get();
                    getline(cin, nombreGenericoParaBuscar);
                    controlador_aux=0;
                    limpiarPantalla();
                    for(int i=0; i < usuarios.size(); i++)
                    {
                        if(usuarios[i].getRut() == nombreGenericoParaBuscar)
                        {
                            //Muestra la informacion y cambia el controlador a 1.
                            usuarios[i].mostrarInformacion();
                            controlador_aux=1;
                        }
                    }
                    if(controlador_aux != 1)
                    {
                        cout << "No se han encontrado coincidencias..." << endl;
                    }
                }
                else cout << "Seleccione una opcion valida." << endl;
                
            }
            //Si la lista no tiene elementos muestra en pantalla que no hay usuarios registrados.
            else cout << "No hay usuarios registrados." << endl;
            pulsaEnter();
        }

        //EDITAR LIBROS
        else if(controlador == 11)
        {
            //Si es que la biblioteca no esta vacia se recorrera esta lista y se mostara una lista de todos los libros que no han sido prestados a nadie, puesto que si el libro esta prestado no va a ser posible imprimirlo.
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
                //Si hay libros que no han sido prestados se entrara al menu, este menu pedira al usuario que ingrese el nombre del libro que desea editar, seguido de esto si es que el nombre coincide con algun nombre de algun libro registrado se accedera a un menu para editar cualquier atributo de forma individual de los libros.
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
                                if(!nTitulo.empty() && depurarEspacios(nTitulo))
                                {
                                    register_edit_book_title(historial, biblioteca[i], nTitulo);
                                    biblioteca[i].setTitulo(nTitulo);
                                }
                                break;
                            //Nuevo autor
                            case 2:
                                cout << "Ingrese el nuevo autor: " << endl << "> ";
                                getline(cin, nAutor);
                                if(!nAutor.empty() && depurarEspacios(nAutor))
                                {
                                    register_edit_book_author(historial, biblioteca[i], nAutor);
                                    biblioteca[i].setAutor(nAutor);
                                }
                                break;
                            //Nueva editorial
                            case 3:
                                cout << "Ingrese la nueva Editorial: " << endl << "> ";
                                getline(cin, nEditorial);
                                if(!nEditorial.empty() && depurarEspacios(nEditorial))
                                {
                                    register_edit_book_publisher(historial, biblioteca[i], nEditorial);
                                    biblioteca[i].setEditorial(nEditorial);
                                }
                                break;
                            //Nuevo Anio de publicacion
                            case 4:
                                cout << "Ingrese el nuevo anio de publicacion: " << endl << "> ";
                                cin >> nAnioDePublicacion;
                                if(nAnioDePublicacion >= 0)
                                {
                                    register_edit_book_release_year(historial, biblioteca[i], to_string(nAnioDePublicacion));
                                    biblioteca[i].setAnioDePublicacion(nAnioDePublicacion);
                                }
                                break;
                            //Nuevo genero
                            case 5:
                                cout << "Ingrese el nuevo genero: " << endl << "> ";
                                getline(cin, nGenero);
                                if(!nGenero.empty() && depurarEspacios(nGenero))
                                {
                                    register_edit_book_genre(historial, biblioteca[i], nGenero);
                                    biblioteca[i].setGenero(nGenero);
                                }
                                break;
                            //Nuevo idioma
                            case 6:
                                cout << "Ingrese el nuevo idioma: " << endl << "> ";
                                getline(cin, nIdioma);
                                if(!nIdioma.empty() && depurarEspacios(nIdioma))
                                {
                                    register_edit_book_language(historial, biblioteca[i], nIdioma);
                                    biblioteca[i].setIdioma(nIdioma);
                                }
                                break;
                            //Nuevo ID
                            case 7:
                                cout << "Ingrese el nuevo Id: " << endl << "> ";
                                cin >> nId;
                                if(nId >= 0)
                                {
                                    register_edit_book_id(historial, biblioteca[i], to_string(nId));
                                    biblioteca[i].setId(nId);
                                }
                                break;
                            //Nuevo numero de paginas
                            case 8:
                                cout << "Ingrese el nuevo numero de paginas: " << endl << "> ";
                                cin >> nNumeroPaginas;
                                if(nNumeroPaginas > 0)
                                {
                                    register_edit_book_pages_number(historial, biblioteca[i], to_string(nNumeroPaginas));
                                    biblioteca[i].setNumeroPaginas(nNumeroPaginas);
                                }
                                break;
                            //Nueva cantidad de stock
                            case 9:
                                cout << "Ingrese el nuevo numero de Stock: " << endl << "> ";
                                cin >> nStock;
                                if(nStock > 0)
                                {
                                    register_edit_book_stock(historial, biblioteca[i], to_string(nStock));
                                    biblioteca[i].setStock(nStock);
                                }
                                break;
                            //En caso de una opcion invalida
                            default:
                                cout << "Opcion invalida, saliendo del menu." << endl;
                                break;
                            
                            }
                            //Controlador auxiliar = 1 sin motivo aparente.
                            controlador_aux=1;
                            rewrite_txt(biblioteca, "libros.txt");
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
                //Si hay usuarios registrados hara exactamente lo mismo que editar libros.
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
                            limpiarPantalla();
                            switch (controlador_aux)
                            {
                            case 1:
                                cout << "Ingrese el nuevo nombre de usuario: " << endl << "> ";
                                cin.get();
                                getline(cin, nNombreUsuario);
                                if(!nNombreUsuario.empty() && depurarEspacios(nNombreUsuario))
                                {
                                    register_edit_user_name(historial, usuarios[i], nNombreUsuario);
                                    usuarios[i].setNombre(nNombreUsuario);
                                }
                                break;
                            
                            case 2:
                                cout << "Ingrese el nuevo rut del usuario: " << endl << "> ";
                                cin.get();
                                getline(cin, nRutUsuario);
                                if(!nRutUsuario.empty() && depurarEspacios(nRutUsuario))
                                {
                                    register_edit_user_rut(historial, usuarios[i], nRutUsuario);
                                    usuarios[i].setRut(nRutUsuario);
                                }
                                break;

                            default:
                                cout << "Opcion invalida, saliendo del menu..." << endl;
                                break;
                            
                            }
                            //Controlador auxiliar = 1 sin motivo aparente.
                            controlador_aux=1;
                            rewrite_users(usuarios, "usuarios.txt");
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
                //Muestra la lista del registro de auditoria si es que la lista no esta vacia.
                for (int i = 0; i < historial.size(); i++)
                {
                    cout << historial[i] << endl;
                }
            }
            //Si la lista esta vacia dice que no hay registros.
            //Si, eso es todo, ¿Que pensabas que era muy complicado? Anda a revisar el text_management.cpp si quieres ver algo complicado.
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
