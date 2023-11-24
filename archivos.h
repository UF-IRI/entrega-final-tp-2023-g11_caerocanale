#ifndef ARCHIVO_H
#define ARCHIVO_H

#include "global.h"
#include "clases.h"
#include "usuario.h"

#include <stdio.h>
#include <fstream>
#include <sstream>


code control(ifstream &arch, Asistencia &asist, Clase *&clase, Usuario *& Cliente, unsigned int tam);
code lecturaClases(ifstream &arch, Clase *& clases, unsigned int &tam);
code lecturaClientes(ifstream &arch, Usuario *& cliente , unsigned int &cantCliente);
unsigned int leerBinario(ifstream& archi, Asistencia*& asist);
int resizec(Clase *&clases, int tam);
int resizeu(Usuario *&cliente, int tam);
int resizea(Asistencia *& cliente, int tam);
int resizei(Inscripcion *& cliente, int tam);

void errores(code codigo);

#endif // ARCHIVO_H

