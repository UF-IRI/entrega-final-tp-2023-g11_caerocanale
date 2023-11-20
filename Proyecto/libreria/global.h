#ifndef GLOBAL_H
#define GLOBAL_H


#include <string>
#include <iostream>
#include <ctime>

using namespace std;

enum eCode {EXITO = 0,ARCHIVOFALLO, HORARIO_LIBRE, CLASE_CERRADA, HORARIO_OCUPADO, REFERENCIA_ERRONEA, MAIL_OCUPADO };

typedef enum eCode code;
typedef string str;

#endif // GLOBAL_H



