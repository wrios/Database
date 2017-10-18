#include <iostream>
#include "Registro.h"
#include "utils.h"

using namespace std;

//Registro::Registro(const vector<string>& campos, const vector<Dato>& datos) :
//    _campo(campos.begin(), campos.end()) {
//        for (int i = 0; i < campos.size(); i++) {
//            _datos.fast_insert(make_pair(campos[i], datos[i]));
//        }
//};

Registro::Registro(const vector<string>& campos, const vector<Dato>& datos) :
         _campoYdato(){
    for (int i = 0; i < campos.size(); ++i) {

        _campoYdato.insert(make_pair(campos[i], datos[i]));

    }
};



const Dato& Registro::dato(const string& campo) const {
    return _campoYdato.at(campo);
}

//Podemos cambiar lo que nos devuelven los metodos publicos de las clases??
const linear_set<string>& Registro::campos() const {
    return _campoYdato.claves(); //RECORDAR: claves() es un metodo de string_map que tiene que hacer Willy
}

bool operator==(const Registro& r1, const Registro& r2) {
    if (! seteq(r1.campos(), r2.campos())){
        return false;
    } else {
        for (auto it = r1.campos().begin(); it != r1.campos().end(); ++it) {
            if (r1.dato(*it) != r2.dato(*it)){
                return false;
            }
        }
    }

    return true;
}

ostream &operator<<(ostream &os, const Registro &r) {
    os << r._campoYdato.significados(); //RECORDAR: significados() es un metodo de string_map que tiene que hacer Willy
    return os;
}


int Registro::get_id() {
    return _id;
}


void Registro::set_id(int _id) {
    Registro::_id = _id;
}
