#include "string_map.h"
#include <utility>
#include <iostream>

using namespace std;

typedef unsigned int u_int;

//construye mapa vacio
template <typename T>
void string_map<T>::string_map(){
    raiz = new Nodo();
    cantElem = 0;
}

//destructor de mapa
template <typename T>
void string_map<T>::~string_map(){
    this->cantElem = 0;
    auto it = this->begin();
    while (it != this->end()){
        it = erase(it);
    }
    delete raiz;
}

//constructor por copia
template <typename T>
void string_map<T>::string_map(const string_map & other){}

//operador de asignacion
template <typename T>
string_map& string_map<T>::operator=(const string_map &otro){
    //invocar al destructor
    this->cant_Elem = otro->cant_Elem;
    this->raiz = otro->raiz;
    for(auto it = otro.begin(); it!=otro.end(); ++it){
        this->insert(*it);
    }
    return this;
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
bool string_map<T>::operator==(const string_map& otro) const{
    bool iguales = (cantElem == otro.cantElem);
    iguales = iguales && mismosNodos(raiz, otro.raiz);
    return iguales;
}


//operador de comparacion
template <typename T>
bool string_map<T>::operator!=(const string_map& otro) const{
    return !(*this == otro);
}

//cantidad de apariciones de la clave
template <typename T>
size_type string_map<T>::count(const key_type &key) const{
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
mapped_type& string_map<T>::operator[](const key_type &key){
    Nodo* sekeer = raiz;
    for(u_int i = 0; i < key.size(); i++){
        if((sekeer->hijos)[i] == NULL ){
            (sekeer->hijos)[int(key[i])] = new Nodo();
        }
        sekeer = (sekeer->hijos)[int(key[i])];
    }
    if(sekeer->definicion == NULL){sekeer->definicion = T();}
    return sekeer->definicion;
}

//devuelve el significado de la clave, sin modificar la clave
template <typename T>
mapped_type& string_map<T>::at(const key_type& key){
    Nodo* sekeer = raiz;
    for(u_int i = 0; i < key.size(); i++){
        if((sekeer->hijos)[int(key[i])] == NULL ){
            throw domain_error("El elemento no esta");
        }
        seeker = (seeker->hijos)[int(key[i])];
    }
    return seeker->definicion;
}

//devuelve el significado de la clave, sin modificar clave ni significado
template <typename T>
const mapped_type& string_map<T>::at(const key_type& key) const{
    Nodo* sekeer = raiz;
    for(u_int i = 0; i < key.size(); i++){
        if((sekeer->hijos)[int(key[i])] == NULL ){
            throw domain_error("El elemento no esta");
        }
        seeker = (seeker->hijos)[int(key[i])];
    }
    return seeker->definicion;
}

//vacia el mapa
template <typename T>
//limpia el mapa no lo destruye
template <typename T>
void string_map<T>::clear(){
    this->cant_Elem = 0;
    auto it = begin();
    while(it != this->end()){
        it = erase(it);
    }
}

//devuelve un nodo al minimo elemento
template <typename T>
Nodo* string_map<T>::minimo(){
    Nodo* aux = raiz->prim;
    while(aux->prim != NULL){
        aux = aux->prim;
    }
    return aux;
}

//devuelve iterator al primer par en orden lexicografico
template <typename T>
typename string_map<T>::iterator string_map<T>::begin(){
    return string_map<T>::iterator it(minimo());
}

//devuelve iterator al ultimo par en orden lexicografico
template <typename T>
typename string_map<T>::iterator string_map<T>::end(){
    return string_map<T>::iterator it(*raiz);
}

//devuelve const_iterator al primer par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::begin()const{
    return string_map<T>::const_iterator it(*raiz);
}

//devuelve const_iterator al ultimo par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::end()const{
    return string_map<T>::const_iterator it(*raiz);
}

//devuelve const_iterator al primer (const)par en orden lexicografico
template <typename T>
const typename string_map<T>::const_iterator string_map<T>::cbegin()const{
    return string_map<T>::const_iterator it(minimo());
}

//devuelve const_iterator al ultimo (const)par en orden lexicografico
template <typename T>
typename string_map<T>::const_iterator string_map<T>::end()const{
    return string_map<T>::const_iterator it(*raiz);
}

//devuelve un iterador a la clave 
template <typename T>
typename string_map<T>::iterator string_map<T>::find(const key_type &key){
    Nodo* seeker = raiz;
    for(u_int i = 0; i < key.size() && seeker->cant_h>1; i++){
        if((sekeer->hijos)[int(key[i])] == NULL ){
            throw domain_error("El elemento no esta");
        }
        seeker = (seeker->hijos)[int(key[i])];
    }
    return string_map<T>::iterator it(*seeker);
}

//devuelve un iterador a la clave
template <typename T>
typename string_map<T>::const_iterator string_map<T>::find(const key_type &key){
    Nodo* sekeer = raiz;
    for(u_int i = 0; i < key.size() && sekeer->cant_h > 1; i++){
        if((sekeer->hijos)[int(key[i])] == NULL ){
            throw domain_error("El elemento no esta");
        }
        seeker = (seeker->hijos)[int(key[i])];
    }
    return string_map<T>::const_iterator it(*seeker);
}

