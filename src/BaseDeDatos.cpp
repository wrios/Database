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
    _indices.insert(make_pair(nombre, string_map<Indice>()));
}

void BaseDeDatos::agregarRegistro(const Registro &r, const string &nombre) {
    Tabla &t = _nombresYtablas.at(nombre);
    const_it_reg rIt = t.agregarRegistro(r);
    for (auto it = _indices.at(nombre).begin(); it != _indices.at(nombre).end(); ++it) {
        it->second.agregarRegistro(rIt);
    }
}

const linear_set<string> BaseDeDatos::tablas() const {
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
    const Tabla &t = dameTabla(nombre);
    const Dato &d = t.tipoCampo(campo);
    bool b = d.esString();
    Indice ind = Indice(t, campo, b);
    _indices[nombre][campo] = ind;
}

const Indice* BaseDeDatos::dameIndice(const string &tabla, const string &campo) const {
    return &(_indices.at(tabla).at(campo));
}
BaseDeDatos::join_iterator::join_iterator(const_it_reg &endT,
                                          const_it_regInd &endI,
                                          bool t): itTabla(endT), endTabla(endT), itIndice(endI), endIndice(endI){
    finaliza = t;
}

void BaseDeDatos::join_iterator::setearItIndices(const Dato &d) {
    itIndice = indice->dameRegistros_begin(d);
    endIndice = indice->dameRegistros_end(d);
}

BaseDeDatos::join_iterator::join_iterator(const BaseDeDatos &bd,
                                          const string &tablaSinIndice,
                                          const string &tablaConIndice,
                                          const string &campoIndice,
                                          bool tabla1TieneI,
                                          const_it_reg &endT,
                                          const_it_regInd &endI) :  itTabla(endT), endTabla(endT), itIndice(endI), endIndice(endI){
    tabla1TieneIndice = tabla1TieneI;
    campo = campoIndice;
    indice = bd.dameIndice(tablaConIndice, campo);
    itTabla = bd.dameTabla(tablaSinIndice).registros_begin();
    endTabla = bd.dameTabla(tablaSinIndice).registros_end();
    if (itTabla != endTabla){
        Dato d = itTabla->dato(campo);
        // busco que haya registros en indice que coincidan con el valor que estoy iterando en itTabla
        while(itTabla != endTabla and indice->noTieneRegistros(d)){
            d = itTabla->dato(campo);
            ++itTabla;
        }
        // hay 2 posibilidades acá, que haya llegado al endTabla o que haya encontrado registros que coinciden con
        // el valor que estoy iterando en itTabla (me importa este ultimo)
        if (itTabla != endTabla)
            setearItIndices(itTabla->dato(campo));
    }
    finaliza = (itTabla == endTabla);
}

BaseDeDatos::join_iterator::join_iterator(const BaseDeDatos::join_iterator& otro): itTabla(otro.itTabla), endTabla(otro.endTabla), itIndice(otro.itIndice), endIndice(otro.endIndice){
    indice = otro.indice;
    finaliza = otro.finaliza;
    campo = otro.campo;
    tabla1TieneIndice = otro.tabla1TieneIndice;
}

bool BaseDeDatos::join_iterator::operator==(const BaseDeDatos::join_iterator & otro) const{
    return ((finaliza and otro.finaliza) or
            (itTabla == otro.itTabla and itIndice == otro.itIndice and endTabla == otro.endTabla and endIndice == otro.endIndice));
}

bool BaseDeDatos::join_iterator::operator!=(const BaseDeDatos::join_iterator & otro) const{
    return !(*this == otro);
}

BaseDeDatos::join_iterator BaseDeDatos::join_iterator::operator++(){
    // avanzo al siguiente registro que coindice el valor de itTabla en el indice
    ++itIndice;
    if (itIndice == endIndice){
        // llegue al final de los registros en indice que coinciden con el valor de itTabla
        ++itTabla;
        if (itTabla == endTabla){
            // llegue al final de los registros en tabla por lo tanto terminé de recorrer el join
            finaliza = true;
        }else{
            Dato d = itTabla->dato(campo);
            //me fijo el valor de itTabla y busco registros que coincidan con ese valor
            while(itTabla != endTabla and indice->noTieneRegistros(d)){
                d = itTabla->dato(campo);
                ++itTabla;
            }
            // hay 2 casos: o llegué al final de los registros en tabla o encontre el siguiente registro de la tabla
            // que tiene registros que coinciden el valor en el indice
            if (itTabla == endTabla)
                finaliza = true;
            else
                setearItIndices(itTabla->dato(campo));
        }
    }
    return *this;
}

BaseDeDatos::join_iterator BaseDeDatos::join_iterator::operator++(int a){
    BaseDeDatos::join_iterator njoin(*this);
    ++(*this);
    return njoin;
}

// Armo un nuevo registro a partir de los campos y datos de dos registros,
// teniendo el primer registro prioridad ante campos repetidos frente al r2
Registro combinarRegistros(const Registro &r1, const Registro &r2){
    vector<string> campos;
    vector<Dato> datos;
    for (const string &campo: r2.campos()) {
        campos.push_back(campo);
        datos.push_back(r2.dato(campo));
    }
    for (const string &campo: r1.campos()) {
        campos.push_back(campo);
        datos.push_back(r1.dato(campo));
    }
    Registro registroCombinado = Registro(campos, datos);
    return registroCombinado;
}

Registro BaseDeDatos::join_iterator::operator*(){
    // pregunto si la primera tabla que mande como parametro al join es la que tiene indice ya que esta tiene prioridad
    // frente a campos repetidos en registros
    if (tabla1TieneIndice)
        return combinarRegistros(**itIndice, *itTabla);
    else
        return combinarRegistros(*itTabla, **itIndice);
}

BaseDeDatos::join_iterator BaseDeDatos::join(const string &tabla1, const string &tabla2, const string &campo) const {
    bool tabla1TieneIndice = _indices.end() != _indices.find(tabla1);
    if (tabla1TieneIndice)
        tabla1TieneIndice = _indices.at(tabla1).end() != _indices.at(tabla1).find(campo);
    // armo 2 iteradores para pasar al constructor y no tener que llamar a los
    // constructores por defecto a la hora de usar el constructor del join
    const_it_reg endIt = this->dameTabla(tabla1).registros_end();
    const_it_regInd endI = linear_set<const_it_reg>().end();
    if (tabla1TieneIndice)
        return BaseDeDatos::join_iterator(*this, tabla2, tabla1, campo, tabla1TieneIndice, endIt, endI);
    else
        return BaseDeDatos::join_iterator(*this, tabla1, tabla2, campo, tabla1TieneIndice, endIt, endI);
}

BaseDeDatos::join_iterator BaseDeDatos::join_end() const {
    // armo 2 iteradores para pasar al constructor y no tener que llamar a los constructores
    // por defecto a la hora de usar el constructor del join
    Tabla t = Tabla(linear_set<string>(),
                    vector<string>(),
                    vector<Dato>());
    const_it_reg endT = t.registros_end();
    const_it_regInd endI = linear_set<const_it_reg>().begin();
    return join_iterator(endT, endI, true);
}