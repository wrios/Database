#ifndef _BASEDEDATOS_H
#define _BASEDEDATOS_H

#include "Registro.h"
#include "Restriccion.h"
#include "Tabla.h"
#include <utility>
#include <list>
#include <string>
#include "linear_map.h"
#include "linear_set.h"
#include "utils.h"
#include "Indice.h"

using namespace std;

/**
 * @brief Una base de datos es un administrador de tablas con funciones de
 * búsqueda.
 *
 * Una base de datos permite administrar tablas identificadas por registro.
 * Permite saber si se puede agegar un registro a una tabla y luego agregarlo.
 * Permite realizar filtros del contenido de tablas mediante criterios de
 * búsqueda. Además mantiene estadísticas del uso de los criterios.
 *
 * **se explica con** TAD BaseDeDatos
 */

typedef Tabla::const_iterador_registros const_it_reg;
typedef linear_set<const_it_reg>::const_iterator const_it_regInd;

class BaseDeDatos {

public:

    class join_iterator;

    friend class join_iterator;

    /** @brief Criterio de búsqueda para una base de datos */
    typedef linear_set<Restriccion> Criterio;

    /**
     * @brief Inicializa una base de datos sin tablas.
     *
     * \pre true
     * \post \P{this} = nuevaDB
     *
     * \complexity{\O(1)}
     */
    BaseDeDatos();

    /**
     * @brief Crea una nueva tabla en la base de datos.
     *
     * @param nombre Nombre identificador de la tabla
     * @param claves Claves de la tabla a crear
     * @param campos Campos de la tabla a crear
     * @param tipos  Tipos para los campos de la tabla a crear
     *
     * \pre db = \P{this} \LAND
     *      \LNOT (nombre \IN tablas(\P{this})) \LAND
     *      \LAND \LNOT \EMPTYSET?(claves) \LAND
     *      \FORALL (c: campo) c \IN claves \IMPLICA c \IN campos \LAND
     *      long(campos) = long(tipos) \LAND sinRepetidos(campos)
     * \post \P{this} = agregarTabla(nuevaTabla(claves, nuevoRegistro(campos, tipos)), db)
     *
     * \complexity{\O(C)}
     */
    void crearTabla(const string &nombre, const linear_set<string> &claves,
                    const vector<string> &campos, const vector<Dato> &tipos);

    /**
     * @brief Agrega un registro a la tabla parámetro
     *
     * @param r Registro a agregar
     * @param nombre Nombre de la tabla donde se agrega el registro
     *
     * \pre db = \P{this} \LAND nombre \IN tablas(\P{this}) \LAND
     *      puedoInsertar?(r, dameTabla(\P{this}))
     * \post \P{this} = insertarEntrada(r, nombre, db)
     *
     * \complexity{\O(copy(Registro)) si la tabla en la que se inserta no tiene índices,
     * \O([L + log(m)]  C + copy(Registro)) sino.}
     */
    void agregarRegistro(const Registro &r, const string &nombre);

    /**
     * @brief Devuelve el conjunto de tablas existentes en la base.
     *
     * El conjunto de nombres se devuelve por referencia no-modificable.
     *
     * \pre true
     * \post \P{res} = tablas(\P{this})
     *
     * \complexity{\O(T)}
     */
    const linear_set<string> tablas() const;

    /**
     * @brief Devuelve la tabla asociada al nombre.
     *
     * La tabla se devuelve por referencia no modificable.
     *
     * @param nombre Nombre de la tabla buscada.
     *
     * \pre nombre \IN tablas(\P{this})
     * \post \P{res} = dameTabla(nombre, \P{this})
     *
     * \complexity{O(1)}
     */
    const Tabla &dameTabla(const string &nombre) const;

    /**
     * @brief Devuelve la cantidad de usos que tiene un criterio
     *
     * @param criterio Criterio por el cual se consulta.
     *
     * \pre nombre \IN tablas(\P{this})
     * \post \P{res} = usoCriterio(criterio, \P{this})
     *
     * \complexity{\O(#cs * cmp(Criterio))}
     */
    int uso_criterio(const Criterio &criterio) const;

