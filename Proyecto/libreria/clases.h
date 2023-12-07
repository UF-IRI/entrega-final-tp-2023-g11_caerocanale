#ifndef CLASES_H
#define CLASES_H
#include "global.h"
#include "usuario.h"




const string clases[6] = {"spinning", "yoga", "pilates", "stretching", "zumba", "boxeo"};
const int ocupado [6]={45, 25, 15,  40, 50, 30};

struct sclases {
    unsigned int id;
    str nombre;
    float horario;
    unsigned int cupoActual;
}; typedef sclases Clase;

typedef enum eCode code;


code anotarClase (Clase *clases, Asistencia &asist, unsigned int idClase);
code bajarClase (Clase *clases, Asistencia &asist, unsigned int idClase);
bool espacio(Clase clase, unsigned int h);
int BuscarIdClases(Clase *clases, float horario, str nombre);
unsigned int cupoactual(Asistencia *asist, unsigned int idclase, unsigned int cantAsistencias);


#endif // CLASES_H


