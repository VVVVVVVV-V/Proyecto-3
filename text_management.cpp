#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include "Libro.h"
#include "Usuario.h"
#include "text_management.h"

// Se define un "pass" que no hace nada, lo necesitamos para las estructuras de tipo
// (condicion) ? (si es verdadero) : (si es falso) y como no necesitamos hacer nada
// en alguno de los dos casos, se utiliza para que no se haga nada.
#define pass (void)0

using namespace std;

// Se define una función que recibe un vector de libros y lo llena con los datos
void read_txt(vector<Libro>& biblioteca, string filename)
{
    // Abre el archivo de texto
    ifstream file(filename);
    // Se define un string para guardar las lineas del archivo
    string line;
    // Se verifica si el archivo se abrió correctamente
    if (file.is_open()) {

        // Basicamente, leer cada linea del archivo, si se lee corectamente
        // o no ha terminado de leer el archivo, devuelve un true y sigue
        // leyendo, si no, devuelve un false y termina el ciclo
        while (getline(file, line)) {
            // Se crea un objeto stringstream para leer los datos de la linea
            stringstream ss(line);
            // Definimos strings para guardar los datos de las lineas
            string titulo, autor, editorial, anio_str, genero, idioma, id_str, paginas_str, stock_str, disponibilidad_str, libros_prestados_str;
            // Definimos un entero para guardar el número de páginas
            int paginas, anio, id, stock, libros_prestados;

            bool disponibilidad;

            /* Basicamente, leemos los datos del tipo de dato stringstream
               hasta alcanzar una coma, ahi, lo leido se almacena en 
               "titulo"*/
            getline(ss, titulo, ',');

            // Se sigue leyendo desde donde se quedó la última vez descartando la ","
            // y se almacena en "autor"
            getline(ss, autor, ',');

            // Se sigue leyendo desde donde se quedó la última vez descartando la ","
            // y se almacena en "editorial"
            getline(ss, editorial, ',');

            // Se sigue leyendo desde donde se quedó la última vez descartando la ","
            // y se almacena en "anio_str"
            getline(ss, anio_str, ',');

            // Se convierte el string de anio a un entero y se almacena en "anio"
            anio = stoi(anio_str);

            // Se sigue leyendo desde donde se quedó la última vez descartando la ","
            // y se almacena en "genero"
            getline(ss, genero, ',');

            // Se sigue leyendo desde donde se quedó la última vez descartando la ","
            // y se almacena en "idioma"
            getline(ss, idioma, ',');

            // Se sigue leyendo desde donde se quedó la última vez descartando la ","
            // y se almacena en "id_str"
            getline(ss, id_str, ',');

            // Se convierte el string de id a un entero y se almacena en "id"
            id = stoi(id_str);

            // Se sigue leyendo desde donde se quedó la última vez descartando la ","
            // y se almacena en "paginas_str"
            getline(ss, paginas_str, ',');

            // Se convierte el string de paginas a un entero y se almacena en "paginas"
            paginas = stoi(paginas_str);

            // Se sigue leyendo desde donde se quedó la última vez descartando la ","
            // y se almacena en "stock_str"
            getline(ss, stock_str, ',');

            // Se convierte el string de stock a un entero y se almacena en "stock"
            stock = stoi(stock_str);

            // Se sigue leyendo desde donde se quedó la última vez descartando la ","
            // y se almacena en "disponibilidad_str"
            getline(ss, disponibilidad_str, ',');

            if (disponibilidad_str == "1") {
                disponibilidad = true;
            } else {
                disponibilidad = false;
            }

            getline(ss, libros_prestados_str, ',');
            libros_prestados = stoi(libros_prestados_str);

            // Crear un objeto Libro y lo agrega al vector
            biblioteca.push_back(Libro(titulo, autor, editorial, anio, genero, idioma, id, paginas, stock, disponibilidad, libros_prestados));
        }
        file.close();
    } 
    else 
    {
        cout << "No se puede abrir el archivo!" << endl;
    }
}

