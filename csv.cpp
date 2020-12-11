/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   csv.cpp
 * Author: dalva
 * 
 * Created on December 11, 2020, 1:15 PM
 */

#include <valarray>

#include "csv.h"

csv::csv() {
    //no hacer nada
}

csv::csv(string fileName) {
    this->fileName = fileName;

    load_file(false);
}

csv::csv(string fileName, bool encabezados) {
    this->fileName = fileName;

    load_file(encabezados);
}

csv::csv(const csv& orig) {
}

csv::~csv() {
}

//getters y setters

string csv::getFileName() {
    return fileName;
}

void csv::setFileName(string fileName) {
    this->fileName = fileName;
}

vector<string> csv::getEncabezados() {
    return encabezados;
}

vector<vector<string>> csv::getData() {
    return data;
}

int csv::getData_Count() {
    return data_count;
}

//funciones y metodos

void csv::load_file(bool hayEncabezados) {

    ifstream leerArchivo;

    leerArchivo.open(fileName);

    if (leerArchivo.is_open()) {
        cout << "El archivo existe" << endl;

        string buffer = "";

        if (hayEncabezados) {
            getline(leerArchivo, buffer);

            string datos = "";
            for (int i = 0; i < buffer.length(); i++) {

                if (buffer[i] == ',') {
                    encabezados.push_back(datos);
                    datos.clear();

                } else if (i == buffer.length() - 1) {
                    encabezados.push_back(datos);
                    datos.clear();

                } else {
                    datos += buffer[i];
                }

            }

            buffer.clear();

            while (getline(leerArchivo, buffer)) {
                
                buffer.clear();
                getline(leerArchivo, buffer);
                
                vector<string> listaD;
                string datos = "";
                for (int i = 0; i < buffer.length(); i++) {

                    if (buffer[i] == ',') {
                        listaD.push_back(datos);
                        datos.clear();

                    } else if (i == buffer.length() - 1) {
                        listaD.push_back(datos);
                        datos.clear();

                    } else {
                        datos += buffer[i];
                    }
                }

                data.push_back(listaD);
                listaD.clear();

            }

        } else {

            while (getline(leerArchivo, buffer)) {

                vector<string> listaD;
                string datos = "";
                for (int i = 0; i < buffer.length(); i++) {

                    if (buffer[i] == ',') {
                        listaD.push_back(datos);
                        datos.clear();

                    } else if (i == buffer.length() - 1) {
                        listaD.push_back(datos);
                        datos.clear();

                    } else {
                        datos += buffer[i];
                    }
                }

                data.push_back(listaD);
                listaD.clear();
            }
        }


    }

    cout << "No se encontro el archivo" << endl;

    leerArchivo.close();
}

void csv::write_file() {

    ofstream saveFile;
    saveFile.open(fileName, ofstream::out | ofstream::trunc);

    if (saveFile.is_open()) {


        if (encabezados.size() > 0) {

            for (int i = 0; i < encabezados.size(); i++) {
                string header = encabezados[i];

                saveFile << header << ',';
            }

            saveFile << endl;

        }


        for (int i = 0; i < data.size(); i++) {

            vector<string> datos = data[i];

            for (int i = 0; i < datos.size(); i++) {

                string data = datos[i];

                saveFile << data << ',';
            }

            saveFile << endl;
        }

    }

    saveFile.close();
}

void csv::print_data() {

    if (data.empty()) {
        cout << "No hay datos por mostrar...." << endl << endl;
    } else {

        if (encabezados.size() > 0) {
            for (int i = 0; i < encabezados.size(); i++) {

                cout << encabezados[i] << setw(10) <<"\t";
            }
        }

        cout << endl;


        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data [i].size(); j++) {
                cout << data [i][j] << setw(10) << "\t";
            }
            cout << endl;
        }
    }

}

vector<string> csv::get_row(int index) {

    if (index < data.size())
        return data[index];

}

