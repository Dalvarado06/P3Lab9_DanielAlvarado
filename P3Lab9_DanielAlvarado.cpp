/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   P3Lab9_DanielAlvarado.cpp
 * Author: dalva
 *
 * Created on December 11, 2020, 12:59 PM
 */

#include <cstdlib>
#include "csv.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    csv* leer = new csv("prototipoChikito.csv", true);
    
    leer->print_data();
    
    vector<string> fila;
     
    leer->truncate_column(0);
    
//    for(int i = 0; i < fila.size(); i++){
//        cout << fila[i] << endl;
//    }
    
    leer->print_data();
    
    delete leer;
    
    return 0;
}