void rewrite_txt(std::vector<Libro>& biblioteca, std::string filename)
{
    // Abre un archivo de salida dado en filename
    ofstream file(filename);
    int i;
    string line = "";
    int length = biblioteca.size();

    // Recorre todos los libros en la biblioteca
    for (i = 0; i < length; i++)
    {
        // Construye una línea con el título, autor, editorial, año de publicación, género, idioma, id, número de páginas, stock y disponibilidad de cada libro
        line = line + biblioteca[i].getTitulo() + "," + biblioteca[i].getAutor() + "," + biblioteca[i].getEditorial() + "," + to_string(biblioteca[i].getAnioDePublicacion()) + "," + biblioteca[i].getGenero() + "," + biblioteca[i].getIdioma() + "," + to_string(biblioteca[i].getId()) + "," + to_string(biblioteca[i].getNumeroPaginas()) + "," + to_string(biblioteca[i].getStock()) + "," + to_string(biblioteca[i].getDisponibilidad()) + "," + to_string(biblioteca[i].getLibrosPrestados()) + "\n";
    }

    // Verifica si el archivo se abrió correctamente
    if (file.is_open())
    {
        // Escribe la línea construida en el archivo y lo cierra
        file << line;
        file.close();
    }
    else
    {
        // Muestra un mensaje de error si no se puede abrir el archivo
        cout << "No se puede abrir el archivo!" << endl;
    }
}

void read_users(vector<Usuario>& lista, string filename)
{
    // Abre el archivo de texto
    ifstream file(filename);
    // Se define un string para guardar las lineas del archivo
    string line;
    // Se verifica si el archivo se abrió correctamente
    if (file.is_open()) {

        // Basicamente, leer cada linea del archivo, si se lee corectamente
        // o no ha terminado de leer el archivo, devuelve un true y sigue
        // leyendo, si no, devuelve un false y termina el ciclo
        while (getline(file, line)) {
            // Se crea un objeto stringstream para leer los datos de la linea
            stringstream ss(line);

            // Definimos un auxiliar para ir guardando los libros solicitados
            // y posteriormente añadirlos a un vector
            string aux;
            // Definimos strings para guardar los datos de las lineas
            string nombre, rut;
            // Definimos un entero para guardar el número de páginas
            vector<string> libros_solicitados;

            /* Basicamente, leemos los datos del tipo de dato stringstream
               hasta alcanzar una coma, ahi, lo leido se almacena en 
               "nombre"*/
            getline(ss, nombre, ',');

            // Se sigue leyendo desde donde se quedó la última vez descartando la ","
            // y se almacena en "rut"
            getline(ss, rut, ',');

            // Se sigue leyendo desde donde se quedó la última vez descartando la ","
            // el bucle revisa el resto de la línea y separa los libros solicitados
            // en aux y los agrega al vector libros_solicitados separando por "]"
            while (getline(ss, aux, ']')) {
                libros_solicitados.push_back(aux);
            }
            
            // Crear un objeto Libro y lo agrega al vector
            lista.push_back(Usuario(nombre, rut, libros_solicitados));
        }
        file.close();
    } 
    else 
    {
        cout << "No se puede abrir el archivo!" << endl;
    }
}

void rewrite_users(vector<Usuario>& lista, string filename)
{
    // Abre un archivo de salida dado en filename
    ofstream file(filename);

    // Se define unas variable para iterar en el bucle
    int i, j;

    // Definimos un string para ir guardando las lineas que se iran escribiendo en el .txt
    string line = "";
    
    // Definimos una variable para guardar la cantidad de objetos de tipo Usuario en el vector
    int length = lista.size();

    // Recorre todos los usuarios en la lista
    for (i = 0; i < length; i++)
    {
        int vector_libros_length = lista[i].getLibroSolicitadoSize();
        // Construye una línea con el nombre y rut del usuario
        line = line + lista[i].getNombre() + "," + lista[i].getRut() + ",";

        // Recorremos el vector de los libros que ha solicitado el usuario y los vamos concatenando
        // a la linea que se escribira en el .txt
        for (j = 0; j < vector_libros_length; j++) {
            line = line + lista[i].getLibroSolicitadoPorIndex(j) + "]";
        }
        
        // Terminamos la linea con un salto de linea para que pase a la siguiente línea
        line = line + "\n";
    }

    // Verifica si el archivo se abrió correctamente
    if (file.is_open())
    {
        // Escribe la línea construida en el archivo y lo cierra
        file << line;
        file.close();
    }
    else
    {
        // Muestra un mensaje de error si no se puede abrir el archivo
        cout << "No se puede abrir el archivo!" << endl;
    }
}

