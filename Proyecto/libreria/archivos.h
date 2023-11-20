#ifndef ARCHIVO_H
#define ARCHIVO_H
#include "global.h"
#include "clases.h"
#include "usuario.h"
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <sstream>




code control(Asistencia *&asist, Clase *clases);
code lecturaClases(ifstream &arch, Clase *& clases, unsigned int &tam);
code lecturaClientes(ifstream &arch, Usuario *& cliente , unsigned int &cantCliente);
code leerAsistencia(ifstream& arch, Asistencia *&asist, unsigned int CantAsistencia);
int resizec(Clase *&clases, int tam);
int resizeu(Usuario *&cliente, int tam);
int resizea(Asistencia *& cliente, int tam);
int resizei(Inscripcion *& cliente, int tam);

#endif // ARCHIVO_H

