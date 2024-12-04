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
void register_new_book(std::vector<std::string>& registro, Libro& libro);
void register_new_user(std::vector<std::string>& registro, Usuario& user);


#endif