#include "string_map.h"
#include <utility>
#include <iostream>

using namespace std;

typedef unsigned int u_int;

//construye mapa vacio
template <typename T>
void string_map<T>::string_map(){
  raiz = NULL;
  cantElem = 0;
}

//destructor de mapa
template <typename T>
void string_map<T>::~string_map(){
  this->cantElem = 0;
  auto it = this->begin();
  while (it != this->end()){
    erase(it);
    it++;
  }
  this->raiz = nullptr;
}

//constructor por copia
template <typename T>
void string_map<T>::string_map(const string_map & other){}

//operador de asignacion
template <typename T>
string_map& string_map<T>::operator=(const string_map & otro){
  //invocar al destructor
  this->cantElem = otro.cantElem;
  this->raiz = otro.raiz;
  for(auto it = otro.begin(); it!=otro.end(); ++it){
    this->insert(*it);
  }
}

template <typename T>
bool string_map<T>::operator==(const string_map& otro) const{}

//operador de comparacion
template <typename T>
bool string_map<T>::operator!=(const string_map& otro) const{ return !(*this == otro);
}

//cantidad de apariciones de la clave
template <typename T>
size_type string_map<T>::count(const key_type &key) const{
  Nodo* esta = raiz;
  for(u_int i = 0; i < key.size(); i++){
    if((esta->hijos)[int(key[i])] == NULL){return 0;}
    else{esta = esta->hijos[int(key[i])];}
  }
  return 1;
}

//cantidad de claves definidas
template <typename T>
size_t string_map<T>::size() const{return cantElem;}

//devuelve true si size() == 0
template <typename T>
bool string_map<T>::empty() const {return cantElem == 0;}

//acceso a la definicion, si no esta define por constructor por defecto
template <typename T>
mapped_type& string_map<T>::operator[](const key_type &key){
  Nodo* sekeer = raiz;
  for(u_int i = 0; i < key.size(); i++){
    if((sekeer->hijos)[i] == NULL ){
      (sekeer->hijos)[int(key[i])] = new Nodo();
    }
      sekeer = (sekeer->hijos)[int(key[i])];
  }
    sekeer->definicion = T();
  return sekeer->definicion;
}

//devuelve el significado de la clave, sin modificar la clave
template <typename T>
mapped_type& string_map<T>::at(const key_type& key){
  Nodo* sekeer = raiz;
  for(u_int i = 0; i < key.size(); i++){
    if((sekeer->hijos)[int(key[i])] == NULL ){
        //Esto es para debbuguear
      //throw domain_error("El elemento no esta");
        cout << "El elemento no esta" << endl;
    }
      sekeer = (sekeer->hijos)[int(key[i])];
  }
  return sekeer->definicion;
}

//devuelve el significado de la clave, sin modificar clave ni significado
template <typename T>
const mapped_type& string_map<T>::at(const key_type& key) const{
  Nodo* sekeer = raiz;
  for(u_int i = 0; i < key.size(); i++){
    if((sekeer->hijos)[int(key[i])] == NULL ){
      //throw domain_error("El elemento no esta");
        cout << "El elemento no esta" << endl;
    }
      sekeer = (sekeer->hijos)[int(key[i])];
  }
  return sekeer->definicion;
}

//vacia el mapa
template <typename T>
void string_map<T>::clear(){}

//devuelve iterator al primer par en orden lexicografico
template <typename T>
typename string_map<T>::iterator string_map<T>::begin(){
  string_map<T>::iterator it(raiz);
    return  it;
}

//devuelve iterator al ultimo par en orden lexicografico
template <typename T>
typename string_map<T>::iterator string_map<T>::end(){}

//devuelve const_iterator al primer par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::begin()const{
  string_map<T>::const_iterator it(raiz);
    return it;
}

//devuelve const_iterator al ultimo par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::end()const{}

//devuelve const_iterator al primer (const)par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::cbegin()const{
  string_map<T>::const_iterator it(raiz);
    return it;
}

//devuelve const_iterator al ultimo (const)par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::end()const{}