string get_current_date()
{
    //Crea una estructura de "Datetime"
    struct tm date;
    
    //Crea una "timestamp" con la fecha y hora actual
    time_t current_time = time(0);

    // Se define un datetime transformando la "timestamp" con la funcion localtime
    tm *current_date = localtime(&current_time);

    // Como una estructura datetime contiene varios atributos como "tm_sec" o "tm_min"
    // podemos acceder a ellos para obtener la fecha actual, accediendo al puntero
    // con el operador "->"
    // Transformamos estos valores a un string y concatenamos para obtener el formato "dd-mm-yyyy"
    // tm_mday contiene el dia actual, tm_mon contiene el mes actual del 0 al 11, por lo que
    // para mostrar el mes 12 hay que sumar 1, tm_year contiene el año actual desde 1900 por lo que 
    // devolveria "124" y por ende hay que sumarle 1900
    string date_str = to_string(current_date->tm_mday) + "-" + to_string(current_date->tm_mon + 1) + "-" + to_string(current_date->tm_year + 1900);

    return date_str;
}

string get_current_hour()
{
 //Crea una estructura de "Datetime"
    struct tm date;
    
    //Crea una "timestamp" con la fecha y hora actual
    time_t current_time = time(0);

    // Se define un datetime transformando la "timestamp" con la funcion localtime
    tm *current_date = localtime(&current_time);

    // Como una estructura datetime contiene varios atributos como "tm_sec" o "tm_min"
    // podemos acceder a ellos para obtener la fecha actual, accediendo al puntero
    // con el operador "->"
    // Transformamos estos valores a un string y concatenamos para obtener el formato "hh:mm:ss"
    // tm_hour contiene la hora actual, tm_min contiene los minutos actuales y tm_sec contiene
    // los segundos actuales
    string date_str = to_string(current_date->tm_hour) + ":" + to_string(current_date->tm_min) + ":" + to_string(current_date->tm_sec);
    return date_str;
}

void check_register()
{
    // Obtenemos la fecha actual y la guardamos en un string, este sera el nombre del archivo
    string date_str = get_current_date() + ".txt";

    // Se crea una variable para poder abrir en lectura un archivo
    ifstream file;

    // Se crea una variable para poder abrir en escritura un archivo
    ofstream created_file;

    // Se abre el archivo con el nombre de la fecha de hoy
    file.open(date_str);

    // Verifica que el archivo no exista, en cuyo caso se crea un archivo con el nombre de la fecha de hoy
    (file) ? pass : created_file.open(date_str), created_file.close();

    // Se cierra el archivo que se abrió en lectura
    file.close();
}

// Una función que recibe un vector que contiene strings y un objeto de tipo Libro
void register_new_book(vector<string>& registro, Libro& libro)
{
    // Se obtiene el titulo del libro
    string new_book = libro.getTitulo();
    string new_book_id = to_string(libro.getId());

    // Se define un string para guardar la linea que se añadira al registro
    string line;
    
    // Definimos el contenido del registro y le añadimos la hora utilizando la funcion
    // get_current_hour() que devuelve la hora actual en string
    line = "Se ha registrado el libro \"" + new_book+"\" con ID " + new_book_id + " a las " + get_current_hour() + " con fecha " + get_current_date();

    // Se añade la linea al vector de strings
    registro.push_back(line);



}

void register_new_user(vector<string>& registro, Usuario& user)
{
    // Se obtiene el nombre del usuario
    string new_user = user.getNombre();
    string new_user_rut = user.getRut();
    string date = get_current_date();
    string hour = get_current_hour();

    // Se define un string para guardar la linea que se añadira al registro
    string line;
    
    // Definimos el contenido del registro y le añadimos la hora utilizando la funcion
    // get_current_hour() que devuelve la hora actual en string
    line = "Se ha registrado el usuario \"" + new_user+"\" con RUT " + new_user_rut + " a las " + hour + " con fecha " + date;

    // Se añade la linea al vector de strings
    registro.push_back(line);
}