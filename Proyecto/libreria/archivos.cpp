#include "archivos.h"
const str path = "../../Proyecto/Dataset_TP/";

time_t t = time(nullptr);
tm* now = localtime(&t);
str fecha = to_string(now->tm_year+1900) + to_string(now->tm_mon+1) + to_string(now->tm_wday);


int resizea(Asistencia ** asist, int tam){

    Asistencia *nueva = new Asistencia[tam+1];

    for (int i = 0; i <tam; i++)
        nueva[i] = *asist[i];

    for (int i = 0; i<(int)tam; i++)
        delete [] asist[i]->clases;
    delete []*asist;
    *asist = nueva;
    return tam+1;
}
int resizei(Inscripcion **ins, int tam){

    Inscripcion *nueva = new Inscripcion[tam+1];

    for (int i = 0; i <tam; i++)
        nueva[i] = *ins[i];


    delete[] *ins;
    *ins = nueva;
    return tam+1;
}

int redui(Inscripcion **ins, int tam){
    Inscripcion *nueva = new Inscripcion[tam-1];

    for (int i = 0; i <tam; i++)
        nueva[i] = *ins[i];


    delete[] *ins;
    *ins = nueva;
    return tam-1;
}

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

    for (int i = 0; i <tam; i++)
        nueva[i] = *usu[i];


    delete []*usu;
    *usu = nueva;

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

    ifstream arch(path+"iriClasesGYM.csv");
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

        arch.open(path+"iriClasesGYM.csv");
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

    ifstream arch(path+"iriClientesGYM.csv");
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

        arch.open(path+"iriClientesGYM.csv");
        getline(arch, linea);
        int i = 0;

        while(getline(arch, linea)){
            stringstream iss(linea);
            str dato;

            getline(iss, dato, del);
            aux[i].id=stoul(dato);

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

            i++;
        }
        arch.close();

        delete[]* cliente;
        *cliente = aux;

        return code::EXITO;
    }
    return code::ARCHIVOFALLO;
}

code escribirUsuario(Usuario usuario){

    ofstream archClientes(path+"iriClientesGYM.csv", ios::app); // Abre el archivo y escribe al final

    if (archClientes.is_open()) {
        // Escribe los datos del usuario en el archivo CSV
        archClientes << usuario.id << "," << usuario.apellido << "," << usuario.nombre << "," << usuario.email << ","
                     << usuario.telefono << "," << usuario.nac << "," << usuario.cuota << "\n";
        archClientes.close();

        return code::EXITO;
    }
    else
        return code::ARCHIVOFALLO;
}
code leerAsistencia( Asistencia **asist, unsigned int cantCliente, Clase *clases) {

    ifstream arch(path+fecha+"asistencia_IRI.dat", ios::binary);
    //asistencias_1697673600000.dat

    if (arch.is_open()) {
        Asistencia *aux = new Asistencia[cantCliente];
        if(aux==nullptr)
            return code::ARCHIVOFALLO;

        for (unsigned int i=0; i < cantCliente; i++){

            arch.read((char*)(&aux[i].idCliente), sizeof(unsigned int));
            arch.read((char*)(&aux[i].cantClases), sizeof(unsigned int));

            aux[i].clases = new Inscripcion[aux[i].cantClases];
            //resizei(&aux[i].clases, aux[i].cantClases);

            for (unsigned int j = 0; j < aux[i].cantClases; j++) {
                arch.read((char*)(&aux[i].clases[j]), sizeof(Inscripcion));
                clases[aux[i].clases[j].idCurso-1].cupoActual++;
            }
             code e = control(aux[i], clases);
        }

        arch.close();
        delete[]* asist;
        *asist = aux;

        return code::EXITO;
    }
    return code::ARCHIVOFALLO;
}


code escribirAsistencia(Asistencia *asist, unsigned int cantCliente) {

    ofstream archi(path+fecha+"asistencia_IRI.dat", ios::binary);
    if (archi.is_open()) {
        for (unsigned int i = 0; i < cantCliente; i++) {
            archi.write((char*)&asist[i].idCliente, sizeof(unsigned int));
            archi.write((char*)&asist[i].cantClases, sizeof(unsigned int));
            for (unsigned int j = 0; j < asist[i].cantClases; j++)
                archi.write((char*)&asist[i].clases[j], sizeof(Inscripcion));
        }
        archi.close();
        return code::EXITO;
    } else {
        return code::ARCHIVOFALLO;
    }
}
void errores(code codigo){
    ifstream arch;
    string line;
    int i=-1;
    arch.open(path+"codigosErrores.txt");

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
