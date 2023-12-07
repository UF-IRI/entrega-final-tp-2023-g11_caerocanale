
#include "catch2/catch.hpp"
#include "usuario.h"
#include "clases.h"
#include "archivos.h"
#include "global.h"


/*

code control(ifstream &arch, Asistencia *&asist, Clase *&clase, Usuario *& Cliente, unsigned int tam);
code lecturaClases(Clase ** clases, unsigned int &tam);
code lecturaClientes(Usuario ** cliente , unsigned int &cantCliente);
code escribirAsistencia(Asistencia **asist, unsigned int cantAsistencias, Clase clases);
code EscribirClientes(susuario& usuario);
*/
/*
//code anotarClase (Clase *clases, Asistencia &asist, unsigned int idClase);
//code bajarClase (Clase *clases, Asistencia &asist, unsigned int idClase);
unsigned int BuscarIdClases(Clase *clases, float horario, str nombre);
unsigned int cupoactual(Asistencia *asist, unsigned int idclase, unsigned int cantAsistencias);
//bool espacio(Clase clase, unsigned int h);

*/




TEST_CASE("anotarClase y bajarClase") {
    // Configura datos de prueba
    Clase *clases = new Clase[1];  // Asegúrate de tener datos válidos en tus clases
    Asistencia *asist = new Asistencia[2];
    unsigned int tam=0;
    unsigned int cantCliente;// Asegúrate de tener datos válidos en tu asistencia

    Asistencia aux[2] = {{1, 0, NULL}, {2, 0, NULL}};
    for (int i=0; i<2; i++)
        asist[i] = aux[i];
    code error = lecturaClases(&clases, tam);

    REQUIRE(error==EXITO);


    // Caso 1: anotarClase con éxito
    REQUIRE(anotarClase(clases, asist[1], 1) == EXITO);
    REQUIRE(asist[1].cantClases == 1);

    // Caso 2: intentar anotar una clase ya ocupada
    REQUIRE(anotarClase(clases, asist[1], 1) == HORARIO_OCUPADO);

    // Caso 3: bajarClase con éxito
    REQUIRE(bajarClase(clases, asist[1], 1) == EXITO);
    REQUIRE(asist[1].cantClases == 0);

    // Caso 4: intentar bajar una clase no inscrita
    REQUIRE(bajarClase(clases, asist[0], 1) == HORARIO_LIBRE);


}



TEST_CASE("ARCHIVOS")
{
    SECTION("CSV"){

        Clase *clase =  new Clase[1];
        unsigned int tam =0;
        code error = lecturaClases(&clase, tam);
        REQUIRE(clase[0].id == 1);
        REQUIRE(error == EXITO);
        delete []clase;
    }
}



TEST_CASE("CLASES"){
    Clase clase[2] = {
        {1, "spinning", 8, 1},
        {2, "spinning", 9, 2}
    };
    Clase *clases = new Clase[2];

    for (int i =0; i<2; i++)
        clases[i]=clase[i];
    Usuario *nuevo = new Usuario[1];
    Usuario lautaro = {1, "Canale", "Lautaro", "laezca@gmail.com", "222222", "02-12-2003", 0};
    Usuario lucila = {2, "Caero", "Lucila", "caero@gmail.com,", "33333333", "12-03-2004", 0};
    nuevo[0] = lautaro;
    Asistencia vacio[1];
    vacio[0].idCliente=1;
    vacio[0].cantClases=2;
    vacio[0].clases[0].fechaInscripcion=22222;
    vacio[0].clases[1].fechaInscripcion=33333;
    vacio[0].clases[0].idCurso=1;
    vacio[0].clases[0].idCurso=2;
    Asistencia *asist = new Asistencia[1];
    asist[0] = vacio[0];
    unsigned int tam =1;
    code error;


/*    SECTION("Nuevo usuario"){
        error = agregarUsuario(nuevo, asist, tam, lucila);
        REQUIRE(nuevo[1].apellido == "Caero");
        REQUIRE(error==code::EXITO);
    }*/
    SECTION("Anotar clase"){
        error = anotarClase(clases, asist[1], 1);
        REQUIRE(clases[0].cupoActual==2);
        REQUIRE(asist[1].cantClases==1);
        REQUIRE(error==EXITO);
        error = anotarClase(clases, asist[1], 1);
        REQUIRE(clases[0].cupoActual==2);
        REQUIRE(asist[1].cantClases==1);
        REQUIRE(error==HORARIO_OCUPADO);
    }
    SECTION("bajar"){
        error = bajarClase(clases, asist[0], 2);
        REQUIRE(clases[1].cupoActual==0);
        REQUIRE(asist[0].cantClases==1);
        REQUIRE(error==EXITO);
        error = bajarClase(clases, asist[0], 2);
        REQUIRE(clases[1].cupoActual==0);
        REQUIRE(asist[0].cantClases==1);
        REQUIRE(error==HORARIO_LIBRE);
    }
    SECTION("Info clases"){
        int id = BuscarIdClases(clases, 8, "spinning");
        REQUIRE(id==1);
    }
    delete []clases;
    delete []nuevo;
    for (unsigned int i=0; i<tam; i++)
     delete asist[i].clases;
    delete []asist;
}