    /**
     * @brief Evalúa si un registro puede ingresarse en la tabla parámetro.
     *
     * @param r Registro a ingresar en la tabla.
     * @param nombre Nombre de la tabla.
     *
     * \pre nombre \IN tablas(\P{this})
     * \post \P{res} = puedoInsertar?(r, dameTabla(nombre, \P{this}))
     *
     * \complexity{\O(C + (c * n * L))}
     */
    bool registroValido(const Registro &r, const string &nombre) const;

    /**
     * @brief Evalúa si un criterio puede aplicarse en la tabla parámetro.
     *
     * @param c Criterio a utilizar.
     * @param nombre Nombre de la tabla.
     *
     * \pre tabla \IN tablas(\P{this})
     * \post \P{res} = criterioValido(c, nombre, \P{this})
     *
     * \complexity{\O(cr)}
     */
    bool criterioValido(const Criterio &c, const string &nombre) const;

    /**
     * @brief Devuelve el resultado de buscar en una tabla con un criterio.
     *
     * @param c Criterio de búsqueda utilizado.
     * @param nombre Nombre de la tabla.
     *
     * \pre nombre \IN tablas(\P{this}) \LAND criterioValido(c, nombre, \P{this})
     * \post \P{res} = buscar(c, nombre, \P{this})
     *
     * \complexity{\O(T + cs * cmp(Criterio) + cr * n * (C + L + copy(reg)))}
     */
    Tabla busqueda(const Criterio &c, const string &nombre);

    /**
     * @brief Devuelve los criterios de máximo uso.
     *
     * \pre true
     * \post \FORALL (c : Criterio) [c \IN \P{res} \IFF
     *       \FORALL (c' : Criterio) usoCriterio(c, db) >= usoCriterio(c', db)]
     *
     * \complexity{\O(cs * copy(Criterio))}
     */
    linear_set<Criterio> top_criterios() const;

    /**
   * @brief Crea un índice en el campo de la tabla pasados como parámetros.
   *
   * @param nombre Nombre de la tabla donde quiero crear el índice.
   * @param campo Campo de la tabla donde quiero crear el índice.
   *
   * \pre tabla \IN tablas(\P{this}) \LAND campo \IN campos(tabla)
   * \post
   *
   * \complexity{\O(m * [L + log(m)])}
   */
    void crearIndice(const string &nombre, const string &campo);

    /**
   * @brief Devuelve el índice de la tabla en el campo pasados como parámetros.
   *
   * @param nombre Nombre de la tabla de donde quiero obtener el índice.
   * @param campo Campo de la tabla de donde quiero obtener el índice.
   *
   * \pre tabla \IN tablas(\P{this}) \LAND campo \IN campos(tabla) \LAND tieneIndice?(tabla, campo, \P{this})
   * \post
   *
   * \complexity{\O(1)}
   */
    const Indice *dameIndice(const string &tabla, const string &campo) const;

    /**
   * @brief Join entre dos tablas de la base de datos por un campo.
   *
   * \pre tabla1 \IN tablas(\P{this}) \LAND tabla2 \IN tablas(\P{this}) \LAND campo \IN campos(tabla1)
   * \LAND \LAND campo \IN campos(tabla2) \LAND (tieneIndice?(tabla1, campo, \P{this}) \LOR tieneIndice?(tabla2, campo, \P{this}))
   * \post
   *
   * \complexity{\O(n * [L + log(m)])}
   */
    join_iterator join(const string &tabla1, const string &tabla2, const string &campo) const;

