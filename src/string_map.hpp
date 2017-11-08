#include "string_map.h"
#include <utility>
#include <iostream>
#include "linear_set.h"
using namespace std;

typedef unsigned int u_int;

template <typename T>
string_map<T>::string_map(){
    raiz = new Nodo();
    raiz->padre = raiz;
    cantElem = 0;
}

template <typename T>
string_map<T>::~string_map(){
    eliminarRec(raiz);
    delete  raiz;
    raiz = NULL;
    cantElem = 0;
}

template <typename T>
string_map<T>::string_map(const string_map & other){
    raiz = new Nodo();
    raiz->padre = raiz;
    cantElem = 0;
    if(!other.empty()){
        for(auto it = other.begin(); it != other.end(); ++it){
            this->insert(*(it.nodo->definicion));
        }
    }
}

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map &other){
    if(!empty()){
        clear();
        if(raiz->definicion != NULL){
            delete raiz->definicion;
            raiz->definicion = NULL;
        }
        cantElem = 0;
    }
    if(!other.empty()){
        for(auto it = other.begin(); it != other.end(); ++it){
            insert(*(it.nodo->definicion));
        }
    }
    return *this;
}



template <typename T>
bool string_map<T>::operator==(const string_map<T>& other) const{
    if(cantElem == other.cantElem){
        typename string_map<T>::const_iterator it1 = begin();
        typename string_map<T>::const_iterator it2 = other.begin();
        while(it1 != end()){
            if(*it1 != *it2){
                return false;
            }
            ++it1;
            ++it2;
        }
        return true;
    }else{
        return false;
    }
}


//operador de comparacion
template <typename T>
bool string_map<T>::operator!=(const string_map<T>& otro) const{
    return !(*this == otro);
}

//cantidad de apariciones de la clave
template <typename T>
size_t string_map<T>::count(const key_type &key) const{
    typename string_map<T>::const_iterator it = find(key);
    if(it == end()){
        return 0;
    }
    return 1;
}

//cantidad de claves definidas
template <typename T>
size_t string_map<T>::size() const {return cantElem;}

//devuelve true si size() == 0
template <typename T>
bool string_map<T>::empty() const {return cantElem == 0;}

template <typename T>
T& string_map<T>::operator[](const key_type &key){
    string_map<T>::iterator it = find(key);
    if(it == end()){
        string_map<T>::mapped_type t = T();
        string_map<T>::value_type tup = make_pair(key,t);
        it = insert(tup).first;
    }
    return it->second;
}

template <typename T>
T& string_map<T>::at(const key_type& key){
    string_map<T>::iterator it = find(key);
    return it->second;
}

//devuelve el significado de la clave, sin modificar clave ni significado
template <typename T>
const T& string_map<T>::at(const key_type& key) const{
    string_map<T>::const_iterator it = find(key);
    return it->second;
}


//limpia el mapa no lo destruye
template <typename T>
void string_map<T>::clear(){
    if(!empty()){
        eliminarRec(raiz);
        if(raiz->definicion != NULL){
            delete raiz->definicion;
            raiz->definicion = NULL;
        }
    }
    cantElem = 0;
}


//devuelve iterator al primer par en orden lexicografico
template <typename T>
typename string_map<T>::iterator string_map<T>::begin(){
    string_map<T>::iterator it(NULL);
    if(!empty()){
        it.nodo = raiz->minimo();
    }
    return it;
}

//devuelve iterator al ultimo par en orden lexicografico
template <typename T>
typename string_map<T>::iterator string_map<T>::end(){
    string_map<T>::iterator it(NULL);
    return it;
}

//devuelve const_iterator al primer par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::begin()const{
    string_map<T>::const_iterator it(NULL);
    if(!empty()){
        it.nodo = raiz->minimo();
    }
    return it;
}

//devuelve const_iterator al ultimo par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::end()const{
    string_map<T>::const_iterator it(NULL);
    return it;
}

