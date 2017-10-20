#include "string_map.h"
#include <utility>
#include <iostream>
#include "linear_set.h"
using namespace std;

typedef unsigned int u_int;

//construye mapa vacio
template <typename T>
string_map<T>::string_map(){
    raiz = NULL;
    cantElem = 0;
}

//destructor de mapa
template <typename T>
string_map<T>::~string_map(){
    this->cantElem = 0;
    auto it = begin();
    while (it != end()){
        it = erase(it);
    }
    delete raiz;
}

//constructor por copia
template <typename T>
string_map<T>::string_map(const string_map & other){}

//operador de asignacion
template <typename T>
string_map<T>& string_map<T>::operator=(const string_map &otro){
    this->~string_map();

    for(auto it = otro.begin(); it!=otro.end(); ++it){
        this->insert(*(it.nodo->definicion));
    }
    return *this;



}


template <typename Nodo>
bool mismosNodos(Nodo* n1 ,Nodo* n2){
    bool res = true;
    if(n1 != NULL && n2 != NULL){
        if(n1->definicion != NULL && n2->definicion != NULL){
            if(n1->definicion != n2->definicion || n1->cant_hijos != n2->cant_hijos || n1->cant_descendientes != n2->cant_descendientes ){
                return false;
            }
        }
        for(u_int i = 0; i < 256; i++){
            res = res && mismosNodos(n1->hijos[i],n2->hijos[i]);
        }
    }
    return res;
}


template <typename T>
bool string_map<T>::operator==(const string_map<T>& otro) const{
    bool iguales = (cantElem == otro.cantElem);
    iguales = iguales && mismosNodos(raiz, otro.raiz);
    return iguales;
}


//operador de comparacion
template <typename T>
bool string_map<T>::operator!=(const string_map<T>& otro) const{
    return !(*this == otro);
}

//cantidad de apariciones de la clave
template <typename T>
size_t string_map<T>::count(const key_type &key) const{
    Nodo* esta = raiz;
    for(u_int i = 0; i < key.size(); i++){
        if((esta->hijos)[int(key[i])] == NULL){
            return 0;
        }else{esta = esta->hijos[int(key[i])];}
    }
    return 1;
}

//cantidad de claves definidas
template <typename T>
size_t string_map<T>::size() const {return cantElem;}

//devuelve true si size() == 0
template <typename T>
bool string_map<T>::empty() const {return cantElem == 0;}

//acceso a la definicion, si no esta define por constructor por defecto
template <typename T>
T& string_map<T>::operator[](const key_type &key){
    Nodo* seeker = raiz;
    for(u_int i = 0; i < key.size(); i++){
        if((seeker->hijos)[i] == NULL ){
            (seeker->hijos)[int(key[i])] = new Nodo();
        }
        seeker = (seeker->hijos)[int(key[i])];
    }
    if(seeker->definicion == NULL){*(seeker->definicion) = T();}
    return *(seeker->definicion);
}

//devuelve el significado de la clave, sin modificar la clave
template <typename T>
T& string_map<T>::at(const key_type& key){
    Nodo* seeker = raiz;
    for(u_int i = 0; i < key.size(); i++){
        if((seeker->hijos)[int(key[i])] == NULL ){
            cout << "El elemento no esta" ;
        }
        seeker = (seeker->hijos)[int(key[i])];
    }
    return *(seeker->definicion);
}

//devuelve el significado de la clave, sin modificar clave ni significado
template <typename T>
const T& string_map<T>::at(const key_type& key) const{
    Nodo* seeker = raiz;
    for(u_int i = 0; i < key.size(); i++){
        if((seeker->hijos)[int(key[i])] == NULL ){
            cout << "El elemento no esta";
        }
        seeker = (seeker->hijos)[int(key[i])];
    }
    return *(seeker->definicion);
}


//limpia el mapa no lo destruye
template <typename T>
void string_map<T>::clear(){
    this->cantElem = 0;
    auto it = begin();
    while(it != this->end()){
        it = erase(it);
    }
}


//devuelve iterator al primer par en orden lexicografico
template <typename T>
typename string_map<T>::iterator string_map<T>::begin(){
    string_map<T>::iterator it(minimo());
    return it;
}
//PORQUE DEVUELVE RAIZ!!!!
//devuelve iterator al ultimo par en orden lexicografico
template <typename T>
typename string_map<T>::iterator string_map<T>::end(){
    string_map<T>::iterator it(raiz);
    return it;
}

