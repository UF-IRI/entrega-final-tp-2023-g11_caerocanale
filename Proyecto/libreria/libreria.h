#ifndef LIBRERIA_H
#define LIBRERIA_H

#include "libreria_global.h"

class LIBRERIA_EXPORT Libreria
{
public:
    Libreria();
};
code anotarClase (Clase clase, Asistencia *asist, float horario);
code bajarClase (Clase *clase, Asistencia *asist, unsigned int idClase);
bool espacio(Clase clase, unsigned int h);
int BuscarIdClases(Clase *clases, int horario, str nombre);
#endif // LIBRERIA_H
