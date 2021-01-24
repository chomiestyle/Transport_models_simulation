#include "params.h"
#include "diccionario.h"

namespace Model{
    
    Params::Params(){
        
        D = diccionario_nuevo();
        
    }
    void  Params::Params_muestra(void){
         diccionario_muestra(D);
        
    }
    void Params::Params_agrega(const char* nuevo_nombre,double nuevo_valor){
         diccionario_agrega(D,nuevo_nombre,nuevo_valor);
        
    }
    double Params::Params_valor(const char* nombre){
        return diccionario_busca_significado(D,nombre);
    }
    
}
