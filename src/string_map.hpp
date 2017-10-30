#include "string_map.h"
#include <utility>
#include <iostream>
#include "linear_set.h"
using namespace std;
//funciones de Nodo


typedef unsigned int u_int;

template <typename T>
string_map<T>::string_map(){
    raiz = new Nodo();
    raiz->padre = raiz;
    cantElem = 0;
}

//destructor de mapa
template <typename T>
string_map<T>::~string_map(){
  //clear();
    //delete raiz;
}

//constructor por copia
template <typename T>
string_map<T>::string_map(const string_map & other){
  if(false){
    clear();
  }
  if(false){
    for(auto it = other.begin(); it != other.end(); ++it){
      this->insert(*(it.nodo->definicion));
    }
  }
  raiz = other.raiz;
  cantElem = other.cantElem;
}

//operador de asignacion
template <typename T>
string_map<T>& string_map<T>::operator=(const string_map &other){
  if(false){
    clear();
  }
  if(!other.empty()){
    for(auto it = other.begin(); it != other.end(); ++it){
      insert(*(it.nodo->definicion));
    }
  }
  raiz = other.raiz;
  cantElem = other.cantElem;
  return *this;
}



template <typename T>
bool string_map<T>::operator==(const string_map<T>& other) const{
  if(empty() && other.empty()){
    return true;
  }else if(!empty() && !other.empty() && cantElem == other.cantElem){
    return raiz->mismosNodos(other.raiz);
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
    Nodo* esta = raiz;
    for(u_int i = 0; i < key.size(); i++){
        if((esta->hijos)[int(key[i])] == NULL){
            return 0;
        }else
          {
            esta = esta->hijos[int(key[i])];
          }
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
  string_map<T>::iterator it = find(key);
  if(it == end()){
    string_map<T>::mapped_type t = T();
    string_map<T>::value_type tup = make_pair(key,t);
    it = insert(tup).first;
    return it->second;
  }else{
    return it->second;
  }/*
  Nodo* seeker = raiz;
    for(u_int i = 0; i < key.size(); i++){
      if((seeker->hijos)[int(key[i])] == NULL ){
            (seeker->hijos)[int(key[i])] = new Nodo();
            (seeker->hijos)[int(key[i])]->padre = seeker;
        }
        seeker = (seeker->hijos)[int(key[i])];
    }
    if(seeker->definicion == NULL){
      seeker->definicion = &tup;
      cantElem++;
      seeker->sumar1padres();
    }
    return (seeker->definicion->second);*/
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
    if(!empty()){
      raiz->eliminarNodosHijos();
    }
    cantElem = 0;
}


//devuelve iterator al primer par en orden lexicografico
template <typename T>
typename string_map<T>::iterator string_map<T>::begin(){
  string_map<T>::iterator it(raiz);
  if(!empty()){
    it.it_avanzarAlMin();
  }
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
  string_map<T>::const_iterator it(raiz);
  if(!empty()){
    it.it_avanzarAlMin();
  }
    return it;
}

//devuelve const_iterator al ultimo par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::end()const{
  string_map<T>::const_iterator it(raiz);
    return it;
}

//devuelve const_iterator al primer (const)par en orden lexicografico
template <typename T>
const typename string_map<T>::const_iterator string_map<T>::cbegin()const{
  string_map<T>::const_iterator it(raiz);
  if(!empty()){
    it.it_avanzarAlMin();
  }
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
    for(u_int i = 0; i < key.size(); i++){
        if((seeker->hijos)[int(key[i])] == NULL ){
          return end();
            cout << "El elemento no esta";
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
            cout << "El elemento no esta";
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
    for(u_int i = 0; i < value.first.size(); i++){
        int o = int(value.first[i]);
        son = (parent->hijos)[o];
        if(son != NULL && i == value.first.size()-1 && son->definicion == NULL){
          insertado = true;
          cantElem++;
          son->sumar1padres();
        }
        if(son == NULL){
            son = new Nodo();
            (parent->hijos)[int(value.first[i])] = son;
            son->padre = parent;
            if (i == value.first.size() - 1 && son->definicion == NULL ){
                insertado = true;
                cantElem++;
                son->sumar1padres();
            }
        }
        parent = son;
    }//recognizer es un puntero donde voy a insertar el significado o a redefinir el significado
    delete son->definicion;
    son->definicion = new value_type(value);
    string_map<T>::iterator it(son);
    return make_pair(it,insertado);
}


//funciones de iterator
template <typename T>
void string_map<T>::iterator::it_avanzarAlMin(){
  std::cout << "llamada al it_minimo" << std::endl;
  Nodo* aux = nodo;
  if(aux == NULL) throw runtime_error("minimo de un null");
  for (u_int i = 0; i < 256; ++i) {
    if (aux->hijos[i] != NULL) {
      aux = aux->hijos[i];
      if (aux->definicion != NULL) {
        std::cout << "saliendo del it_minimo "<< i << std::endl;
        nodo = aux;
        return;
      }else{
        i = 0;
      }
    }
  }
  if(true) throw runtime_error("no tiene minimo");
}

template <typename T>
void string_map<T>::const_iterator::it_avanzarAlMin(){
  Nodo* aux = nodo;
  if(aux == NULL) throw runtime_error("minimo de un null");
  for (u_int i = 0; i < 256; ++i) {
    if (aux->hijos[i] != NULL) {
      aux = aux->hijos[i];
      if (aux->definicion != NULL) {
        std::cout << "saliendo del it_minimo"<< i << std::endl;
        nodo = aux;
        return;
      }else{
        i = 0;
      }
    }
  }
  if(true) throw runtime_error("no tiene minimo");
}

template <typename T>
//3 casos
//es descendiente
//es su hermano mayor
//es su primo
typename string_map<T>::iterator string_map<T>::iterator::operator++(){
    //es descendiente
  Nodo* aux = nodo;
  string_map<T>::iterator it(aux);
    if(aux->cant_hijos > 0){
        std::cout << "llamada al minimo en operator++()"<< std::endl;
        it.it_avanzarAlMin();
        return it;
    }
    //si llego hasta aca es porque no tiene descendientes
    //CUIDADO ACAA!!!
    while(aux->padre != aux && !aux->tieneHM()){
        std::cout << "buscando al padre en operator++()"<< std::endl;
        aux = aux->padre;
    }
    //sali porque el padre es la raiz o la cantidad de hermanos es mayor a 1
    //busco a mi hermano mayor o al menor de mis "primos lejanos"
    if(aux->tieneHM()){
        std::cout << "avanza al mayor en operator++()"<< std::endl;
        it.nodo =  it.nodo->hermanoMayor();
        //devuelvo iterador apuntando al menor primo o mayor hermano
        return it;
    }
    //si estoy aca es porque soy el mayor elemento
    while(aux->padre != aux){ aux = aux->padre;}
    std::cout << "devuelve iterador a la raiz en operator++()"<< std::endl;
    return it;
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
            //el padre tiene otros hijos nodos y yo no tengo hijos
            //solo borro ese nodo
          aux->padre->cant_hijos--;
            delete aux;
        }else{
            //el padre solo tiene ese nodo como hijo, borro los antesesores
            while(aux != raiz && aux->padre->cant_hijos == 1){
                viejo = aux;
                aux = aux->padre;
                delete viejo;
            }
        }
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
    std::cout << "si sale por aca es porque sigue apuntando al mismo lugar" << std::endl;
    return *this;
}


template <typename T>
typename string_map<T>::iterator string_map<T>::iterator::avanzarAlMin(){
  it_avanzarAlMin();
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
  for(u_int i = 0; i < nodo->padre->cant_hijos; i++){
    if(nodo->padre->hijos[i] != NULL && nodo->padre->hijos[i]->definicion->first > nodo->definicion->first){
      nodo = nodo->padre->hijos[i];
      return *this;
    }
  }
  std::cout << "si sale por aca es porque sigue apuntando al mismo lugar" << std::endl;
  return *this;

}


template <typename T>
typename string_map<T>::const_iterator string_map<T>::const_iterator::avanzarAlMin(){
  it_avanzarAlMin();
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
      it_avanzarAlMin();
        return *this;
    }
    //si llego hasta aca es porque no tiene descendientes
    string_map<T>::const_iterator it(nodo);
    //CUIDADO ACAA!!!
    while(nodo->padre != nodo && !nodo->tieneHM()){
        it.nodo = it.nodo->padre;
    }
    //sali porque el padre es la raiz o la cantidad de hermanos es mayor a 1
    //busco a mi hermano mayor o al menor de mis "primos lejanos"
    if(nodo->tieneHM()){
      nodo =  it.nodo->hermanoMayor();
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


//funciones de Nodo


template <typename T>
typename string_map<T>::Nodo* string_map<T>::Nodo::minimo(){
    std::cout << "llamada al minimo" << std::endl;
    Nodo* aux = this;
    if(aux == NULL) throw runtime_error("minimo de un null");
    for (u_int i = 0; i < 256; ++i) {
        if (aux->hijos[i] != NULL) {
            aux = aux->hijos[i];
            if (aux->definicion != NULL) {
              std::cout << "saliendo del minimo"<< i << std::endl;
                return aux;
            }
            i =0;
        }
    }
    if(true) throw runtime_error("no tiene minimo");
}

template <typename T>
typename string_map<T>::Nodo* string_map<T>::Nodo::sucesor(){
    std::cout << "llamada al sucesor" << std::endl;
    //no tiene hijos, entonces el siguiente mayor es algun pariente mayor o el final
    if(cant_hijos > 0 ) throw runtime_error("buscando el sucesor cuando el nodo tiene hijos");
    bool hm = this->tieneHM();
    Nodo* temp = this;
    while(temp != temp->padre && hm){
        std::cout << "while del sucesor" << std::endl;
        temp = temp->padre;
    }
    if(hm){//si tiene hermano mayor, asigno el hermano mayor
        temp->hermanoMayor();
    }//sino, this es la raiz, asique no haga nada y devuelvo this porque ya esta en la posicion
    return temp;
}

template <typename T>
bool string_map<T>::Nodo::tieneHM(){
    for(u_int i = 0; i < 256; i++){
        std::cout << "for tieneHM" << std::endl;
        Nodo* temp = padre->hijos[i];
        if(temp->definicion != NULL && temp->definicion->first > definicion->first){
            return true;
        }

    }
    return false;
}

template <typename T>
typename string_map<T>::Nodo* string_map<T>::Nodo::hermanoMayor() {
    for(u_int i = 0; i < 256; i++){
        std::cout << "for del hermanoMayor" << std::endl;
        Nodo* temp = padre->hijos[i];
        if(temp->definicion != NULL && temp->definicion->first > definicion->first){
            return temp;
        }
    }
    if(true) throw runtime_error("no tiene hermano mayor");
}

template <typename T>
void string_map<T>::Nodo::eliminarNodosHijos(){
  for(u_int i = 0; i < 256; i++){
    if(hijos[i] != NULL){
      hijos[i]->eliminarNodos();
    }
  }
}
template <typename T>
void string_map<T>::Nodo::eliminarNodos(){
    for(u_int i = 0; i < 256; i++){
        if(hijos[i] != NULL){
           hijos[i]->eliminarNodos();
        }
    }
    delete this;
}
template <typename T>
void string_map<T>::Nodo::sumar1padres(){
  string_map<T>::Nodo* temp = this;
  while(temp != temp->padre){
    temp->padre->cant_hijos++;
    temp = temp->padre;
  }
}

template <typename T>
bool string_map<T>::Nodo::mismosNodos(Nodo* n2){
  if(this == NULL && n2 == NULL){
    return true;
  }
  bool res = true;
  if(this != NULL && n2 != NULL){
    if(cant_hijos != n2->cant_hijos){return false;}
    if(definicion != NULL && n2->definicion != NULL){
      if(definicion == n2->definicion){
        for(u_int i = 0; i < 256; i++){
          res = res && hijos[i]->mismosNodos(n2->hijos[i]);
        }
        return res;
      }
    }
  }
  return false;
}
