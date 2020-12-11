/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   csv.h
 * Author: dalva
 *
 * Created on December 11, 2020, 1:15 PM
 */

#ifndef CSV_H
#define CSV_H

#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class csv {
public:
    
    //constructor vacio
    csv();
    //constructor de copia
    csv(const csv& orig);
    //constructor con filename
    csv(string);
    //constructor con filename y bool de encabezados
    csv(string, bool);
    //destructor
    virtual ~csv();
    
    
    //setters y getters
    
    //retorna el nombre del archivo
    string getFileName();
    //setea el nombre del archivo a usar
    void setFileName();
    //regresa los encabezados encontrados del archivo
    vector<string> getEncabezados();
    //retorna todos los datos del archivo
    vector<vector<string>> getData();
    //regresa el numero de registros del archivo
    int getData_Count();
    
    //funciones
    
    //hace un sort del data ascendentemente o descendentemente dependiendo del bool
    vector<vector<string>> sort_data(int, bool);
    
    //retorna los datos de una columna
    vector<string> get_column(int);
    
    //retorna los datos de una fila
    vector<string> get_row(int);
    
    //retorna el valor maximo de una columna
    vector<string> get_max(int);
    
    //retorna el valor minimo de una columna
    vector<string> get_min(int);
    
    //imprime los datos del archivo
    void print_data();
    
    //elimina la fila indicada
    void truncate_row(int);
    
    //elimina la columna indicada
    void truncate_column(int);
    
    //concatena dos archivos
    csv* concat(csv*, string);
    
    //escribe los datos a un archivo txt
    void write_file();
    
    //carga el archivo y guarda sus encabezados de ser bool igual a true
    void load_file(bool);
    
    
    
private:
    
    string fileName;
    vector<string> encabezados;
    vector<vector<string>> data;
    int data_count;

};

#endif /* CSV_H */

