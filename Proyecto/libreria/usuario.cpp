#include "usuario.h"
#include "archivos.h"

code agregarUsuario(Usuario *cliente,Asistencia* asist, unsigned int &cantCliente, str apellido, str nombre, str  email, str telefono, str nac, float cuota)
{

    Usuario *ini  = &cliente[0],
        *fin = &cliente[cantCliente-1];

    while(true){
        if(ini->email == email || ini->telefono == telefono) //Revisemos que no este registrado ya su mail
            return::MAIL_OCUPADO;

        if(ini==fin)
            break;
        ini++;
    }

    //añadimos los datos en un espacio vacio
    cantCliente = resizeu(cliente, cantCliente);

    cliente[cantCliente-1].apellido = apellido;
    cliente[cantCliente-1].id= cantCliente;
    cliente[cantCliente-1].nombre = nombre;
    cliente[cantCliente-1].email = email;
    cliente[cantCliente-1].telefono = telefono;
    cliente[cantCliente-1].nac  =  nac;
    cliente[cantCliente-1].cuota = cuota;

    cantCliente = resizea(asist, cantCliente-1);

    asist[cantCliente-1].idCliente=cantCliente;


    return::EXITO;
}
