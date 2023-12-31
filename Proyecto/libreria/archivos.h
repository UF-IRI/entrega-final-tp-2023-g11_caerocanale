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
code lecturaClases(Clase ** clases, unsigned int &tam);
code lecturaClientes(Usuario ** cliente , unsigned int &cantCliente);
code leerAsistencia( Asistencia **asist, unsigned int cantCliente, Clase *clases);


int resizea(Asistencia ** asist, int tam);
int resizei(Inscripcion **ins, int tam);
int resizec(Clase **clases, int tam);
int resizeu(Usuario **usu, int tam);
int redui(Inscripcion **ins, int tam);

void errores(code codigo);

code escribirAsistencia(Asistencia *asist, unsigned int cantCliente);
code escribirUsuario(Usuario usuario);
#endif // ARCHIVO_H

