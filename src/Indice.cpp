#include "Indice.h"
Indice::Indice(const Tabla &tab, const string &campo, bool esString) {
    _campo = campo;
    _esString = esString;
    const_it_reg begin = tab.registros_begin();
    const_it_reg end = tab.registros_end();
    // recorro todos los registros en la tabla y agrego el iterador apuntando a cada registro a la lista del indice
    while (begin != end){
        this->agregarRegistro(begin);
        ++begin;
    }
}

const_it_regInd Indice::dameRegistros_begin(const Dato &d) const{
    if (_esString)
        return _indicesStr.at(d.valorStr()).begin();
    else
        return _indicesNat.at(d.valorNat()).begin();
}

const_it_regInd Indice::dameRegistros_end(const Dato &d) const {
    if (_esString)
        return _indicesStr.at(d.valorStr()).end();
    else
        return _indicesNat.at(d.valorNat()).end();

}

bool Indice::noTieneRegistros(const Dato &d) const {
    if (_esString){
        bool noTieneRegistros = _indicesStr.end() == _indicesStr.find(d.valorStr());
        if (!noTieneRegistros)
            noTieneRegistros = _indicesStr.at(d.valorStr()).empty();
        return noTieneRegistros;
    } else {
        bool noTieneRegistros = _indicesNat.end() == _indicesNat.find(d.valorNat());
        if (!noTieneRegistros)
            noTieneRegistros = _indicesNat.at(d.valorNat()).empty();
        return noTieneRegistros;
    }
}

void Indice::agregarRegistro(const_it_reg &r) {
    if (_esString){
        string valorCampo = r->dato(_campo).valorStr();
        _indicesStr[valorCampo].insert(r);
    }else{
        int valorCampo = r->dato(_campo).valorNat();
        _indicesNat[valorCampo].insert(r);
    }
}