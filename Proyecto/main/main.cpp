#include "archivos.h"
#include "clases.h"
#include "usuario.h"
#include "global.h"


int main() {
/*
    Clase clase;
    Clase* clases = &clase;
    Usuario  usua;
    Usuario * cliente = &usua;
    Asistencia asistencia;
    Asistencia* asist = &asistencia;
    unsigned int cantCliente =0;
    unsigned int tam=0;
    unsigned int cantAsist = 0;
    code error;

    //abro archivos
    ifstream arch;
    arch.open("../../Proyecto/Datatset_TP/iriClasesGYM.csv",ios::in);
    error = lecturaClases(arch,clases,tam);
    arch.close();

    arch.open("../../Proyecto/Datatset_TP/iriClientesGYM.csv",ios::in);
    error = lecturaClientes(arch,cliente,cantCliente);
    arch.close();

    arch.open("../../Proyecto/Datatset_TP/asistencias_1697673600000.dat",ios::binary);
    error = leerAsistencia(arch, asist, cantAsist);
    arch.close();

    errores(error);


    bool menu = 1;
    bool seguridad=0;
    float horario;
    string eleccion;

    while (menu){
        cout << "Usted pertenece a 1.Clase, o desea 2.Registrarse ?" << endl;
        int ref;
        cin >> ref;

        switch (ref){
        case 1:

            cout << "Usted desea anotarse/bajarse de una clase, es eso correcto? 1.Si 0.No: "; //Metodo de seguridad para reconocer si hubo un error incial
            cin >> seguridad;

            while (seguridad){
                cout << "Bienvenido/a " << cliente->nombre << endl;
                cout << "Desea 1.anotarse o 2.darse de baja?" << endl;
                cin >> ref;

                cout << "Escriba el horario a anotarse: ";

                cin >> horario;

                //El cliente ingresa los datos de las clases y comparamos lo escrito con datos pregrabados del dia y el tipo de clase a anotarse
                if(horario>=7&& horario<=21){
                    cout << "Escriba en minuscula la clase: ";
                    cin >> eleccion;
                    int idClase = BuscarIdClases(clases, horario, eleccion);
                    switch (ref){

                    case 1:

                        error =  anotarClase (clases, asist, idClase);
                        break;

                    case 2:
                        error = bajarClase (clases, asist, idClase);
                        break;

                    default:
                        cout << "No es una opcion, vuelva a intentar" << endl;
                        error = (code)5;
                    }

                    errores(error);


                    cout << "Desea registrarse o darse de baja de otra clase? 1.si 0.no" << endl;

                    cin >> seguridad;
                }

                break;

            case 2:
            {
                string apellido, nombre;
                string email, telefono;
                str nac;
                cout << "Ingrese su nombre: ";
                cin >> nombre;
                cout << "Ingrese su apellido: ";
                cin >> apellido;
                cout << "Ingrese su email: ";
                cin >> email;
                cout << "Ingrese su telefono: ";
                cin >> telefono;
                cout << "Ingrese su fecha de nacimiento en el siguiente formato: ";
                cout << "dia-mes-anio";
                cin >> nombre;
                unsigned int cant=0;
                error = agregarUsuario (cliente, asist, cant, apellido, nombre, email, telefono, nac, 0);

                errores(error);

                break;
            }
            default:
                cout << "No es una opcion, vuelva a intentar" << endl;
            }

            cout << "Quiere hacer algo mas? 1.Si 0.No";
            cin >> menu;
        }

    }
    //Borrar las memorias dinamicas.
    delete []cliente;
    delete []clases;
    for (unsigned int i=0; i<asist->cantClases; i++)
        delete asist[i].clases;
    delete []asist;
    //eliminar el de inscripciones
    return 0;
    */

    Clase *clase =  new Clase[1];
    unsigned int tam =0;

    code error = lecturaClases(&clase, tam);

    errores(error);

    for (unsigned int i = 0; i < 10; i++)
        cout << clase[i].id << "\t" << clase[i].nombre << endl;

    cout << endl << endl;
    Usuario *usu = new Usuario[1];
     Usuario nuevo = {1, "Canale", "Lautaro", "laezca@gmail", "11232233", "2-12-2003", 0};
    usu[0] = nuevo;
    Asistencia *asi = new Asistencia[1];
    asi[0].idCliente = 1;
    unsigned int cantClientes = 1;

    error = anotarClase(clase, asi[0],5);
    errores(error);

    error = leerAsistencia(&asi, cantClientes, clase);

    errores(error);


}
