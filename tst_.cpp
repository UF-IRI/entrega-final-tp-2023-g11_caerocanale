/*
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "usuario.h"
using namespace testing;


code control(Asistencia *&asist, Clase *clases);
code lecturaClases(ifstream &arch, Clase *& clases, unsigned int &tam);
code lecturaClientes(ifstream &arch, Usuario *& cliente , unsigned int &cantCliente);
//code leerAsistencia(ifstream& arch, Asistencia *&asist, unsigned int CantAsistencia);
code leerBinario(ifstream & archi, Asistencia *& asist, Inscripcion *&insc);
int resizec(Clase *&clases, int tam);
int resizeu(Usuario *&cliente, int tam);
int resizea(Asistencia *& cliente, int tam);
int resizei(Inscripcion *& cliente, int tam);

void errores(code codigo);
code anotarClase (Clase *&clases, Asistencia *&asist,unsigned int idClase);
code bajarClase (Clase *&clases, Asistencia *&asist, unsigned int idClase);
int BuscarIdClases(Clase *clases, int horario, str nombre);
bool espacio(Clase clase, unsigned int h);
unsigned int cupoactual(Clase *& clases, unsigned int idclase, unsigned int cantAsistencias);

code agregarUsuario(Usuario *cliente,Asistencia* asist, unsigned int &cantCliente, str apellido, str nombre, str  email, str telefono, str nac, float cuota);




TEST_CASE("Hay espacio")
{
//bool hayEspacio(int nombre,unsigned int cupoActual, int*maximo);
    unsigned int name = 3; //streching
    unsigned int cupoActual = 30;
    int maximo = 40;
    bool espacio= hayEspacio(name, cupoActual, maximo);
    require(espacio== true);
    cupoActual = 80;
    bool espacio= hayEspacio(name, cupoActual, maximo);
    require(espacio== false);
}

TEST_CASE("Clases repetidas"){

    int num = 1;
    Asistencia  AsistUnica[5];
    for(int i = 0; i< 5; i++){
    AsistUnica[i].CursosInscriptos.idClase[0] = num +1;
    AsistUnica[i].CursosInscriptos.idClase[1] = num +2;
    AsistUnica[i].CursosInscriptos.idClase[2] = num +1;
    AsistUnica[i].CursosInscriptos.idClase[3] = num +2;
    AsistUnica[i].CursosInscriptos.idClase[4] = num +1;
    num++;
    }
    unsigned int cantinscriptos[5];
    unsigned int CantAsist = 5;
     for(int i = 0; i< 5; i++){
    cantinscriptos[i] = ClasesRepetidas(AsistUnica[i], CantAsist);
     }
    Asistencia Nueva[5];
    Nueva[1].CursosInscriptos.idClase= {2,3};
    Nueva[1].CursosInscriptos.idClase= {3,4};
    Nueva[1].CursosInscriptos.idClase= {4,5};
    Nueva[1].CursosInscriptos.idClase= {5,6};
    Nueva[1].CursosInscriptos.idClase= {6,7};

       for(int i = 0; i< 5; i++){
    require (AsistUnica[i].CursosInscriptos.idClase[i]==Nueva[1].CursosInscriptos.idClase[i]);
    check(cantinscriptos[i]==2);
    }
}

TEST_CASE(){
//unsigned int cupoactual(Asistencia* asistencias, unsigned int idclase, unsigned int cantAsistencias);
//Creo que ya la hice
    unsigned int cupos = 0;



    const int cantAsistencias = 2;
    Asistencia dummyAsistencias[cantAsistencias];

    // Guardo la datos
    for (int i = 0; i < cantAsistencias; i++) {
    dummyAsistencias[i].idCliente = i + 1;//id consecuente
    dummyAsistencias[i].cantInscriptos = 3; // creo 3 inscripciones
    dummyAsistencias[i].CursosInscriptos = new Inscripcion[dummyAsistencias[i].cantInscriptos];

    for (unsigned int j = 0; j < dummyAsistencias[i].cantInscriptos; j++) {
        dummyAsistencias[i].CursosInscriptos[j].idClase=1;
        dummyAsistencias[i].CursosInscriptos[j].fechaInscripcion=time(NULL);

    }

    }
    unsigned int idclase=1;

    // Llamada a la función para obtener el número de inscripciones
    cupos = cupoactual(dummyAsistencias, idclase, cantAsistencias);

    // Verificación del resultado usando REQUIRE
    REQUIRE(cupos == 2);

    // Liberar la memoria asignada dinámicamente
    for (unsigned int i = 0; i < cantAsistencias; i++)
    delete[] dummyAsistencias[i].CursosInscriptos;
    delete[] dummyAsistencias;


}

}
//unsigned int BuscarIdClases(Clases *clases, unsigned int horario, string nombre);

TEST_CASE(){
    unsigned int horario=8;
    string nombre = "spinning";
    Clases * clases[6];
    clases[0].id=1;
    clases[1].id=2;
    clases[2].id=3;
    clases[3].id=4;
    clases[4].id=5;
    clases[5].id=6;

    clases[0].nombre= "spinning";
    clases[1].nombre= "zumba" ;
    clases[2].nombre= "yoga";
    clases[3].nombre= "spining" ;
    clases[4].nombre= "boxeo";
    clases[5].nombre= "boxeo";

    clases[0].horario= 8;
    clases[1].horario= 9;
    clases[2].horario= 10;
    clases[3].horario= 8;
    clases[4].horario= 9;
    clases[5].horario= 10;


    unsigned int idClase = BuscarIdClases(clases, horario, nombre);
    require(idClase == 1);
    horario = 10;
    nombre = "boxeo";

    idClase = BuscarIdClases(clases, horario, nombre);
    require(idClase == 6);


}
TEST_CASE(){
//void inscribir(Asistencia *& asist, Clases *,unsigned int &CantAsistencias, unsigned int idcliente);
//VER como funciona la funcion y anota a los clientes

    Asistencia asist;
    asist.idCliente= 45 ;
    asist.cantInscriptos = 3;
    asist.CursosInscriptos.idClase[3]= {3,5,10};
    clases[0].id=1;
    clases[1].id=2;
    clases[2].id=3;
    clases[3].id=4;
    clases[4].id=5;
    clases[5].id=10;

    clases[0].nombre= "spinning";
    clases[1].nombre= "zumba" ;
    clases[2].nombre= "yoga";
    clases[3].nombre= "spining" ;
    clases[4].nombre= "boxeo";
    clases[5].nombre= "boxeo";

    clases[0].horario= 8;
    clases[1].horario= 9;
    clases[2].horario= 10;
    clases[3].horario= 8;
    clases[4].horario= 9;
    clases[5].horario= 10;

    inscribir(asist, clases, asist.cantInscriptos, asist.idCliente);
    require() ;
}
*/
/*
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
*/
