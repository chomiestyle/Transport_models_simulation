#ifndef _PARAMS
#define _PARAMS

#include "diccionario.h"
namespace Model{
    
    class Params{
        public:
        Diccionario *D;
        Params ();
        void Params_muestra(void);
        void Params_agrega(const char* nuevo_nombre,double nuevo_valor);
        double Params_valor(const char* nombre);
    };
}
#endif
