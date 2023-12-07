#include "usuario.h"
#include "archivos.h"

code agregarUsuario(Usuario *cliente,Asistencia *asist, unsigned int &cantCliente, Usuario nuevo)
{
    if (cantCliente==0){
        cliente[0] = nuevo;
        cliente[0].id = 1;

        asist[0].clases = new Inscripcion[1];
        asist[0].idCliente = 1;

        cantCliente++;
        return EXITO;
    }

    Usuario *ini  = &cliente[0],
        *fin = &cliente[cantCliente-1];

    while(true){
        if(ini->email == nuevo.email || ini->telefono == nuevo.telefono) //Revisemos que no este registrado ya su mail
            return::MAIL_OCUPADO;

        if(ini==fin)
            break;
        ini++;
    }



    cantCliente = resizeu(&cliente, cantCliente);
    cliente[cantCliente-1] = nuevo;
    cliente[cantCliente-1].id = cantCliente;

    cantCliente = resizea(&asist, cantCliente-1);
    asist[cantCliente-1].idCliente = cantCliente;
    asist[cantCliente-1].clases = new Inscripcion[1];


    return::EXITO;
}