    /**
   * @brief Iterador al final del conjunto resultante de hacer el Join.
   *
   * \pre true
   * \post
   *
   * \complexity{\O(1)}
   */
    join_iterator join_end() const;

private:
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /** \name Representación
     * rep: basededatos \TO bool\n
     * rep(bd) \EQUIV 
     *  * claves(_indices) = claves(_nombresYtablas) \LAND
     *  * \FORALL (c : Criterio) c \IN claves(_criteriosYusos) \IMPLIES
     *     * (
     *       * \EXISTS (n : string) n \IN _nombresYtablas
     *       * \LAND criterioValido(c, n, db)
     *     * ) \LAND
     *     * obtener(c, _criteriosYusos) > 0
     *  *\FORALL (t : string) def?(t, _indices) \IMPLIES
     *    * (
     *      * \FORALL (c : Campo) def?(c, obtener(t, _indices)) \IMPLIES
     *        * (c \IN campos(t) ) )
     *
     * abs: basededatos \TO BaseDeDatos\n
     * abs(bd) \EQUIV bd' \|
     *  * tablas(bd') = significados(_nombresYtablas)\LAND
     *  * (\FORALL t : string) def?(t, _nombresYtablas) \IMPLIES
     *    * obtener(t, _nombresYtablas) = dameTabla(nt, bd') \LAND
     *  * (\FORALL c : criterio) 
     *    * (usoCriterio(c, bd') == 0 \LAND \LNOT def?(c, _criteriosYusos)) \LOR
     *    * (usoCriterio(c, db') == obtener(c, _criteriosYusos))
     *  * \FORALL (t : string) def?(t, _indices) \IMPLIES
     *    * (
     *      *\FORALL (c : Campo) def?(c, obtener(t, _indices)) \IMPLIES
     *        * (
     *          * \LNOT esVacio?(obtener(c, obtener(t, _indices))) =
     *          * tieneIndice?(t, c, bd') ) )
     */
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    /** @{ */

    /** @brief Diccionario con los nombres y las tablas de la base de datos. */
    string_map<Tabla> _nombresYtablas;

    /** @brief Diccionario con los criterios de búsqueda y sus cantidades de usos. */
    linear_map<Criterio, int> _criteriosYusos;

    /** @brief Diccionario con las tablas y los campos donde tienen índice. */
    string_map<string_map<Indice> > _indices;
    /** @} */

    /** @{ */
    /**
     * @brief Revisa si los campos del registro y la tabla tienen el mismo tipo.
     *
     * \pre campos(r) == campos(t)
     * \post \P{res} == \FORALL (c : campo) c \IN campos(r) \IMPLIES
     * Nat?(valor(c, r)) == tipoCampo(c, t)
     *
     * \complexity{O(C^2)}
     */
    bool _mismos_tipos(const Registro &r, const Tabla &t) const;

    /**
     * @brief Revisa si el registro no repite claves en la tabla.
     *
     * \pre compatible(r, t)
     * \post \P{res} = \FORALL (r' : Registro) r \IN registros(t) \IMPLIES
     *  \EXISTS (c : campo) c \IN claves(t) \LAND valor(c, r') != valor(c, r)
     *
     * \complexity{O(c * C + c * n * (C + L))}
     */
    bool _no_repite(const Registro &r, const Tabla &t) const;

    /**
     * @brief Filtra la lista de registros parametro según el criterio.
     *
     * El resultado tiene aliasing con el parámetro registros.
     *
     * \pre \FORALL (r : Registro) r \IN registros \IMPLIES campo \IN
     *      campos(r) \LAND tipo?(valor(campo, r)) = tipo?(valor)
     * \post \P{res} = filtrarRegistrosSegunRestriccion(
     *       nueva(campo, valor, igualdad), registros)
     */
    list<Registro> &_filtrar_registros(const string &campo, const Dato &valor,
                                       list<Registro> &registros,
                                       bool igualdad) const;

    /**
     * @brief Filtra la lista de registros parametro según el criterio.
     *
     * El resultado tiene aliasing con el parámetro registros.
     *
     * \pre \FORALL (r : Registro) r \IN registros \IMPLIES campo \IN
     *      campos(r) \LAND tipo?(valor(campo, r)) = tipo?(valor)
     * \post \P{res} = filtrarRegistrosSegunRestriccion(
     *       nueva(campo, valor, true), registros)
     */
    list<Registro> &_filtrar_registros(const string &campo, const Dato &valor,
                                       list<Registro> &registros) const;

    /**
     * @brief Obtiene los campos y tipos de una tabla.
     *
     * \pre true
     * \post (\FORALL (c : Campo) está?(c, \P1(\P{res})) \IFF c \IN campos(t))
     *       \LAND #(campos(t)) = long(\P1(\P{res}))
     *       \LAND \FORALL (i : Nat) 0 \LEQ i < #(campos(t)) \IMPLIES
     *       tipo?(\P2(\P{res})[i]) = tipoCampo(\P1(\P{res})[i], t)
     */
    pair<vector<string>, vector<Dato> > _tipos_tabla(const Tabla &t);
    /** @} */



public:

