#include "archivos.h"
#include "clases.h"
#include "usuario.h"
#include "global.h"


int main() {


    Clase* clases = new Clase[1];
    Usuario * cliente = new Usuario[1];
    Asistencia* asist = new Asistencia[1];
    unsigned int cantCliente =0;
    unsigned int tam=0;
    code error;


    error = lecturaClases(&clases,tam);
    errores(error);


    error = lecturaClientes(&cliente,cantCliente);
    errores(error);


    error = leerAsistencia(&asist, cantCliente, clases);
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
                unsigned int id;
                cout << "Ingrese su numero de identificacion que se le asisgno: ";
                cin >> id;
                cout << "Bienvenido/a " << cliente[id-1].nombre << endl;

                do{
                    cout << "Desea 1.anotarse o 2.darse de baja?" << endl;
                    cin >> ref;

                    cout << "Escriba el horario a eleccion: ";

                    cin >> horario;

                    //El cliente ingresa los datos de las clases y comparamos lo escrito con datos pregrabados del dia y el tipo de clase a anotarse
                    if(horario>=7&& horario<=21){
                        cout << "Escriba en minuscula el nombre de la clase: ";
                        cin >> eleccion;
                        int idClase = BuscarIdClases(clases, horario, eleccion);
                        switch (ref){

                        case 1:

                            error =  anotarClase(clases, asist[id-1], idClase);
                            break;

                        case 2:
                            error = bajarClase (clases, asist[id-1], idClase);
                            break;

                        default:
                            cout << "No es una opcion, vuelva a intentar" << endl;
                            error = (code)5;
                        }

                        errores(error);


                        cout << "Desea registrarse o darse de baja de otra clase? 1.si 0.no" << endl;

                        cin >> seguridad;
                    }
                }while (seguridad);
                    break;

                case 2:
                {
                    Usuario nuevo;
                    string apellido, nombre;
                    string email, telefono;
                    str nac;
                    cout << "Ingrese su nombre: ";
                    cin >> nuevo.nombre;
                    cout << "Ingrese su apellido: ";
                    cin >> nuevo.apellido;
                    cout << "Ingrese su email: ";
                    cin >> nuevo.email;
                    cout << "Ingrese su telefono: ";
                    cin >> nuevo.telefono;
                    cout << "Ingrese su fecha de nacimiento en el siguiente formato: ";
                    cout << "dia-mes-anio";
                    cin >> nuevo.nac;

                    error = agregarUsuario (cliente, asist, cantCliente, nuevo);
                    errores(error);

                    cout << "Su numero de identificacion es " << cantCliente << " es importante que lo recuerde";

                    error = escribirUsuario(cliente[cantCliente-1]);

                    break;
                }
                default:
                cout << "No es una opcion, vuelva a intentar" << endl;

            cout << "Quiere hacer algo mas? 1.Si 0.No";
            cin >> menu;
        }

    }
    error = escribirAsistencia(asist, cantCliente);
    errores(error);

    delete []cliente;
    delete []clases;
    for (unsigned int i=0; i<cantCliente; i++)
        delete asist[i].clases;
    delete []asist;
    return 0;






    return 0;
}