//devuelve const_iterator al primer (const)par en orden lexicografico
template <typename T>
const typename string_map<T>::const_iterator string_map<T>::cbegin()const{
    string_map<T>::const_iterator it(NULL);
    if(!empty()){
        it.nodo = raiz->minimo();
    }
    return it;
}

//devuelve const_iterator al ultimo (const)par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::cend() const{
    string_map<T>::const_iterator it(NULL);
    return it;
}

//devuelve un iterador a la clave
template <typename T>
typename string_map<T>::iterator string_map<T>::find(const key_type &key){
    Nodo* seeker = raiz;
    for(u_int i = 0; i < key.size(); i++){
        if((seeker->hijos)[int(key[i])] == NULL ){
            return end();
        }
        seeker = (seeker->hijos)[int(key[i])];
    }
    string_map<T>::iterator it(seeker);
    if(seeker->definicion == NULL){
        return end();
    }
    return it;
}

//devuelve un iterador a la clave
template <typename T>
typename string_map<T>::const_iterator string_map<T>::find(const key_type &key) const{
    Nodo* seeker = raiz;
    for(u_int i = 0; i < key.size(); i++){
        if((seeker->hijos)[int(key[i])] == NULL ){
            return end();
        }
        seeker = (seeker->hijos)[int(key[i])];
    }
    string_map<T>::const_iterator it(seeker);
    if(seeker->definicion == NULL){
        return end();
    }
    return it;
}

//define o redefine
template <typename T>
pair<typename string_map<T>::iterator, bool> string_map<T>::insert(const string_map::value_type& value){
    Nodo* parent = raiz;
    Nodo* son = raiz;
    bool insertado = false;
    string_map<T>::iterator itr(raiz);
    if(value.first.length() == 0){
        if(raiz->definicion == NULL){cantElem++; insertado = true;}
        else{delete son->definicion;}
        raiz->definicion = new value_type(value);
        return make_pair(itr,insertado);
    }
    for(u_int i = 0; i < value.first.size(); i++){
        int o = int(value.first[i]);
        son = (parent->hijos)[o];
        if(son != NULL && i == value.first.size()-1 && son->definicion == NULL){
            insertado = true;
            cantElem++;
            son->restaBlecerCantHijos(true);
        }
        if(son == NULL){
            son = new Nodo();
            (parent->hijos)[int(value.first[i])] = son;
            son->padre = parent;
            if (i == value.first.size() - 1){
                insertado = true;
                cantElem++;
                son->restaBlecerCantHijos(true);
            }
        }
        parent = son;
    }//recognizer es un puntero donde voy a insertar el significado o a redefinir el significado
    if(son->definicion != NULL){delete son->definicion;}
    son->definicion = new value_type(value);
    string_map<T>::iterator it(son);
    return make_pair(it,insertado);
}


template <typename T>
typename string_map<T>::iterator string_map<T>::iterator::operator++(){
    Nodo* aux = nodo;
    if(aux->cant_hijos > 0){
        nodo = aux->minimo();
        return *this;
    }
    aux = aux->dameMayor();
    if(aux != nodo){
        nodo = aux;
    }else{
        nodo = NULL;
    }
    return *this;
}

template <typename T>
typename string_map<T>::iterator& string_map<T>::iterator::operator=(const iterator& otro){
    nodo = otro.nodo;
    return *this;
}

template <typename T>
typename string_map<T>::iterator string_map<T>::erase(string_map<T>::iterator pos){
    Nodo* aux = pos.nodo;
    Nodo* temp = aux->padre;
    typename string_map<T>::key_type key = pos.nodo->definicion->first;
    typename string_map<T>::iterator res = ++pos;
    int tam = key.size()-1;
    if (aux->cant_hijos > 0){
        delete aux->definicion;
        aux->definicion = NULL;
        aux->restaBlecerCantHijos(false);
        cantElem--;
        return res;
    }else{
        if(aux->padre == aux){
            std::cout << " "" " << std::endl;
            eliminarRec(aux);
            //delete aux;
            cantElem--;
            return res;
        }else{
            restablecerCadena(aux, key, tam);
            cantElem--;
            return res;
        }
    }
}

