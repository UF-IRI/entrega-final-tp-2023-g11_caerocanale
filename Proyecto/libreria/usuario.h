#ifndef USUARIO_H
#define USUARIO_H
#include "global.h"



struct inscripcion{
    unsigned int idCurso;
    time_t fechaInscripcion;
}; typedef inscripcion Inscripcion;

struct asistencia{
    unsigned int idCliente;
    unsigned int cantClases=0;
    Inscripcion *clases;
}; typedef asistencia Asistencia;

struct susuario {
    unsigned int id;
    string apellido, nombre;
    string email, telefono;
    str nac;
    float cuota; //Mejoras a hacer con más tiempo
    //  bool aptoFisico;No está en el archivo
}; typedef struct susuario Usuario;


code agregarUsuario(Usuario **cliente,Asistencia **asist, unsigned int &cantCliente, Usuario nuevo);
#endif // USUARIO_H