//devuelve const_iterator al primer par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::begin()const{
    string_map<T>::const_iterator it(minimo());
    return it;
}

//devuelve const_iterator al ultimo par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::end()const{
    string_map<T>::const_iterator it = raiz;
    return it;
}

//devuelve const_iterator al primer (const)par en orden lexicografico
template <typename T>
const typename string_map<T>::const_iterator string_map<T>::cbegin()const{
    string_map<T>::const_iterator it(minimo());
    return it;
}

//devuelve const_iterator al ultimo (const)par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::cend() const{
    string_map<T>::const_iterator it(raiz);
    return it;
}

//devuelve un iterador a la clave
template <typename T>
typename string_map<T>::iterator string_map<T>::find(const key_type &key){
    Nodo* seeker = raiz;
    for(u_int i = 0; i < key.size() && seeker->cant_hijos > 1; i++){
        if((seeker->hijos)[int(key[i])] == NULL ){
            cout << "El elemento no esta";
        }
        seeker = (seeker->hijos)[int(key[i])];
    }
    string_map<T>::iterator it = seeker;
    return it;
}

//devuelve un iterador a la clave
template <typename T>
typename string_map<T>::const_iterator string_map<T>::find(const key_type &key) const{
    Nodo* seeker = raiz;
    for(u_int i = 0; i < key.size() && seeker->cant_hijos > 1; i++){
        if((seeker->hijos)[int(key[i])] == NULL ){
            cout << "El elemento no esta";
        }
        seeker = (seeker->hijos)[int(key[i])];
    }
    string_map<T>::const_iterator it = seeker;
    return it;
}



//FALTA RETORNAR EL PAR!!!!!!!!!!!
//define o redefine
template <typename T>
pair<typename string_map<T>::iterator, bool> string_map<T>::insert(const string_map::value_type& value){
    Nodo* recognizer = raiz;
    for(u_int i = 0; i < value.first.size(); i++){
        if(recognizer->hijos[int(value.first[i])] == NULL){
            recognizer->hijos[int(value.first[i])] = new Nodo();
            recognizer->hijos[int(value.first[i])]->padre = recognizer;
            recognizer->hijos[int(value.first[i])]->padre->prim = recognizer->hijos[int(value.first[i])];
        }
        recognizer->hijos[int(value.first[i])]->padre->cant_hijos++;
        recognizer->hijos[int(value.first[i])]->padre->cant_descendientes++;
        recognizer = recognizer->hijos[int(value.first[i])];
    }
    bool insertado;
    if(recognizer->definicion == NULL){cantElem++; insertado = true;}
    else{insertado = false;}
    //recognizer->definicion es de tipo dato
    *(recognizer->definicion) = value.second;
    //me dice que no tiene operador de asignacion
    string_map<T>::iterator it(recognizer);
    return make_pair(it,insertado);

}

//devuelve un bool indicando si tiene significado
template <typename T>
bool string_map<T>::reestablecerPrim(Nodo* pos){
    u_int menor;
    Nodo* aux;
    for(u_int i = 0; i<256 && aux == NULL; i++){
        menor = i;
        aux = pos->hijos[i];
    }
    pos->prim = pos->hijos[menor];
    return (pos->prim != NULL)&&(pos->prim->definicion != NULL);
}

template <typename T>
//3 casos
//es descendiente
//es su hermano mayor
//es su primo
typename string_map<T>::iterator string_map<T>::iterator::operator++(){
    //es descendiente
    while(nodo->cant_hijos > 0){
        while(nodo->prim->definicion == NULL){
            nodo = nodo->prim;
        }
        return *this;
    }
    //si llego hasta aca es porque no tiene descendientes
    string_map<T>::iterator it(nodo);
    //CUIDADO ACAA!!!
    while(/*nodo->padre != raiz &&*/ nodo->padre->cant_hijos > 1){
        it.nodo = it.nodo->padre;
    }
    //sali porque el padre es la raiz o la cantidad de hermanos es mayor a 1
    //busco a mi hermano mayor o al menor de mis "primos lejanos"
    if((it.avanzarMayor())->first > it->first){
        nodo =  it.avanzarAlMin().nodo;
        //devuelvo iterador apuntando al menor primo o mayor hermano
        return *this;
    }
    //si estoy aca es porque soy el mayor elemento
    nodo = end();
    return *this;
    //devuelvo iterator apuntando al final
}

template <typename T>
typename string_map<T>::iterator& string_map<T>::iterator::operator=(const iterator& otro){
    nodo = otro.nodo;
    return *this;
}

