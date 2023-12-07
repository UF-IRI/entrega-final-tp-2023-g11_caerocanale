#include "usuario.h"
#include "archivos.h"

code agregarUsuario(Usuario **cliente,Asistencia** asist, unsigned int &cantCliente, Usuario nuevo)
{

    Usuario *ini  = cliente[0],
        *fin = cliente[cantCliente-1];

    while(true){
        if(ini->email == nuevo.email || ini->telefono == nuevo.telefono) //Revisemos que no este registrado ya su mail
            return::MAIL_OCUPADO;

        if(ini==fin)
            break;
        ini++;
    }


    //añadimos los datos en un espacio vacio
    cantCliente = resizeu(cliente, cantCliente);
    cliente[cantCliente-1]->id = cantCliente;

    cantCliente = resizea(asist, cantCliente-1);
    asist[cantCliente-1]->idCliente=cantCliente;

    return::EXITO;
}
