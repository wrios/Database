#include <iostream>
#include "Registro.h"
#include "utils.h"

using namespace std;

string_map<Dato> Registro::datos() const{
    return _datos;
}

//Registro::Registro(const vector<string>& campos, const vector<Dato>& datos) :
//    _campo(campos.begin(), campos.end()) {
//        for (int i = 0; i < campos.size(); i++) {
//            _datos.fast_insert(make_pair(campos[i], datos[i]));
//        }
//};

Registro::Registro(const vector<string>& campos, const vector<Dato>& datos){
    for (int i = 0; i < campos.size(); ++i) {
        _campos.insert(campos[i]);
        _datos.insert(pair(campos[i], datos[i]));
    }
};



const Dato& Registro::dato(const string& campo) const {
    return _datos.at(campo);
}

//Podemos cambiar lo que nos devuelven los metodos publicos de las clases??
const linear_set<string> Registro::campos() const {
    return _campos; //RECORDAR: claves() es un metodo de string_map que tiene que hacer Willy
}

bool operator==(const Registro& r1, const Registro& r2) {
    if (! seteq(r1.campos(), r2.campos())){
        return false;
    } else {
        auto it2 = r2.datos().begin();
        for (auto it = r1.datos().begin(); it != r1.datos().end(); ++it) {
            if (*it != *it2){
                return false;
            }
            ++it2;
            if(it2 == r2.datos().end()){
                return false;
            }
        }
    }

    return true;
}

ostream &operator<<(ostream &os, const Registro &r) {
    //os toma un linear_set
    //os << r._campoYdato.significados(); //RECORDAR: significados() es un metodo de string_map que tiene que hacer Willy
    return os;
}
