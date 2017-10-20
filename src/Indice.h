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

    Indice(const Tabla tab,const string campo, bool esString);
    //constructor de indice

//    Indice(const Tabla tab,const string campo, const string& valorStr);
    //el constructor de indice se crea con un string map

//    Indice(const Tabla tab,const string campo, const int valorNat);
    //el constructor de indice se crea con un ABBV(arbol binario de busqueda valanciado)

    //~Indice();


//    Indice& operator=(const Indice &);
//
//
//    bool operator==(const Indice& otro) const;
//
//
//    bool operator!=(const Indice& otro) const {return !(*this == otro);}


    void agregarRegistro(const Registro &r);


    string dameCampo() const;
    //el indice tiene mas de un campo, "s"


private:

    bool _esString;
    string _campo;
    map<int, linear_set<const Registro*> > _indicesNat;
    string_map<linear_set<const Registro*> > _indicesStr;

};


#endif // INDICE_H