//define o redefine 
template <typename T>
typename pair<string_map<T>::iterator, bool> string_map<T>::insert(const value_type &value){
    Nodo* recognizer = raiz;
    for(u_int i = 0; i < value.first.size(); i++){
        if(recognizer->hijos[int(value[i])] == NULL){
            recognizer->hijos[int(value.first[i])] = new Nodo();
            recognizer->hijos[int(value.first[i])]->padre = recognizer;
            recognizer->hijos[int(value.first[i])]->padre->prim = hijos[int(value[i])];
        }
        recognizer->hijos[int(value.first[i])]->padre->cant_hijos++;
        recognizer->hijos[int(value.first[i])]->padre->cant_descendientes++;
        recognizer = recognizer->hijos[int(value.first[i])];
    }
    if(recognizer->definicion == NULL){can_Elem++;}
    recognizer->definicion = value.second;
}

//devuelve un bool indicando si tiene significado
template <typename T>
bool reestablecerPrim(Nodo* pos){
    u_int menor;
    for(u_int i = 0; i<256 && aux == NULL; i++){
        menor = i;
    }
    pos->prim = pos->hijos[menor];
    return (prim != NULL)&&(prim->definicion != NULL);
}

template <typename T>
typename string_map<T>::iterator string_map<T>::erase(string_map<T>::iterator pos){
    if(empty()){throw domain_error("Error: Diccionario vacio");}
    string_map<T>::iterator viejo = pos->padre;
    string_map<T>::iterator res = pos;
    res++;
    if(pos->cant_hijos > 0){
        //si tiene hijos, borro su definicion y dejo que su hijos vivan
        pos->definicion = NULL;
    }else{
        //no tiene hijos, borro el nodo y me fijo que pasa con el padre
        if(viejo->cant_hijos > 1){
            //el padre tiene otros hijos nodos
            //solo borro ese nodo
            delete pos;
        }else{
            //el padre solo tiene ese nodo como hijo, borro los antesesores
            while(pos != raiz && pos->padre->cant_hijos == 0){
                Nodo* aux = pos;
                pos = pos->padre;
                delete aux;
            }
        }
        viejo->cant_hijos--;
        reestablecerPrim(viejo->padre);
    }
    return res;
}

template <typename T>
typename string_map<T>::iterator string_map<T>::erase(const key_type &key){
    string_map<T>::iterator iter = find();
    erase(iter);
}

void swap(const string_map other&){
using std::swap;
swap(raiz, other.raiz);
swap(cant_Elem, other.cant_Elem);

}


template <typename T>
void string_map<T>::iterator::iterator(const iterator& otro){
    string_map<T>::iterator it(otro->nodo);
}

template <typename T>
string_map<T>::iterator string_map<T>::iterator::operator=(const iterator& otro){
    return string_map<T>::iterator it(otro->nodo);
}

template <typename T>
bool string_map<T>::iterator::operator==(const iterator& otro){
    return nodo == otro->nodo;
}

template <typename T>
bool string_map<T>::iterator::operator!=(const iterator& otro){
    return !(*this == otro);
}

template <typename T>
//3 casos
//es descendiente
//es su hermano mayor
//es su primo
string_map<T>::iterator string_map<T>::iterator::operator++(){
    //es descendiente
    while(cant_descendientes > 0){
        while(nodo->prim->definicion == NULL){
            nodo = nodo->prim;
        }
        return *this;
    }
    //si llego hasta aca es porque no tiene descendientes
    string_map<T>::iterator it(nodo);
    while(nodo->padre != raiz && nodo->padre->cant_hijos > 1){
        it->nodo = it->nodo->padre;
    }
    //sali porque el padre es la raiz o la cantidad de hermanos es mayor a 1
    //busco a mi hermano mayor o al menor de mis "primos lejanos"
    if((it.avanzarMayor())->nodo->clave > nodo->clave){
        nodo =  it.avanzarAlMin()->nodo;
        //devuelvo iterador apuntando al menor primo o mayor hermano
        return *this;
    }
    //si estoy aca es porque soy el mayor elemento
    nodo = end();
    return *this;
    //devuelvo iterator apuntando al final
}

string_map<T>::iterator string_map<T>::iterator::herm_Mayor(){
    for(u_int i = 0; i < nodo->padre->hijos->size(); i++){
        if(nodo->padre->hijos[i] != NULL && nodo->padre->hijos[i]->clave > nodo->clave){
            nodo = nodo->padre->hijos[i];
            return *this;
        }
    }
    //si sale por aca es porque sigue apuntando al mismo lugar
    return *this;
}

string_map<T>::iterator string_map<T>::iterator::avanzarAlMin(){
    while(prim != NULL){
        nodo = prim;
    }
    return *this;
}

bool string_map<T>::iterator::tieneHM(key_type& clave){
    for(u_int i = 0; i < nodo->padre->hijos->size(); i++){
        Nodo* aux  = nodo->padre->hijos[i];
        if(!(nodo->clave > aux->clave)){ return true;}
    }
    return false;
}


template <typename T>
typename   string_map<T>::value_type& string_map<T>::iterator::operator*(){
    return nodo->definicion;
}

template <typename T>
typename string_map<T>::value_type* string_map<T>::iterator::operator->(){
    return *(nodo->definicion);
}


//devuelve el sucesor inorder de la posicion pasada como parametro
Nodo* sucesor(Nodo* pos) const{
    if(pos->descendientes == 0 && hermanos_mayores > 0){
        Nodo* aux = pos->padre;
        while(aux != ultima_pos){
            aux= aux->h_mayor;
            return string_map<T>::iterator it(aux);
        }
    }
    else if(pos->descendientes > 0){
        Nodo*  aux = pos->prim_h;
        return string_map<T>::iterator it(aux);
    }
}
