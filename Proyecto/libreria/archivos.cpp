#include "archivos.h"

int resizec(Clase **clases, int tam){

    Clase *nueva = new Clase[tam+1]; //Creamos nueva estructura con la cantidad deseada

    for (int i = 0; i <tam; i++) //Cargamos la estructura nueva
        nueva[i] = *clases[i];


    delete []*clases; //Borramos la vieja

    *clases = nueva; // Apuntamos la estructura hacia la posicion de la nueva, con el tamaño deseado
    //nueva queda en la ram hasta el infinito?

    return tam+1;
}
int resizeu(Usuario **usu, int tam){

    Usuario *nueva = new Usuario[tam+1];

    for (int i = 0; i <tam; i++){
        nueva[i] = *usu[i];
    }

    delete []*usu;

    *usu = nueva;

    return tam+1;
}
int resizea(Asistencia ** asist, int tam){

    Asistencia *nueva = new Asistencia[tam+1];

    for (int i = 0; i <tam; i++){
        nueva[i] = *asist[i];
    }
    delete []*asist;
    *asist = nueva;
    return tam+1;
}
int resizei(Inscripcion **ins, int tam){

    Inscripcion *nueva = new Inscripcion[tam+1];

    for (int i = 0; i <tam; i++){
        nueva[i] = *ins[i];

    }
    delete[] *ins;
    *ins = nueva;
    return tam+1;
}

int reduI(Inscripcion ** ins, int tam){

    if (tam==2){
        Inscripcion *aux = new Inscripcion [1];
        aux[0] = *ins[0];

        delete[] *ins;
        *ins = aux;
        return tam-1;
    }

    Inscripcion *nueva = new Inscripcion[tam-1];

    for (int i = 0; i <tam; i++){
        nueva[i] = *ins[i];
    }
    delete[] *ins;
    *ins = nueva;
    return tam-1;
}

code control(Asistencia &asist, Clase *clase){

    code controlador = EXITO;

    for (unsigned int i =0; i<asist.cantClases; i++){
        for (unsigned int j = i+1; j<asist.cantClases; i++){

            if (clase[asist.clases[j].idCurso -1].horario == clase[asist.clases[i].idCurso -1].horario){ //Comprobamos que no haya sobreposición  de horario
                int h= (asist.clases[j].fechaInscripcion < asist.clases[i].fechaInscripcion)?i:j;
                code a = bajarClase(clase, asist, asist.clases[h].idCurso);
                if (a !=EXITO)
                    controlador=a;
            }
        }
    }
    return controlador;
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
            cantCliente++;

            getline(aux, linea, ',');
            cliente[cantCliente-1].id=stoul(linea);

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
            cliente[cantCliente-1].cuota=stof(linea);


        }
        return code::EXITO;
    }
    return code::ARCHIVOFALLO;
}


code leerAsistencia(ifstream& arch, Asistencia *&asist, unsigned int &CantAsistencia) {
    unsigned int i = 0;

    if (arch.is_open()) {
        arch.clear();
        arch.seekg(0);
        while (!arch.eof()) {
            arch.read((char*)(&asist[i].idCliente), sizeof(unsigned int));
            arch.read((char*)(&asist[i].cantClases), sizeof(unsigned int));
            resizea(&asist, i); //HACER UN RESIZE PARA ASISTENCIA
            CantAsistencia++;

            for (unsigned int j = 0; j < asist[i].cantClases; j++) {
                arch.read((char*)(&asist[i].clases[j].idCurso), sizeof(unsigned int));
                arch.read((char*)(&asist[i].clases[j].fechaInscripcion), sizeof(time_t));

                // Verificar si es necesario incrementar el tamaño del arreglo de Inscripcion
                resizei(&asist[i].clases, j); //IDEM ARRIBA
            }
            i++;
        }
        return code::EXITO;
    }
    return code::ARCHIVOFALLO;
}

void errores(code codigo){
    ifstream arch;
    string line;
    int i=-1;
    arch.open("../../Proyecto/Dataset_TP/codigosErrores.txt");

    if (arch.is_open()){
        do{
            getline(arch, line);
            i++;
        } while((int)codigo != i && !arch.eof());

        cout << line << endl;
    }
    else
        cout<< "Error al abrir" << endl;
    arch.close();
    return;
}
