#include "catch2/catch.hpp"
#include "archivos.h"
#include "usuario.h"
#include "clases.h"



TEST_CASE("ARCHIVOS")
{
    Clase *clase =  new Clase[1];
    unsigned int tam =0;

    code error = lecturaClases(&clase, tam);

    errores(error);

    for (unsigned int i = 0; i < 10; i++)
        cout << clase[i].id << "\t" << clase[i].nombre << endl;

    cout << endl << endl;

    REQUIRE(clase[0].id == 1);
    REQUIRE(error == EXITO);

    Usuario *usu = new Usuario[1];
    unsigned int clientes=0;
    error = lecturaClientes(&usu, clientes);

    errores(error);

    for (int i = 0; i < 10 ; i++)
        cout << usu[i].id << "\t" << usu[i].apellido << endl;

    REQUIRE (usu[0].id == 1);
    REQUIRE(error == EXITO);

    delete []usu;
    delete []clase;
}
/*
TEST_CASE("Usuarios nuevo"){

    Usuario *usu = new Usuario[1];

    usu[0].apellido = "Bodoque";
    usu[0].nombre = "Juan Carlos";
    usu[0].cuota = 0;
    usu[0].email = "l@g";
    usu[0].id = 1;
    usu[0].nac = "2-12-2003";
    usu[0].telefono = "11223344";

    unsigned int cantClientes = 1;

    Asistencia *asist = new Asistencia[1];

    asist[0].idCliente = 1;
    asist[0].cantClases = 0;

    Usuario nuevo = {1, "Canale", "Lautaro", "laezca@gmail", "11232233", "2-12-2003", 0};
    code error = agregarUsuario(usu, asist, cantClientes, nuevo);

    REQUIRE (error == code::EXITO);
    REQUIRE (usu[1].id == 2);
    REQUIRE (asist[1].idCliente==2);

    delete []usu;
    for (unsigned int i = 0; i<cantClientes; i++)
        delete [] asist[i].clases;
    delete []asist;
}
*/

/*
TEST_CASE("CLASES"){





    Usuario *nuevo = NULL;
    Usuario pablo[1] = {{1, "Canale", "Lautaro", "laezca@gmail.com", "222222", "02-12-2003", 0}};
    nuevo[0] = pablo[0];


    Asistencia vacio[1];
    vacio[0].idCliente=1;
    vacio[0].cantClases=2;
    vacio[0].clases[0].fechaInscripcion=22222;
    vacio[0].clases[1].fechaInscripcion=33333;
    vacio[0].clases[0].idCurso=1;
    vacio[0].clases[0].idCurso=2;

    Asistencia *asist = NULL;
    asist[0] = vacio[0];

    unsigned int tam =1;
    code error;
    SECTION("Nuevo usuario"){
    error = agregarUsuario(nuevo, asist, tam, "Bodoque", "Juan", "juanca@gmail.com", "111111", "12-2-2003", 0);

    REQUIRE(nuevo[1].apellido == "Bodoque");
    REQUIRE(error==code::EXITO);
    }
    SECTION("Anotar clase"){
    error = anotarClase(clases, asist[1], 1);

    REQUIRE(clases[0].cupoActual==2);
    REQUIRE(asist[1].cantClases==1);
    REQUIRE(error==code::EXITO);

    error = anotarClase(clases, asist[1], 1);

    REQUIRE(clases[0].cupoActual==2);
    REQUIRE(asist[1].cantClases==1);
    REQUIRE(error==code::HORARIO_OCUPADO);
    }

    SECTION("bajar"){

    error = bajarClase(clases, asist[0], 2);

    REQUIRE(clases[1].cupoActual==0);
    REQUIRE(asist[0].cantClases==1);
    REQUIRE(error==code::EXITO);

    error = bajarClase(clases, asist[0], 2);

    REQUIRE(clases[1].cupoActual==0);
    REQUIRE(asist[0].cantClases==1);
    REQUIRE(error==code::HORARIO_LIBRE);
    }

    SECTION("Info clases"){
    int id = BuscarIdClases(clases, 8, "spinning");

    REQUIRE(id==1);

    }



    delete []clases;
    delete []nuevo;
    delete asist->clases;
    delete []asist;
}
*/
