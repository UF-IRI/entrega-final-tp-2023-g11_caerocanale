#include "usuario.h"
#include "archivos.h"

code agregarUsuario(Usuario **cliente,Asistencia **asist, unsigned int &cantCliente, Usuario nuevo)
{
    if (cantCliente==0){
        *cliente[0] = nuevo;
        cliente[0]->id = 1;

        asist[0]->clases = new Inscripcion[1];
        asist[0]->idCliente = 1;

        cantCliente++;
        return EXITO;
    }

    Usuario *ini  = cliente[0],
        *fin = cliente[cantCliente-1];

    while(true){
        if(ini->email == nuevo.email || ini->telefono == nuevo.telefono) //Revisemos que no este registrado ya su mail
            return::MAIL_OCUPADO;

        if(ini==fin)
            break;
        ini++;
    }



    Usuario *aux = new Usuario[cantCliente+1];
    for (unsigned int i=0; i<cantCliente; i++)
        aux[i] = *cliente[i];

    aux[cantCliente] = nuevo;
    aux[cantCliente].id = cantCliente+1;


    Asistencia *aux2 = new Asistencia[cantCliente+1];
    for (unsigned int i=0; i<cantCliente; i++)
        aux2[i] = *asist[i];

    aux2[cantCliente].idCliente = cantCliente+1;
    aux2[cantCliente].clases = new Inscripcion[1];

    delete[] *cliente;
    *cliente = aux;

    for(unsigned int i=0; i<cantCliente; i++)
        delete[] asist[i]->clases;

    delete[] *asist;

    *asist = aux2;


    cantCliente++;

    return::EXITO;
}
