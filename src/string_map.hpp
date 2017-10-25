#include "string_map.h"
#include <utility>
#include <iostream>
#include "linear_set.h"
using namespace std;

typedef unsigned int u_int;



//construye mapa vacio
template <typename T>
string_map<T>::string_map(){
    raiz = new Nodo();
    cantElem = 0;
}

//destructor de mapa
template <typename T>
string_map<T>::~string_map(){
    clear();
    delete raiz;
}

//constructor por copia
template <typename T>
string_map<T>::string_map(const string_map & other){

}

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
    bool res = false;
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
    if(esta->definicion != NULL){ return 1;}
    return 0;
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
    if(seeker->definicion == NULL){
//        seeker->definicion = new
        seeker->definicion->second = T();
    }
    return seeker->definicion->second;
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
    return (seeker->definicion->second);
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
    return (seeker->definicion->second);
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
    string_map<T>::iterator it(seeker);
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

//define o redefine
template <typename T>
pair<typename string_map<T>::iterator, bool> string_map<T>::insert(const string_map::value_type& value){
    Nodo* recognizer = raiz;
    bool insertado = false;
    for(u_int i = 0; i < value.first.size(); i++){

        if(recognizer->hijos[int(value.first[i])] == NULL){

            recognizer->hijos[int(value.first[i])] = new Nodo();
            recognizer->hijos[int(value.first[i])]->padre = recognizer;
            recognizer->cant_hijos++;

//            if(recognizer->cant_hijos == 1){
//                recognizer->prim = recognizer->hijos[int(value.first[i])];
//            } else{
//                reestablecerPrim(recognizer);
//            }
        }
        //HACIENDO DEBBUG ACA NUNCA ENTRO!!!!
        if (i == value.first.size() - 1 && recognizer->hijos[int(value.first[i])]->definicion == NULL ){
            insertado = true;
        }

        recognizer = recognizer->hijos[int(value.first[i])];
    }//recognizer es un puntero donde voy a insertar el significado o a redefinir el significado

    if (insertado){
        cantElem++;
    }

    if (recognizer->definicion != nullptr)
        delete recognizer->definicion;
    recognizer->definicion = new value_type(value);
//    recognizer->definicion->second = value.second; //SE ROMPE PORQUE DATO NO TIENE OPERATOR=
    string_map<T>::iterator it(recognizer);
    return make_pair(it,insertado);
}



template <typename T>
//3 casos
//es descendiente
//es su hermano mayor
//es su primo
typename string_map<T>::iterator string_map<T>::iterator::operator++(){
    //es descendiente
    while(nodo->cant_hijos > 0){
        while(minimo(nodo)->definicion == NULL){
            nodo = minimo(nodo);
        }
        return *this;
    }
    //si llego hasta aca es porque no tiene descendientes
    string_map<T>::iterator it(nodo);
    //CUIDADO ACAA!!!
    while(nodo->padre != nodo && nodo->padre->cant_hijos > 1){
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
    while(nodo->padre != NULL){ nodo = nodo->padre;}
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
typename string_map<T>::iterator string_map<T>::iterator::avanzarMayor(){
    for(u_int i = 0; i < nodo->padre->cant_hijos; i++){
        if(nodo->padre->hijos[i] != NULL && nodo->padre->hijos[i]->definicion->first > nodo->definicion->first){
            nodo = nodo->padre->hijos[i];
            return *this;
        }
    }
    //si sale por aca es porque sigue apuntando al mismo lugar
    return *this;
}


template <typename T>
typename string_map<T>::iterator string_map<T>::iterator::avanzarAlMin(){
    nodo = minimo(nodo);
    return *this;
}




template <typename T>
typename string_map<T>::value_type& string_map<T>::iterator::operator*(){
    return *(nodo->definicion);
}

template <typename T>
typename string_map<T>::value_type* string_map<T>::iterator::operator->(){
    return nodo->definicion;
}


template <typename T>
linear_set<string> string_map<T>::claves() const{
    linear_set<string> ls;
    for (auto it = this->begin(); it!= this->end(); ++it){
        ls.insert(it.nodo->definicion->first);
    }
    return ls;
}


template <typename T>
linear_set<T> string_map<T>::significados() const{
    linear_set<T> ls;
    for (auto it = this->begin(); it!= this->end(); ++it){
        ls.insert(it.nodo->definicion->second);
    }
    return ls;
}

//FALTA IMPLEMENTAR!!!!!!!!!!!
template <typename T>
typename string_map<T>::const_iterator string_map<T>::const_iterator::avanzarMayor(){

}


template <typename T>
typename string_map<T>::const_iterator string_map<T>::const_iterator::avanzarAlMin(){
    while(nodo->prim != NULL){
        nodo = nodo->prim;
    }
    return *this;
}

template <typename T>
string_map<T>::const_iterator::const_iterator(const const_iterator& otro){
    nodo = otro.nodo;
}

template <typename T>
typename string_map<T>::const_iterator& string_map<T>::const_iterator::operator=(const const_iterator& otro){
    nodo = otro.nodo;
    return *this;
}

template <typename T>
bool string_map<T>::const_iterator::operator==(const const_iterator& otro) const{
    return nodo == otro.nodo;
}

template <typename T>
bool string_map<T>::const_iterator::operator!=(const const_iterator& otro) const{
    return !(*this == otro);
}

template <typename T>
typename string_map<T>::const_iterator string_map<T>::const_iterator::operator++(){
    //es descendiente
    while(nodo->cant_hijos > 0){
        while(minimo(nodo)->definicion == NULL){
            nodo = minimo(nodo);
        }
        return *this;
    }
    //si llego hasta aca es porque no tiene descendientes
    string_map<T>::const_iterator it(nodo);
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
    while(nodo->padre != NULL){ nodo = nodo->padre;}
    return *this;
    //devuelvo iterator apuntando al final
}

template <typename T>
typename string_map<T>::value_type& string_map<T>::const_iterator::operator*(){
    return *(nodo->definicion);
}
template <typename T>
typename string_map<T>::value_type* string_map<T>::const_iterator::operator->(){
    return nodo->definicion;
}