template <typename T>
size_t string_map<T>::erase(const key_type &key){
    string_map<T>::iterator iter = find(key);
    if(iter != end()){
        erase(iter);
        return 1;
    }
    return 0;
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
    Nodo* aux = nodo;
    if(aux->cant_hijos > 0){
        nodo = aux->minimo();
        return *this;
    }
    aux = aux->dameMayor();
    if(aux != nodo){
        nodo = aux;
    }else{
        nodo = NULL;
    }
    return *this;
}

template <typename T>
typename string_map<T>::value_type& string_map<T>::const_iterator::operator*(){
    return *(nodo->definicion);
}
template <typename T>
typename string_map<T>::value_type* string_map<T>::const_iterator::operator->(){
    return nodo->definicion;
}

//funciones de Nodo

template <typename T>
typename string_map<T>::Nodo* string_map<T>::Nodo::minimo(){
    Nodo* aux = this;
    for (u_int i = 0; i < 256; ++i) {
        if (aux->hijos[i] != NULL) {
            aux = aux->hijos[i];
            if (aux->definicion != NULL) {
                return aux;
            }
            i =0;
        }
    }
}

template <typename T>
typename string_map<T>::Nodo* string_map<T>::Nodo::dameMayor(){
    typename string_map<T>::key_type key = definicion->first;
    int i = key.size()-1;
    typename string_map<T>::Nodo* temp = this;
    typename string_map<T>::Nodo* salida;
    while(temp->padre != temp){
        salida = temp->hermanoMayor(int(key[i]));
        if(salida != temp){
            return salida;
        }
        temp = temp->padre;
        i--;
    }
    return this;
}

template <typename T>
typename string_map<T>::Nodo* string_map<T>::Nodo::hermanoMayor(int key_i) {
    int i = key_i + 1;
    while(i < 256){
        Nodo* temp = padre->hijos[i];
        if(padre->hijos[i] != NULL){
            if(padre->hijos[i]->definicion != NULL){
                return padre->hijos[i];
            }else{
                temp = padre->hijos[i]->minimo();
                return temp;
            }
        }
        i++;
    }
    return this;
}

template <typename T>
void string_map<T>::Nodo::restaBlecerCantHijos(bool sr){
    string_map<T>::Nodo* temp = this;
    while(temp != temp->padre){
        if(sr){
            temp->padre->cant_hijos++;
        }else{
            temp->padre->cant_hijos--;
        }
        temp = temp->padre;
    }
}

template <typename T>
void string_map<T>::eliminarRec(string_map<T>::Nodo* n){
    for(int i = 0; i < 256; i++){
        if(n->hijos[i] != NULL){
            eliminarRec(n->hijos[i]);
            delete n->hijos[i];
            n->hijos[i] = NULL;
        }
    }
    if(n->definicion != NULL){
        delete n->definicion;
        n->definicion = NULL;
    }
}

template <typename T>
void string_map<T>::restablecerCadena(typename string_map<T>::Nodo* n, string_map<T>::key_type key, int posicion){
    //entro sabiendo que n no tiene hijos y no soy raiz
    typename string_map<T>::Nodo* aux = n->padre;
    delete n->definicion;
    n->definicion = NULL;
    bool borrar = true;
    while(n->padre != n){
        if(aux->cant_hijos == 1){
            delete aux->hijos[int(key[posicion])];
            aux->hijos[int(key[posicion])] = NULL;
            borrar = true;
        }else if(aux->cant_hijos > 1 && borrar){
            delete aux->hijos[int(key[posicion])];
            aux->hijos[int(key[posicion])] = NULL;
            borrar = false;
        }else{
            aux->cant_hijos --;
            borrar = false;
        }
        n = aux;
        aux = n->padre;
        posicion--;
    }
}