vector<string> csv::get_column(int index) {

    vector<string> selectedColumn;

    if (index >= data[0].size()) {
        cout << "La columna deseada no existe" << endl << endl;
    } else {

        for (int i = 0; i < data.size(); i++) {
            vector<string> fila = data[i];
            string datos = fila[index];

            selectedColumn.push_back(datos);

        }

        return selectedColumn;
    }


}

vector<string> csv::get_max(int index) {

    int maxFila = 0;
    string maxTemp = "";
    string max = "";

    if (index >= data[0].size()) {
        cout << "Esa columna no existe!!" << endl;
    } else {

        for (int i = 0; i < data.size(); i++) {

            maxTemp = data[i][index];

            if (maxTemp > max) {
                max = maxTemp;
                maxFila = i;
            }
        }


        return data[maxFila];

    }
}

vector<string> csv::get_min(int index) {

    int minFila = 0;
    string minTemp = "";
    string min = "";

    if (index >= data[0].size()) {
        cout << "Esa columna no existe!!" << endl;
    } else {

        for (int i = 0; i < data.size(); i++) {

            minTemp = data[i][index];

            if (minTemp < min) {
                min = minTemp;
                minFila = i;
            }
        }


        return data[minFila];

    }
}

void csv::truncate_row(int row) {

    if (row >= data.size()) {
        cout << "La fila no existe !!!" << endl << endl;
    } else {
        data.erase(data.begin() + row);
        data_count = data_count - 1;
    }
}

void csv::truncate_column(int column) {

    if (column >= data[0].size()) {
        cout << "La columna seleccionada no existe" << endl << endl;
    } else {

        for (int i = 0; i < data.size(); i++) {

            vector<string> fila;
            fila = data[i];

            fila.erase(fila.begin() + column);

            data[i] = fila;
        }
    }
}

csv* csv::concat(csv* archivo1, string newName) {

    vector<string> headers = archivo1->getEncabezados();
    bool sonIguales = false;

    if (encabezados.size() > 0 && headers.size() > 0) {

       
        if (headers.size() == encabezados.size()) {

            for (int i = 0; i < headers.size(); i++) {

                if (headers[i] == encabezados[i]) {
                    sonIguales = true;
                } else {
                    sonIguales = false;
                }
            }
        } else {
            cout << "Hay discrepancia en los headers!" << endl << endl;
            sonIguales = false;
        }

    } else if (archivo1->getData().at(0).size() == data[0].size()) {
        sonIguales = true;
    }

    csv* archivo2;

    if (sonIguales) {

        archivo2 = new csv();

        for (int i = 0; i < data.size(); i++) {
            vector<string> fila = data[i];

            archivo2->getData().push_back(fila);
        }


        for (int i = 0; i < archivo1->getData().size(); i++) {
            vector<string> fila = archivo1->getData().at(i);

            archivo2->getData().push_back(fila);

        }

        archivo2->setFileName(newName);

        return archivo2;
    }


}

vector<vector<string>> csv::sort_data(int columna, bool esAscendete) {

    if (columna >= data[0].size()) {
        cout << "La fila ingresada no es valida!!!" << endl << endl;
        
    } else {

        if (esAscendete) {

            bool flag = true;

            while (flag) {

                flag = false;

                for (int i = 0; i < data.size() - 1; i++) {

                    string fila1 = data[i][columna];
                    string fila2 = data[i + 1][columna];

                    if (fila1 < fila2) {

                        vector<string> fila1 = data[i];
                        truncate_row(i);

                        data.push_back(fila1);

                        flag = true;
                    }

                }

            }

            return data;

        } else {

            bool flag = true;

            while (flag) {

                flag = false;

                for (int i = 0; i < data.size() - 1; i++) {

                    string fila1 = data[i][columna];
                    string fila2 = data[i + 1][columna];

                    if (fila1 > fila2) {

                        vector<string> fila2 = data[i+1];
                        truncate_row(i+1);

                        data.push_back(fila2);

                        flag = true;
                    }

                }

            }
            
            return data;
        }

    }
}