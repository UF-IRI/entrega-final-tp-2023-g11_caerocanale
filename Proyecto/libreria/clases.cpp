#include "global.h"
#include "clases.h"
#include "archivos.h"



bool espacio(Clase clase, unsigned int h){
    return (ocupado[h] - clase.cupoActual > 0);
}

code anotarClase (Clase *clase, Asistencia &asist, unsigned int idClase){
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
        asist.cantClases = (unsigned int)resizei (&asist.clases, asist.cantClases);

        asist.clases[asist.cantClases -1].idCurso = idClase;
        asist.clases[asist.cantClases -1].fechaInscripcion = time(nullptr);
        return::EXITO;
    }
    return::REFERENCIA_ERRONEA;
}

code bajarClase (Clase *clase, Asistencia &asist, unsigned int idClase){
    if (idClase>60)
        return::REFERENCIA_ERRONEA;

    if (clase[idClase-1].id == idClase){

        for (unsigned int i=0; i<asist.cantClases; i++){

            if(asist.clases[i].idCurso == idClase){
                if (asist.cantClases==1){
                    asist.clases[i].idCurso = -1;
                    asist.clases[i].fechaInscripcion=-1;

                    asist.cantClases=0;
                } else {

                    for (unsigned int j=i; j<asist.cantClases-1; j++){
                        asist.clases[j].idCurso= asist.clases[j+1].idCurso;
                        asist.clases[j].fechaInscripcion= asist.clases[j+1].fechaInscripcion;
                    }//Luego de bajar la posición en uno de todos para luego reducir el tamaño de asist.clases

                    asist.cantClases = (unsigned int)redui (&asist.clases, asist.cantClases);
                }

                clase[idClase-1].cupoActual--;
                return::EXITO;
            }
        }
        return::HORARIO_LIBRE;
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
    return i+1;
}

unsigned int cupoactual(Asistencia *asist, unsigned int idclase, unsigned int cantAsistencias) {

    unsigned int contador = 0;
    unsigned int i = 0 ;
    while (i < cantAsistencias) {
        for (unsigned int j = 0; j<asist[i].cantClases; j++){
        if (asist[i].clases[j].idCurso == idclase)
            contador = contador + 1;
        }
        i++;
    }
    return contador;
}


