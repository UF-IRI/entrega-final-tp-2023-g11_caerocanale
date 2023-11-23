#include "global.h"
#include "clases.h"
#include "usuario.h"



bool espacio(Clase clase, unsigned int h){
    return (ocupado[h] - clase.cupoActual > 0);
}

code anotarClase (Clase *&clase, Asistencia &asist, unsigned int idClase){
    if (idClase>60)
        return::REFERENCIA_ERRONEA;
    if (clase[idClase-1].id == idClase){
        int h=0;
        while(clase[idClase-1].nombre != clases[h] && h<7)
            h++;
        if(!espacio(clase[idClase-1], h))
            return::CLASE_CERRADA;

        for (unsigned int i=0; i<asist.cantClases; i++){
            if(asist.clases[i].idCurso == idClase)
                return::HORARIO_OCUPADO;
        }

        clase[idClase-1].cupoActual++;
        asist.cantClases++;
        asist.clases[asist.cantClases -1].idCurso = idClase;
        asist.clases[asist.cantClases -1].fechaInscripcion = time_t(0);
        return::EXITO;
    }
    return::REFERENCIA_ERRONEA;
}

code bajarClase (Clase *&clase, Asistencia &asist, unsigned int idClase){
    if (idClase>60)
        return::REFERENCIA_ERRONEA;
    if (clase[idClase-1].id == idClase){
        for (unsigned int i=0; i<asist.cantClases; i++){
            if(asist.clases[i].idCurso == idClase){
                for (unsigned int j=i; j<asist.cantClases-1; j++){
                    asist.clases[j].idCurso= asist.clases[j+1].idCurso;
                    asist.clases[j].fechaInscripcion= asist.clases[j+1].fechaInscripcion;
                }
                clase[idClase-1].cupoActual--;
                return::EXITO;
            }
            return::HORARIO_LIBRE;
        }
    }
    return::REFERENCIA_ERRONEA;
}



int BuscarIdClases(Clase *clases, float horario, str nombre){
    int i = 0;
    while(clases[i].horario != horario && clases[i].nombre != nombre && i<61){
        i++;
    }
    if (i>60)
        return -1;
    return i;
}

unsigned int cupoactual(Clase *& clases, unsigned int idclase, unsigned int cantAsistencias) {

    unsigned int contador = 0;
    unsigned int i = 0 ;
    while (i < cantAsistencias) {
        if (clases[i].id == idclase)
            contador = contador + 1;
        i++;
    }
    return contador;
}


