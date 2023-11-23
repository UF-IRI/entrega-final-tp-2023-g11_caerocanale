#include "catch2/catch.hpp"
#include "archivos.h"

TEST_CASE("ARCHIVOS")
{
    ifstream archClases;
    archClases.open("iriClasesGYM.csv");
    Clase clases;
    Clase *clase =  &clases;
    unsigned int tam =0;

    code error = lecturaClases(archClases, clase, tam);

    cout << error << endl;
    REQUIRE(clase[0].id == 1);
    REQUIRE(error == EXITO);

    REQUIRE(0 == 0);
    delete []clase;
}


#include "usuario.h"
#include "clases.h"

TEST_CASE("CLASES"){


    Clase clase[2] = {
                        {1, "spinning", 8, 1},
                        {2, "spinning", 9, 2}
    };
    Clase *clases = NULL;
    for (int i =0; i<2; i++)
        clases[i]=clase[i];


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
    delete asist->clases;
    delete []asist;
}
