#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <list>

//void filtrar(Contenedor & c, const typename Contenedor::value_type& elem){

template<class Contenedor>
bool pertenece(const typename Contenedor::value_type& x, Contenedor c) {
    for (auto elem: c){
        if (elem == x)
            return true;
    }
    return false;
}

//template<class T>
template<class Contenedor>
bool subset(Contenedor c1, Contenedor c2) {
    for (auto elem: c1){
        if (not pertenece(elem, c2))
            return false;
    }
    return true;
}

//template<class T>
template<class Contenedor>
bool seteq(Contenedor c1, Contenedor c2) {
    return subset(c1, c2) and subset(c2, c1);
}

template<class T>
std::ostream &operator<<(ostream &os, const list<T> &l) {
  os << "[";
  for (auto e : l) {
    os << e << ", ";
  }
  os << "]";
  return os;
}

template<class A, class B>
std::ostream &operator<<(ostream &os, const pair<A, B> &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

#endif //UTILS_H
