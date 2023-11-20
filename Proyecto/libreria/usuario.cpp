#include "usuario.h"

code agregarUsuario(Usuario *cliente,Asistencia* asist, unsigned int &cantCliente, str apellido, str nombre, str  email, str telefono, str nac, float cuota)
{

    Usuario *ini  = &cliente[0],
        *fin = &cliente[cantCliente-1];

    while(true){
        if(ini->email == email) //Revisemos que no este registrado ya su mail
            return::MAIL_OCUPADO;

        if(ini==fin)
            break;
        ini++;
    }

    //añadimos los datos en un espacio vacio
    cliente[cantCliente].apellido = apellido;
    cliente[cantCliente].id= cantCliente+1;
    cliente[cantCliente].nombre = nombre;
    cliente[cantCliente].email = email;
    cliente[cantCliente].telefono = telefono;
    cliente[cantCliente].nac  =  nac;
    cliente[cantCliente].cuota = cuota;

    asist[cantCliente].idCliente=cantCliente+1;

    cantCliente++;

    return::EXITO;
}
