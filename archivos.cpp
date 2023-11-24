#include "archivos.h"


void resizea(Asistencia*& asist, unsigned int &tam){
    if(asist==nullptr){
        asist = new Asistencia[++tam];
        return;
    }

    Asistencia* temp = new Asistencia[++tam];

    for(unsigned int i = 0; i < tam-1; i++)
        temp[i] = asist[i];

    asist = temp;

}
int resizec(Clase *&clases, int tam){
    clases = new Clase[tam];
    Clase *nueva = new Clase[tam+1]; //Creamos nueva estructura con la cantidad deseada
    for (int i = 0; i <tam; i++) //Cargamos la estructura nueva
        nueva[i] = clases[i];
    delete []clases; //Borramos la vieja
    clases = nueva; // Apuntamos la estructura hacia la posicion de la nueva, con el tamaño deseado
    //nueva queda en la ram hasta el infinito?
    return tam+1;
}
int resizeu(Usuario *&cliente, int tam){
    //Revisar resize de Clase, es igual pero con Usuario
    cliente = new Usuario[tam];
    Usuario *nueva = new Usuario[tam+1];
    for (int i = 0; i <tam; i++){
        nueva[i] = cliente[i];
    }
    delete []cliente;
    cliente = nueva;
    return tam+1;
}
int resizei(Inscripcion *& cliente, int tam){
    //Revisar resize de Clase, es igual pero con Usuario
    cliente = new Inscripcion[tam];
    Inscripcion *nueva = new Inscripcion[tam+1];
    for (int i = 0; i <tam; i++){
        nueva[i] = cliente[i];
    }
    delete []cliente;
    cliente = nueva;
    return tam+1;
}



code lecturaClases(ifstream &arch, Clase *& clases, unsigned int &tam){
    string linea;
    stringstream aux;

    if(arch.is_open()){

        string header;
        getline(arch, header);//Leemos el header

        while(!arch.eof() && getline(arch, linea)){
            aux.clear();
            aux<<linea;
            tam= resizec(clases,tam);
            getline(aux, linea, ',');
            clases[tam-1].id=stoi(linea);//identificador
            getline(aux, linea, ',');
            clases[tam-1].nombre=linea;//Nombre de la clase
            getline(aux,linea);
            clases[tam-1].horario=stoi(linea);//Turno de la clase
        }
        return code::EXITO;
    }
    return code::ARCHIVOFALLO;
    //agregar si hay un error
}
code lecturaClientes(ifstream &arch, Usuario *& cliente , unsigned int &cantCliente){

    string linea;
    stringstream aux;

    if(arch.is_open()){

        string header;
        getline(arch, header);//Leemos el header
        //idCliente,nombre,apellido,email,telefono,fechaNac,estado
        while(!arch.eof() && getline(arch, linea)){
            aux.clear();
            aux<<linea;

            cantCliente= resizeu(cliente, cantCliente);
            getline(aux, linea, ',');
            cliente[cantCliente-1].id=stoi(linea);

            getline(aux, linea, ',');
            cliente[cantCliente-1].nombre=linea;

            getline(aux, linea, ',');
            cliente[cantCliente-1].apellido=linea;

            getline(aux, linea, ',');
            cliente[cantCliente-1].email=linea;

            getline(aux, linea, ',');
            cliente[cantCliente-1].telefono=linea;

            getline(aux,linea);
            cliente[cantCliente-1].nac=linea;//Turno de la clase

            getline(aux, linea, ',');
            cliente[cantCliente-1].cuota=stoi(linea);


        }
    }
    return code::EXITO;
}
unsigned int leerBinario(ifstream& archi, Asistencia*& asist) {
    if (archi.is_open()) {
        archi.clear();
        archi.seekg(0);

        unsigned int cantAsistencia = 0; // Variable para saber cantidad de asistencias

        while (!archi.eof()) {
            resizea(asist, cantAsistencia);

            Asistencia* nAsistencia = &asist[cantAsistencia - 1]; // Obtener la dirección de la nueva asistencia

            archi.read((char*)&nAsistencia->idCliente, sizeof(unsigned int));
            archi.read((char*)&nAsistencia->cantClases, sizeof(unsigned int)); // Leer cada asistencia

            nAsistencia->clases = new Inscripcion[nAsistencia->cantClases]; // Crear inscripciones de ese tamaño

            for (unsigned int j = 0; j < nAsistencia->cantClases; j++) {
                archi.read((char*)&nAsistencia->clases[j], sizeof(Inscripcion)); // Leer cada inscripcion
            }
        }

        return cantAsistencia; // Devolver la cantidad de asistencias leídas
    }

    return 4; // Hace takataka
}

code control(ifstream &arch, Asistencia &asist, Clase *&clases, Usuario *& cliente, unsigned int tam){
    // no estoy segura pero le agregue tam y cliente porque no funciona sino
    code controlador = EXITO;
    string linea;
    stringstream aux;
    unsigned int cantCliente=0;
    for (unsigned int i =0; i<asist.cantClases; i++){
        for (unsigned int j = i+1; j<asist.cantClases; i++){
            if (clases[asist.clases[j].idCurso -1].horario == clases[asist.clases[i].idCurso -1].horario){ //Comprobamos que no haya sobreposición  de horario
                int h= (asist.clases[j].fechaInscripcion < asist.clases[i].fechaInscripcion)?i:j;
                code a = bajarClase(clases, asist, asist.clases[h].idCurso);
                if (a !=EXITO)
                    controlador=a;
            }
            while(!arch.eof() && getline(arch, linea)){
                aux.clear();
                aux<<linea;
                tam++;
                getline(aux, linea, ',');
                clases[tam-1].id=stoul(linea);//identificador
                getline(aux, linea, ',');
                clases[tam-1].nombre=linea;//Nombre de la clase
                getline(aux,linea);
                clases[tam-1].horario=stof(linea);//Turno de la clase
            }
            return code::EXITO;
        }
        while(!arch.eof() && getline(arch, linea)){
            //Esta cliente pero no esta pasado como parametro
            aux.clear();
            aux<<linea;
            cantCliente++;
            getline(aux, linea, ',');
            cliente[cantCliente-1].id=stoul(linea);
            getline(aux, linea, ',');
            cliente[cantCliente-1].nombre=linea;
            cliente[cantCliente-1].nac=linea;//Turno de la clase
            getline(aux, linea, ',');
            cliente[cantCliente-1].cuota=stof(linea);
        }
        return code::EXITO;
    }
    return code::ARCHIVOFALLO;
}


//CODIGO ASISTENCIA
void errores(code codigo){
    ifstream arch;
    string line;
    int i=-1;
    arch.open("codgiosErrores.txt");
    arch.open("../../Proyecto/Datatset_TP/codigosErrores.txt");
    if (arch.is_open()){
        do{
            getline(arch, line);
            i++;
        } while((int)codigo != i && !arch.eof());
    cout << line << endl;
    }
    else
    cout<< "Error no encontrado" << endl;
cout<< "Error al abrir" << endl;
return;
}
