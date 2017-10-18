#include "Tabla.h"
#include "utils.h"

using namespace std;

Tabla::Tabla(const linear_set<string> &claves, 
             const vector<string> &campos, 
             const vector<Dato> &tipos) 
      {
    //QUE ONDAAA??
        for (auto it = claves.begin(); it != claves.end(); ++it) {
            _claves.insert(make_pair(*it, true));
        }

        for (int i = 0; i < campos.size(); i++) {
            _camposYtipos.insert(make_pair(campos[i], tipos[i]));
        }
}

//QUE ONDAAAAAAaa??
Tabla::const_iterador_registros Tabla::agregarRegistro(const Registro& r) {
    return Tabla::const_iterador_registros(
        linear_set<Registro>::const_iterator(_registros.insert(make_pair(_registros.size()+1, r))));
}

const linear_set<string>& Tabla::campos() const {
    return _camposYtipos.claves();
}

const linear_set<string>& Tabla::claves() const {
    return _claves.claves();
}

const Dato& Tabla::tipoCampo(const string& campo) const {
    return _camposYtipos.at(campo);
}
//Deberia ir llenando el vector res con los registros, no con el par<int, registro>
const linear_set<Registro> &Tabla::registros() const {
    linear_set<Registro> res;
    for (int i = 1; i < _registros.size()+1; ++i) {
        res.insert(_registros[i]);
    }
    return res;
}
//QUE ONDAAAAAAAA???
Tabla::const_iterador_registros Tabla::registros_begin() const {
  return Tabla::const_iterador_registros(_registros.begin());
}

//QUE ONDAAAAAAA??
Tabla::const_iterador_registros Tabla::registros_end() const {
  return Tabla::const_iterador_registros(_registros.end());
}

int Tabla::cant_registros() const {
  return _registros.size();
}

bool operator==(const Tabla& t1, const Tabla& t2) {
    if (not (t1.campos() == t2.campos())) {
        return false;
    } else if (not (t1.claves() == t2.claves())) {
        return false;
    } else {
        linear_set<string> cs = t1.campos();
        for (auto c : cs) {
            if (t1.tipoCampo(c).esNat() != t2.tipoCampo(c).esNat()) {
                return false;
            }
        }
        return t1.registros() == t2.registros();
    }
}

bool operator!=(const Tabla& t1, const Tabla& t2) {
    return not (t1 == t2);
}
