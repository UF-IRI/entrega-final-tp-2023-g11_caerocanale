#include "archivo.h"
#include <clases.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

eCode leer(sClase *&arch){

    ifstream infile("../../Proyecto/Dataset_TP/iriClasesGYM.csv"); //Abrimos el csv
    if (!infile.is_open()) { //Prueba de que no haya errores
        cout << "Error opening CSV file" << endl;
        return::ARCHIVOFALLO;
    }

    arch = new sClase[7];

    for (int i=0; i<7; i++){
        arch[i].disponibilidad = new sTurnos[1];
    }
    string header;
    getline(infile, header); //Leemos el header

    int index=0, pos=0;

    string line;

    char delimiter = ',';

    string idCurso, nombre, turno;
    bool primer=true;
    stringstream iss;

    while (infile.good()) { //Comprobamos que el archivo no esté vacio

        getline(infile, line);  //Leemos linea por linea
        iss<< line;

        getline(iss, idCurso, delimiter); //identificador
        getline(iss, nombre, delimiter); //Nombre de la clase
        getline(iss, turno, delimiter); //Turno de la clase



        if (nombre != arch[index].nombre && !primer) {// Al cambiar el nombre de la clase, sabemos que cambiamos de clase, por lo que haremos un resize y
            index++; //Empezamos a llenar la siguiente clase
            pos = 0;
            //Agregar resize que disminuya el array de pos en uno
        }

        arch[index].disponibilidad[pos].idclase = stoi(idCurso);
        arch[index].nombre = nombre;


        arch[index].disponibilidad[pos].hora = stof(turno);
        pos++; //Aumentamos la posicion y un resize a las clases

        arch[index].id = index+1; //Id de la clase

        primer=false;

    }
    infile.close(); //Cerramos el archivo
    return::EXITO;
}





int resize (sClase *&arch, int tam){

    arch = new sClase[tam];
    sClase *nueva = new sClase[tam+1]; //Creamos nueva estructura con la cantidad deseada

    for (int i = 0; i <tam; i++) //Cargamos la estructura nueva
        nueva[i] = arch[i];


    delete []arch; //Borramos la vieja

    arch = nueva; // Apuntamos la estructura hacia la posicion de la nueva, con el tamaño deseado
    //nueva queda en la ram hasta el infinito?

    return tam+1;
}

int resize (sTurnos *&arch, int tam){
    //Revisar resize de sClase, es igual pero con sTurnos
    arch = new sTurnos[tam];
    sTurnos *nueva = new sTurnos[tam+1];

    for (int i = 0; i <tam; i++){
        nueva[i] = arch[i];
    }

    delete []arch;

    arch = nueva;

    return tam+1;
}

int resize (sUsuario *&arch, int tam){
    //Revisar resize de sClase, es igual pero con sUsuario
    arch = new sUsuario[tam];
    sUsuario *nueva = new sUsuario[tam+1];

    for (int i = 0; i <tam; i++){
        nueva[i] = arch[i];
    }

    delete []arch;

    arch = nueva;

    return tam+1;
}


