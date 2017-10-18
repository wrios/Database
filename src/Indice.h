#ifndef INDICE_H
#define INDICE_H

#include <string>
#include "string_map.h"
#include <map>
#include "Tabla.h"
#include "Registro.h"
//#include <stdio.h>
//#include <stdlib.h>
#include "string"

using namespace std;


class Indice {

public:

    Indice(Tabla tab, string campo, bool esString);


    ~Indice();


//    Indice& operator=(const Indice &);
//
//
//    bool operator==(const Indice& otro) const;
//
//
//    bool operator!=(const Indice& otro) const {return !(*this == otro);}


    void agregarRegistro(const Registro &r);


    string dameCampo() const;


private:

    bool _esString;
    string _campo;
    map<int, linear_set<Registro> > _indicesNat;
    string_map<linear_set<Registro> > _indicesStr;

};


#endif // INDICE_H
