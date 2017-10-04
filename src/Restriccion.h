#ifndef RESTRICCION_H
#define RESTRICCION_H

#include <string>
#include "Dato.h"

class Restriccion { 

public:

    Restriccion(const string& campo, const Dato& dato, bool igual);
    
    const string& campo() const;

    const Dato& dato() const;
    
    const bool& igual() const;

private:
    string _campo;
    Dato _dato;
    bool _igual;
   
};

bool operator==(const Restriccion& r1, const Restriccion& r2);
bool operator<(const Restriccion& r1, const Restriccion& r2);

Restriccion Rig(const string& campo, const string& valor);
Restriccion Rig(const string& campo, const int& valor);
Restriccion Rdif(const string& campo, const string& valor);
Restriccion Rdif(const string& campo, const int& valor);

#endif 
