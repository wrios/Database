#include "BaseDeDatos.h"
#include <list>
#include <tuple>
#include <algorithm>

BaseDeDatos::BaseDeDatos(){};

void BaseDeDatos::crearTabla(const string &nombre, 
                             const linear_set<string> &claves,
                             const vector<string> &campos,
                             const vector<Dato> &tipos) {
  _nombresYtablas.insert(make_pair(nombre, Tabla(claves, campos, tipos)));
}

void BaseDeDatos::agregarRegistro(Registro &r, const string &nombre) {
    Tabla &t = _nombresYtablas.at(nombre);
    r.set_id(t.registros().size());
    t.agregarRegistro(r);
}

const linear_set<string> &BaseDeDatos::tablas() const {
    return _nombresYtablas.claves(); }

const Tabla &BaseDeDatos::dameTabla(const string &nombre) const {
  return _nombresYtablas.at(nombre);
}

int BaseDeDatos::uso_criterio(const BaseDeDatos::Criterio &criterio) const {
  if (_criteriosYusos.count(criterio)) {
    return _criteriosYusos.at(criterio);
  } else {
    return 0;
  }
}

//CHEQUEAR COMPLEJIDAD
bool BaseDeDatos::registroValido(const Registro &r, const string &nombre) const {
  const Tabla &t = _nombresYtablas.at(nombre);

  return (t.campos() == r.campos() and _mismos_tipos(r, t) and
          _no_repite(r, t));
}

bool BaseDeDatos::_mismos_tipos(const Registro &r, const Tabla &t) const {
  for (auto c : t.campos()) {
    if (r.dato(c).esNat() != t.tipoCampo(c).esNat()) {
      return false;
    }
  }
  return true;
}

bool BaseDeDatos::_no_repite(const Registro &r, const Tabla &t) const {
  list<Registro> filtrados(t.registros().begin(), t.registros().end());
  for (auto clave : t.claves()) {
    _filtrar_registros(clave, r.dato(clave), filtrados);
  }
  return filtrados.empty();
}

list<Registro> &
BaseDeDatos::_filtrar_registros(const string &campo, const Dato &valor,
                                list<Registro> &registros) const {
  return _filtrar_registros(campo, valor, registros, true);
}

list<Registro> &BaseDeDatos::_filtrar_registros(const string &campo,
                                                const Dato &valor,
                                                list<Registro> &registros,
                                                bool igualdad) const {
  auto iter = registros.begin();
  while ( iter != registros.end()) {
    auto now = iter;
    iter++;
    if ((not igualdad) xor now->dato(campo) != valor) {
      registros.erase(now);
    }
  }

  return registros;
}

pair<vector<string>, vector<Dato> > BaseDeDatos::_tipos_tabla(const Tabla &t) {
  vector<string> res_campos;
  vector<Dato> res_tipos;
  for (auto c : t.campos()) {
    res_campos.push_back(c);
    res_tipos.push_back(t.tipoCampo(c));
  }
  return make_pair(res_campos, res_tipos);
}

bool BaseDeDatos::criterioValido(const Criterio &c,
                                 const string &nombre) const {
  const Tabla &t = _nombresYtablas.at(nombre);
  for (auto restriccion : c) {
    if (not t.campos().count(restriccion.campo())) {
      return false;
    }
    if (t.tipoCampo(restriccion.campo()).esNat() != 
        restriccion.dato().esNat()) {
      return false;
    }
  }
  return true;
}

Tabla BaseDeDatos::busqueda(const BaseDeDatos::Criterio &c,
                            const string &nombre) {
  if (_criteriosYusos.count(c)) {
    _criteriosYusos.at(c)++;
  } else {
    _criteriosYusos.fast_insert(make_pair(c, 1));
  }

  const Tabla &ref = dameTabla(nombre);
  auto campos_datos = _tipos_tabla(ref);
  Tabla res(ref.claves(), campos_datos.first, campos_datos.second);
  list<Registro> regs(ref.registros().begin(), ref.registros().end());
  for (auto restriccion : c) {
    _filtrar_registros(restriccion.campo(), restriccion.dato(),
                       regs, restriccion.igual());
  }
  for (auto r : regs) {
    res.agregarRegistro(r);
  }
  return res;
}

linear_set<BaseDeDatos::Criterio> BaseDeDatos::top_criterios() const {
  linear_set<Criterio> ret;
  int max = 0;
  for (auto crit_count : _criteriosYusos) {
    if (crit_count.second >= max) {
      if (crit_count.second > max) {
        ret = linear_set<Criterio>();
        max = crit_count.second;
      }
      ret.fast_insert(crit_count.first);
    }
  }
  return ret;
}

void BaseDeDatos::crearIndice(const string &nombre, const string &campo) {
    Tabla t = dameTabla(nombre);
    Dato d = t.tipoCampo(campo);
    bool b = d.esString();
    Indice ind = Indice(t, campo, b);
    _indices[nombre][campo] = ind;
}


BaseDeDatos::join_iterator::join_iterator(const join_iterator& otro) :
    it(otro.it){}


//BaseDeDatos::join_iterator& BaseDeDatos::join_iterator::operator=(const join_iterator & otro){
//
//}

bool BaseDeDatos::join_iterator::operator==(const BaseDeDatos::join_iterator & otro) const{
    return it == otro.it;
}

bool BaseDeDatos::join_iterator::operator!=(const BaseDeDatos::join_iterator & otro) const{
    return !(it == otro.it);
}

BaseDeDatos::join_iterator BaseDeDatos::join_iterator::operator++(){
    ++it;
    return *this;
}

Registro BaseDeDatos::join_iterator::operator*(){
    return *it;
}

Registro *BaseDeDatos::join_iterator::operator->(){
    return &(*it);
}


BaseDeDatos::join_iterator BaseDeDatos::join(const string &tabla1, const string &tabla2, const string &campo) const {

}


