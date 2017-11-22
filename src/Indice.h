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

/**
 *  @brief Representa un Indice de una Tabla en una Base de Datos.
 *
 *  **se explica con** TAD Diccionario(Dato, Conjunto(puntero a Registro))
 */

typedef Tabla::const_iterador_registros const_it_reg;
typedef linear_set<const_it_reg>::const_iterator const_it_regInd;

class Indice {

public:

    /**
     * @brief Inicializa un índice vacío
     *
     * \pre true
     * \post \P{this} = nuevoInd
     *
     * \complexity{\O(1)}
     */
    Indice() {}


    /**
     * @brief Inicializa un índice en la tabla y el campo pasados como parametros
     *
     * \pre campo \IN campos(tab)
     *
     * \complexity{\O(1)}
     */
    Indice(const Tabla &tab, const string &campo, bool esString);


    /**
     * @brief Destructor de índice
     *
     * \complexity{\O(S * sn)}
     */
    ~Indice() {}



    /**
     * @brief Devuelve un iterador apuntando al primer elemento del conjunto de iteradores de Registro donde esos registros tienen dato d
     *
     * \pre d \IN claves(\P{this})
     *
     * \complexity{\O(1)}
     */
    const_it_regInd dameRegistros_begin(const Dato &d) const;


    /**
     * @brief Devuelve un iterador apuntando al final del conjunto de iteradores de Registro donde esos registros tienen dato d
     *
     * \pre d \IN claves(\P{this})
     *
     * \complexity{\O(1)}
     */
    const_it_regInd dameRegistros_end(const Dato &d) const;


    /**
     * @brief Agrega el registro al indice
     *
     * \complexity{\O(S)}
     */
    void agregarRegistro(const_it_reg &r);



    /**
     * @brief Indica verdadero si el dato no tiene registros asociados
     *
     * \pre d \IN claves(\P{this})
     *
     * \complexity{\O(S)}
     */
    bool noTieneRegistros(const Dato &d) const;

private:

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /** \name Representación
     * rep: indice \TO bool\n
     * rep(d) \EQUIV
     * * _esString = true \IMPLIES
     *  *
     *  _indicesNat = \EMPTYSET \LAND
     *  *
     *  (\FORALL s : string) def?(s, _indicesStr) \IMPLIES
     *   *
     *   (\FORALL p : puntero(Registro)) p \IN obtener(s, _indicesStr) \IMPLIES
     *   _campo \IN campos(*p) \LAND valor(_campo, *p) = datoString(s)
     *
     * * _esString = false \IMPLIES
     *  *
     *  _indicesStr = \EMPTYSET \LAND
     *  *
     *  (\FORALL n : nat) def?(n, _indicesNat) \IMPLIES
     *   *
     *   (\FORALL p : puntero(Registro)) p \IN obtener(n, _indicesNat) \IMPLIES
     *   _campo \IN campos(*p) \LAND valor(_campo, *p) = datoNat(n)
     *
     *
     *
     * abs: indice \TO Dicc(Dato, Conjunto(puntero a Registro))\n
     * abs(d) \EQUIV d' \|
     *  (\FORALL dat : Dato)
     *  * def?(dat, d') \IFF
     *       Nat?(dat) \IMPLIES def?(dat, _indicesNat) \LOR String?(dat) \IMPLIES def?(dat, _indicesStr) \LAND
     *
     *  * def?(dat, d') \IMPLIES
     *       *
     *        Nat?(dat) \IMPLIES obtener(dat, d') = obtener(dat, _indicesNat) \LOR
     *       *
     *        String?(dat) \IMPLIES obtener(dat, d') = obtener(dat, _indicesStr)
     */
    //////////////////////////////////////////////////////////////////////////////////////////////////////


    /** @{ */

    /** @brief Define si el campo es string. */
    bool _esString;
    /** @brief Nombre del campo. */
    string _campo;
    /** @brief Diccionario si el campo es nat. */
    map<int, linear_set<const_it_reg> > _indicesNat;
    /** @brief Diccionario si el campo es string. */
    string_map<linear_set<const_it_reg> > _indicesStr;

    /** @} */
};


#endif // INDICE_H
