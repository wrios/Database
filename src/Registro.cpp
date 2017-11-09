#include <iostream>
#include "Registro.h"
#include "utils.h"

using namespace std;



Registro::Registro(const vector<string>& campos, const vector<Dato>& datos){
    for (int i = 0; i < campos.size(); ++i) {
        _campos.insert(campos[i]);
        _camposYdatos.insert(make_pair(campos[i], datos[i]));
    }
};



const Dato& Registro::dato(const string& campo) const {
    return _camposYdatos.at(campo);
}


const linear_set<string> Registro::campos() const {
    return _campos;
}


bool operator==(const Registro& r1, const Registro& r2) {
    linear_set<string> c1 = r1.campos();
    linear_set<string> c2 = r2.campos();
    if (not (c1 == c2)) {
        return false;
    }
    linear_set<string> campos = r1.campos();
    for (auto c : campos) {
        if (r1.dato(c) != r2.dato(c)) {
            return false;
        }
    }
    return true;
}


ostream &operator<<(ostream &os, const Registro &r) {
    //os toma un linear_set
    //os << r._campoYdato.significados();
    return os;
}
