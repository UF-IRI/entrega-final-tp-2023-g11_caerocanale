#include "archivos.h"

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
int resizea(Asistencia *& cliente, int tam){
    //Revisar resize de Clase, es igual pero con Usuario
    cliente = new Asistencia[tam];
    Asistencia *nueva = new Asistencia[tam+1];

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


code control(Asistencia &asist, Clase *&clase){
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


code lecturaClases(Clase ** clases, unsigned int &tam){

    ifstream arch("../../Proyecto/Dataset_TP/iriClasesGYM.csv");
    string linea;
    char del = ',';

    tam =0;
    if(arch.is_open()){

        getline(arch, linea);//Leemos el header
        while(getline(arch,linea))
            tam++;
        arch.close();


        Clase *aux = new Clase [tam];
        if (aux==nullptr)
            return code::ARCHIVOFALLO;

        arch.open("../../Proyecto/Dataset_TP/iriClasesGYM.csv");
        getline(arch, linea);

        int i =0;
        while (getline(arch,linea)){
            stringstream iss(linea);
            str dato;

            getline(iss, dato, del);
            aux[i].id = stoul(dato);

            getline(iss, dato, del);
            aux[i].nombre = dato;

            getline(iss, dato, del);
            aux[i].horario = stof(dato);

            i++;
        }

        delete[] *clases;

        *clases = aux;

        arch.close();

        return code::EXITO;
    }
    return code::ARCHIVOFALLO;
    //agregar si hay un error
}

code lecturaClientes(Usuario ** cliente , unsigned int &cantCliente){

    ifstream arch("../../Proyecto/Dataset_TP/iriClasesGYM.csv");
    string linea;
    char del = ',';

    cantCliente =0;
    if(arch.is_open()){

        getline(arch, linea);//Leemos el header
        //idCliente,nombre,apellido,email,telefono,fechaNac,estado

        while (getline(arch,linea))
            cantCliente++;
        arch.close();


        Usuario *aux = new Usuario [cantCliente];
        if (aux==nullptr)
            return code::ARCHIVOFALLO;

        arch.open("../../Proyecto/Dataset_TP/iriClasesGYM.csv");
        getline(arch, linea);
        int i = 0;

        while(getline(arch, linea)){
            stringstream iss(linea);
            str dato;

<<<<<<< Updated upstream
    if (arch.is_open()) {
        arch.clear();
        arch.seekg(0);
        while (!arch.eof()) {
            arch.read((char*)(&asist[i].idCliente), sizeof(unsigned int));
            arch.read((char*)(&asist[i].cantClases), sizeof(unsigned int));
            resizea(asist, i); //HACER UN RESIZE PARA ASISTENCIA
            CantAsistencia++;
=======
            getline(iss, dato, del);
            aux[i].id=stoul(dato);
>>>>>>> Stashed changes

            getline(iss, dato, del);
            aux[i].nombre=dato;

            getline(iss, dato, del);
            aux[i].apellido=dato;

            getline(iss, dato, del);
            aux[i].email=dato;

            getline(iss, dato, del);
            aux[i].telefono=dato;

            getline(iss,dato, del);
            aux[i].nac=dato;

            getline(iss, dato, del);
            aux[i].cuota=stof(dato);

<<<<<<< Updated upstream
                // Verificar si es necesario incrementar el tamaño del arreglo de Inscripcion
                resizei(asist[i].clases, j); //IDEM ARRIBA
            }
=======
>>>>>>> Stashed changes
            i++;
        }
        arch.close();

        delete[]* cliente;
        *cliente = aux;

        return code::EXITO;
    }
    return code::ARCHIVOFALLO;
}



code leerAsistencia( Asistencia **asist, unsigned int cantCliente, Clase *clases) {

    ifstream arch("../../Proyecto/Dataset_TP/asistencias_1697673600000.dat", ios::binary);
    unsigned int i =0;

    if (arch.is_open()) {
        Asistencia *aux = new Asistencia[cantCliente];
        if(aux==nullptr)
            return code::ARCHIVOFALLO;

        while (!arch.eof()) {

            arch.read((char*)(&aux[i].idCliente), sizeof(unsigned int));
            arch.read((char*)(&aux[i].cantClases), sizeof(unsigned int));

            aux[i].clases = new Inscripcion[aux[i].cantClases];
            //resizei(&aux[i].clases, aux[i].cantClases);

            for (unsigned int j = 0; j < aux[i].cantClases; j++) {
                arch.read((char*)(&aux[i].clases[j]), sizeof(Inscripcion));
                clases[aux[i].clases[j].idCurso-1].cupoActual++;
            }
            code e = control(aux[i], clases);
            i++;
        }

        if (cantCliente != i)
            cout << "diferencia de usuarios y asistencias por " << (int)i-(int)cantCliente << " usuarios" << endl;
        arch.close();
        delete[]* asist;
        *asist = aux;

        return code::EXITO;
    }
    return code::ARCHIVOFALLO;
}
void errores(code codigo){
    ifstream arch;
    string line;
    int i=-1;
    arch.open("../../Proyecto/Datatset_TP/codigosErrores.txt");

    if (arch.is_open()){
        do{
            getline(arch, line);
            i++;
        } while((int)codigo != i && !arch.eof());

        cout << line << endl;
    }
    else
        cout<< "Error al abrir" << endl;
    return;
}
