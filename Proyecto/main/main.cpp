#include "archivos.h"
#include "clases.h"
#include "usuario.h"



#include "global.h"


int main() {
    Clase* clases;
    Usuario * cliente;
    Asistencia* asist;
    unsigned int cantCliente;
    unsigned int tam=1;


    //abro archivos
    ifstream arch;
    arch.open("clasesGYM.csv",ios::in);
    lecturaClases(arch,clases,tam);
    arch.close();
    arch.open("clientesGYM.csv",ios::in);
    lecturaClientes(arch,cliente,cantCliente);
    arch.close();
    arch.open("asistenciasGYM.dat",ios::binary);
    arch.close();

    bool menu = 1;
    bool seguridad;
    unsigned int horario;
    string eleccion;
    int error;
    while (menu){
        cout << "Usted pertenece a 1.Clase, 2.Musculito ?" << endl;
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
                horario -= 8;

                //El cliente ingresa los datos de las clases y comparamos lo escrito con datos pregrabados del dia y el tipo de clase a anotarse
                if(horario>=7&& horario<=21){
                    cout << "Escriba en minuscula la clase: ";
                    cin >> eleccion;
                    int idClase = BuscarIdClases(clases, horario, eleccion);
                    switch (ref){

                    case 1:

                        error =  anotarClase (&clases, asist, idClase);
                        break;

                    case 2:
                        error = bajarClase (&clases, asist, idClase);
                        break;

                    default:
                        cout << "No es una opcion, vuelva a intentar" << endl;
                    }


                    switch (error){
                    case HORARIO_LIBRE:
                        cout  << "Lo sentimos, pero parece que usted no se encuentra anotado a ninguna clase de las " << horario+8 <<"hs"<<endl;
                        break;

                    case CLASE_CERRADA:
                        cout << "La clase de las "<<horario+8<<"hs se encuentra completa, o no se  da en ese horario, lo lamentamos" << endl;
                        break;

                    case HORARIO_OCUPADO:
                        cout  << "Lo sentimos, pero parece que usted ya se encuentra anotado a una clase a las " << horario+8 <<"hs "<< endl;
                        break;

                    case REFERENCIA_ERRONEA:
                        cout << "Hubo un error al revisar sus datos, por favor, vuelva a intentarlo" << endl;
                        break;

                    case EXITO:
                        cout << "La funcion se ha completado con exito";
                        break;

                    default:
                        break;
                    }

                    cout << "Desea registrarse o darse de baja de otra clase? 1.si 0.no" << endl;

                    cin >> seguridad;
                }

                break;

            case 2:

                break;

            default:
                cout << "No es una opcion, vuelva a intentar" << endl;
            }

            cout << "Quiere hacer otro cambio? 1.Si 0.No";
            cin >> menu;
        }


        //Borrar las memorias dinamicas.
        delete []cliente;
        delete []clases;
        delete []asist;
        //eliminar el de inscripciones
        return 0;
    }
}