//devuelve un iterador a la clave 
template <typename T>
typename string_map<T>::iterator string_map<T>::find(const key_type &key){
  Nodo* sekeer = raiz;
  for(u_int i = 0; i < key.size(); i++){
    if((sekeer->hijos)[int(key[i])] == NULL ){
      //throw domain_error("El elemento no esta");
        cout << "El elemento no esta" << endl;
    }
    sekeer = (sekeer->hijos)[int(key[i])];
  }
  string_map<T>::iterator it(sekeer);
    return it;
}

//devuelve un iterador a la clave 
template <typename T>
typename string_map<T>::const_iterator string_map<T>::find(const key_type &key) const {
  Nodo* sekeer = raiz;
  for(u_int i = 0; i < key.size(); i++){
    if((sekeer->hijos)[int(key[i])] == NULL ){
      //throw domain_error("El elemento no esta");
        cout << "El elemento no esta" << endl;
    }
    sekeer = (sekeer->hijos)[int(key[i])];
  }
  string_map<T>::const_iterator it(sekeer);
    return it;
}


//NO anda!
//dado una pair<clave,sig> devuelve un pair<iterator,bool> indicando si lo inserto
template <typename T>
typename pair<string_map<T>::iterator, bool> string_map<T>::insert(const value_type &value){
  if(empty()){
      //throw domain_error("Error: Diccionario vacio");
      cout << "Error: Diccionario vacio" << endl;}
  string_map<T>::iterator iter = begin();
  for(u_int i = 0; i < value.second.size(); i++){
    if(iter){//no esta definido en la posicion, creo un nodo
         }
      else{iter->erase(const key_type& key){}
      }
    }
}


template <typename T>
typename string_map<T>::iterator string_map<T>::erase(string_map<T>::iterator pos){}


template <typename T>
void string_map<T>::swap(const string_map &other){
  using std::swap;
  swap(raiz, other.raiz);
  swap(cantElem, other.cantElem);

}

template <typename T>
void string_map<T>::iterator::iterator(const iterator& otro){
  string_map<T>::iterator it(otro->nodo);
}

template <typename T>
string_map<T>::iterator& string_map<T>::iterator::operator=(const iterator& otro){
  string_map<T>::iterator it(otro->nodo);
    return it;
}

template <typename T>
bool string_map<T>::iterator::operator==(const iterator& otro) const {
  return nodo == otro->nodo;
}

template <typename T>
bool string_map<T>::iterator::operator!=(const iterator& otro) const {
  return !(*this == otro);
}

//QUIEN ES PADRE???
template <typename T>
string_map<T>::iterator& string_map<T>::iterator::operator++(){
  string_map<T>::iterator it(*this);
  while(padre->der == NULL && it->padre != NULL){
    it = it->padre;
    if(it->padre->definicion != NULL){return it;}
  }
  if(it->der != NULL){//tengo hermano derecho
    it = it->der;
    while(it->h_prim != NULL){//voy por el menor camino(lexicografico)
      it = it->h_prim;
    }
    return it;//devuelvo iterator que apunta a el menor de la rama en la que estoy
  }
  else{
    return it;//iterator apuntado a la posicion pasando el ultimo
  }
 }


//QUIEN ES PADRE???
template <typename T>
string_map<T>::iterator string_map<T>::iterator::operator++(){
  string_map<T>::iterator it(*this);
  while(padre->der == NULL && it->padre != NULL){
    it = it->padre;
    if(it->padre->definicion != NULL){return *(it);}
  }
  if(it->der != NULL){//tengo hermano derecho
    it = it->der;
    while(it->h_prim != NULL){//voy por el menor camino(lexicografico)
      it = it->h_prim;
    }
    return *(it);//devuelvo iterator que apunta a el menor
  }
  else{
    return *(it);//iterator apuntado a la posicion pasando el ultimo
  }
}


//Todavia no funca!
template <typename T>
typename   string_map<T>::value_type& string_map<T>::iterator::operator*(){
  return (nodo->definicion);
}

//*/desreferencia
//->atributo/ desreferencia y accede al atributo

template <typename T>
typename string_map<T>::value_type* string_map<T>::iterator::operator->(){
  return *(nodo->definicion);
}