    /** @brief Iterador Constante de los registros resultantes de hacer Join entre dos tablas.
     *  **se explica con** TAD Iterador Unidireccional(Registro)
     *
     * El join_iterator permite recorrer los registros pertenecientes al conjunto de registros que se
     * obtiene haciendo Join entre dos tablas por un campo. Para éso va a pasar una única vez por cada registro de
     * la tabla resultante. El resultado se mantiene constante, es decir, no se permite modificar
     * los elementos de la estructura.
     *  */
    class join_iterator {
    public:

        /**
         * @brief Constructor por parametros del iterador.
         *
         * \complexity{\O(1)}
         */
        join_iterator(const BaseDeDatos &bd,
                      const string &tablaSinIndice,
                      const string &tablaConIndice,
                      const string &campoIndice,
                      bool tabla1TieneI,
                      const_it_reg &endT,
                      const_it_regInd &endI
        );

        /**
         * @brief Constructor por parametros del iterador.
         *
         * \complexity{\O(1)}
         */
        join_iterator(const_it_reg &endT,
                      const_it_regInd &endI,
                      bool t);

        /**
         * @brief Constructor por copia del iterador.
         *
         * \complexity{\O(1)}
         */
        join_iterator(const BaseDeDatos::join_iterator &otro);

        /**
         * @brief Comparación entre iteradores
         *
         * \pre ambos iteradores refieren a la misma colección
         * \post true sii los iteradores apuntan al mismo elemento
         *
         * \complexity{\O(1)}
         */
        bool operator==(const join_iterator &otro) const;

        /**
         * @brief Comparación entre iteradores
         *
         * \pre ambos iteradores refieren a la misma colección
         * \post true sii los iteradores no apuntan al mismo elemento
         *
         * \complexity{\O(1)}
         */
        bool operator!=(const join_iterator &otro) const;

        /**
         * @brief Avanza el iterador del join pasado como parametro y lo devuelve.
         * Si estaba en el último registro del join devuelve join_end().
         * Sino, al avanzar el join va a avanzar primero el iterador de la tabla indexada recorriendo el conjunto de
         * los registros y una vez que no queden mas registros por recorrer en ese conjunto busca los proximos
         * registros que sean parte del join desde la posicion actual.
         *
         * \pre El iterador no debe estar en la posición pasando-el-último.
         * \post \P{res} es una referencia a \P{this}. \P{this} apunta a la posición
         * siguiente.
         *
         * \complexity{\O(n * [L + log(m)])}
         */
        join_iterator operator++();


        /**
         * @brief Primero devuelve el iterador y luego lo avanza.
         *
         * \pre El iterador no debe estar en la posición pasando-el-último.
         * \post \P{res} es una referencia a \P{this}. \P{this} apunta a la posición
         * siguiente.
         *
         * \complexity{\O(n * [L + log(m)])}
         */
        join_iterator operator++(int a);

        /**
        * @brief Desreferencia el join combinando los registros actuales
        * (o sea los registros de los iteradores internos del join) de la tabla indexada y de la tabla no indexada.
        *
        * El valor devuelto tiene aliasing dentro de la colección.
        *
        * \pre El iterador no debe estar en la posición pasando-el-último.
        * \post El valor resultado es una referencia constante al valor apuntado.
        *
        * \complexity{\O(copy(Registro))}
        */
        Registro operator*();


        /**
        * @brief Setea el begin y end de los iteradores de indice en el join con un dato como parametro
        *
        * \complexity{\O(1)}
        */
        void setearItIndices(const Dato &d);

    private:


        /** @{ */
        /** @brief Indica si la tabla1 pasada como parametro en el join tiene indice. */
        bool tabla1TieneIndice;

        /** @brief Indica si el join terminó. */
        bool finaliza;

        /** @brief Iterador a la posición actual del conjunto de los registros de la tabla sin índice. */
        const_it_reg itTabla;

        /** @brief Iterador a la posición actual del conjunto de los registros de la tabla con índice. */
        const_it_regInd itIndice;

        /** @brief Iterador al final del conjunto de los registros de la tabla sin índice. */
        const_it_reg endTabla;

        /** @brief Iterador al final del conjunto de los registros de la tabla con índice. */
        const_it_regInd endIndice;

        /** @brief Campo donde se va a producir el Join. */
        string campo;

        /** @brief Puntero al índice de la tabla con índice. */
        const Indice *indice;
        /** @} */
    };

};

#endif
