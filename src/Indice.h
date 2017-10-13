#ifndef INDICE_H
#define INDICE_H

#include <string>
#include "string_map.h"
#include <map>
#include "Tabla.h"
#include "Registro.h"

using namespace std;


class Indice {

public:

    Indice();


    Indice(Tabla tab, string campo);


    ~Indice();


    Indice& operator=(const Indice &);


    bool operator==(const Indice& otro) const;
    bool operator!=(const Indice& otro) const {return !(*this == otro);}





private:

    string_map<map<int, bool> > _indices;

};


#endif // INDICE_H
