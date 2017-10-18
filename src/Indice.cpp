#include "Indice.h"

Indice::Indice(Tabla tab, string campo, bool esString) {
    _campo = campo;
    _esString = esString;
    for (auto elem: tab.registros()){
        agregarRegistro(*elem);
    }
}


string Indice::dameCampo() const {
    return _campo;
}

Indice::~Indice() {
    //TODO invocar destructores
//    if (_esString){
//        _indicesStr.~string_map();
//    } else{
//        _indicesNat.~map();
//    }
//    _campo.~string();
//    _esString.~bool();
}

void Indice::agregarRegistro(const Registro &r) {
    if (_esString){
        string valorCampo = r.dato(_campo).valorStr();
        //chequear caso no definido
        _indicesStr[valorCampo].insert(r);
    }else{
        int valorCampo = r.dato(_campo).valorNat();

        _indicesNat[valorCampo].insert(r);
    }
}

