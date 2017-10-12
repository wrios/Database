#include "string_map.h"
#include <utility>

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
void string_map<T>::~string_map(){}

//constructor por copia
template <typename T>
void string_map<T>::string_map(const string_map & other){}

//operador de asignacion
template <typename T>
string_map& string_map<T>::operator=(const string_map &){}

template <typename T>
bool string_map<T>::operator==(const string_map& otro) const{}

//operador de comparacion
template <typename T>
bool string_map<T>::operator!=(const string_map& otro) const{}

//cantidad de apariciones de la clave
template <typename T>
size_type string_map<T>::count(const key_type &key) const{}

//cantidad de claves definidas
template <typename T>
size_t string_map<T>::size(){return cantElem;}

//devuelve true si size() == 0
template <typename T>
bool string_map<T>::empty(){return cantElem == 0;}

//acceso a la definicion, si no esta define por constructor por defecto
template <typename T>
mapped_type& string_map<T>operator[](const key_type &key){}

//devuelve el significado de la clave, sin modificar la clave
template <typename T>
mapped_type& string_map<T>::at(const key_type& key){}

//devuelve el significado de la clave, sin modificar clave ni significado
template <typename T>
const mapped_type& string_map<T>::at(const key_type& key) const{}

//vacia el mapa
template <typename T>
void string_map<T>::clear(){}

//devuelve iterator al primer par en orden lexicografico
template <typename T>
typename string_map<T>::iterator string_map<T>::begin(){}

//devuelve iterator al ultimo par en orden lexicografico
template <typename T>
typename string_map<T>::iterator string_map<T>::end(){}

//devuelve const_iterator al primer par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::begin()const{}

//devuelve const_iterator al ultimo par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::end()const{}

//devuelve const_iterator al primer (const)par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::cbegin()const{}

//devuelve const_iterator al ultimo (const)par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::end()const{}

//devuelve un iterador a la clave 
template <typename T>
typename string_map<T>::iterator string_map<T>::find(const key_type &key){}

//devuelve un iterador a la clave 
template <typename T>
typename string_map<T>::const_iterator string_map<T>::find(const key_type &key){}

//dado una pair<clave,sig> devuelve un pair<iterator,bool> indicando si lo inserto
template <typename T>
typename pair<string_map<T>::iterator, bool> string_map<T>::insert(const value_type &value){
  if(empty()){throw domain_error("Error: Diccionario vacio");}
  string_map<T>::iterator iter = begin();
  for(u_int i = 0; i < value.second.size(); i++){
    if(iterator){//no esta definido en la posicion, creo un nodo}
      else{itererase(const key_type& key){}

template <typename T>
typename string_map<T>::iterator string_map<T>::erase(string_map<T>::iterator pos){}

void swap(const string_map other&){
  using std::swap;
  swap(raiz, other.other);
  swap(cantElem, other.cantElem);

}

template <typename T>
string_map<T>::iterator& string_map<T>::iterator::operator++(){
  string_map<T>::iterator it(*this);
  while(padre->der == NULL && it->padre != NULL){
      it = it->padre;
  }
  if(der == NULL && padre == NULL){//no tengo padre ni hermano derecho
    return string_map<T>::iterator it(end());
  }
  else if(){//
    
  }

 }