//DEBERIA DEVOLVER LA CANTIDAD DE ELEMENTOS ELIMINADOS (size_type)!!!
template <typename T>
typename string_map<T>::iterator string_map<T>::erase(string_map<T>::iterator pos){
    Nodo* aux = pos.nodo;
    if(empty()){cout << "Error: Diccionario vacio";}
    Nodo* viejo = aux->padre;
    if(aux->cant_hijos > 0){
        //si tiene hijos, borro su definicion y dejo que su hijos vivan
        aux->definicion = NULL;
    }else{
        //no tiene hijos, borro el nodo y me fijo que pasa con el padre
        if(viejo->cant_hijos > 1){
            //el padre tiene otros hijos nodos
            //solo borro ese nodo
            delete aux;
        }else{
            //el padre solo tiene ese nodo como hijo, borro los antesesores
            while(aux != raiz && aux->padre->cant_hijos == 0){
                viejo = aux;
                aux = aux->padre;
                delete viejo;
            }
        }
        aux->cant_hijos--;
        reestablecerPrim(aux->padre);
    }
    return ++pos;
}

template <typename T>
size_t string_map<T>::erase(const key_type &key){
    string_map<T>::iterator iter = find(key);
    erase(iter);
    return 1;
}
template <typename T>
void string_map<T>::swap(const string_map &other){
using std::swap;
swap(raiz, other.raiz);
swap(cantElem, other.cantElem);

}


template <typename T>
string_map<T>::iterator::iterator(const iterator& otro){
    nodo = otro.nodo;
}

template <typename T>
bool string_map<T>::iterator::operator==(const iterator& otro) const{
    return nodo == otro.nodo;
}

template <typename T>
bool string_map<T>::iterator::operator!=(const iterator& otro) const{
    return !(*this == otro);
}



template <typename T>
typename string_map<T>::iterator string_map<T>::iterator::herm_Mayor(){
    for(u_int i = 0; i < nodo->padre->cant_hijos; i++){
        if(nodo->padre->hijos[i] != NULL && nodo->padre->hijos[i]->definicion->first > nodo->definicion->first){
            nodo = nodo->padre->hijos[i];
            return *this;
        }
    }
    //si sale por aca es porque sigue apuntando al mismo lugar
    return *this;
}


//FALTA IMPLEMENTAR!!!!!!!!!!!
template <typename T>
typename string_map<T>::iterator string_map<T>::iterator::avanzarMayor(){

}


template <typename T>
typename string_map<T>::iterator string_map<T>::iterator::avanzarAlMin(){
    while(nodo->prim != NULL){
        nodo = nodo->prim;
    }
    return *this;
}


template <typename T>
bool string_map<T>::iterator::tieneHM(key_type& clave){
    for(u_int i = 0; i < nodo->padre->cant_hijos; i++){
        Nodo* aux  = nodo->padre->hijos[i];
        if(!(nodo->definicion->first > aux->definicion->first)){ return true;}
    }
    return false;
}


template <typename T>
typename string_map<T>::value_type& string_map<T>::iterator::operator*(){
    return *(nodo->definicion);
}

template <typename T>
typename string_map<T>::value_type* string_map<T>::iterator::operator->(){
    return nodo->definicion;
}


/*b

template <typename T>
linear_set<string> string_map<T>::claves() const{
    linear_set<string> ls;
    for (auto it = this->begin(); it!= this->end(); ++it){
        ls.fast_insert(it->first);
    }
    return ls;
}


template <typename T>
linear_set<T> string_map<T>::significados() const{
    linear_set<T> ls;
    for (auto it = this->begin(); it!= this->end(); ++it){
        ls.insert(it->second);
    }
    return ls;
} b*/

/*b
template <typename T>
string_map<T>::const_iterator::const_iterator(const const_iterator &){}

template <typename T>
typename string_map<T>::const_iterator& string_map<T>::const_iterator::operator=(const const_iterator &){

}

template <typename T>
bool string_map<T>::const_iterator::operator==(const const_iterator &) const{

}

template <typename T>
bool string_map<T>::const_iterator::operator!=(const const_iterator &) const{

}

template <typename T>
typename string_map<T>::const_iterator string_map<T>::const_iterator::operator++(){

}
template <typename T>
T& string_map<T>::const_iterator::operator*(){

}
template <typename T>
T* string_map<T>::const_iterator::operator->(){

}
b*/