#if !defined(_BOOK_MANAGE_H_)
#define _BOOK_MANAGE_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include "Libro.h"
#include "Usuario.h"

void read_txt(std::vector<Libro>& biblioteca, std::string filename);
void rewrite_txt(std::vector<Libro>& biblioteca, std::string filename);
void read_users(std::vector<Usuario>& lista, std::string filename);
void rewrite_users(std::vector<Usuario>& lista, std::string filename);


std::string get_current_date();
std::string get_current_hour();
void check_register();

/*
- Registro de auditoria:
    - Añadir libro
    - Añadir usuario
    - Editar libro:
        - Cambiar titulo
        - Cambiar autor
        - Cambiar genero
        - Cambiar idioma
        - Cambiar id
        - cambiar numero de paginas
        - Cambiar editorial
        - Cambiar año de publicacion
        - Cambiar cantidad de stock
    - Editar usuario:
        - Cambiar nombre
        - Cambiar Rut
    - Prestar libro
    - Devolver libro
*/
void register_new_book(std::vector<std::string>& registro, Libro& libro);
void register_edit_book_title(std::vector<std::string>& registro, Libro& libro);
void register_edit_book_author(std::vector<std::string>& registro, Libro& libro);
void register_edit_book_genre(std::vector<std::string>& registro, Libro& libro);
void register_edit_book_language(std::vector<std::string>& registro, Libro& libro);
void register_edit_book_id(std::vector<std::string>& registro, Libro& libro);
void register_edit_book_pages_number(std::vector<std::string>& registro, Libro& libro);
void register_edit_book_publisher(std::vector<std::string>& registro, Libro& libro);
void register_edit_book_release_year(std::vector<std::string>& registro, Libro& libro);
void register_edit_stock(std::vector<std::string>& registro, Libro& libro);


void register_new_user(std::vector<std::string>& registro, Usuario& user);
void register_edit_user_name(std::vector<std::string>& registro, Usuario& user);
void register_edit_user_rut(std::vector<std::string>& registro, Usuario& user);


void register_lend_book(std::vector<std::string>& registro, Libro& libro);
void register_return_book(std::vector<std::string>& registro, Libro& libro);



#endif