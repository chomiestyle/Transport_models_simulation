#include "params.h"
#include "p_idm.h"

namespace Model{
    
    P_idm::P_idm(){
        p_idm=new Params;
        p_idm->Params_agrega("v0",120/3.6 );//velocidad max
        p_idm->Params_agrega("T",1.6 );//headway de equilibrio
        p_idm->Params_agrega("a",0.73);//aceleracio max
        p_idm->Params_agrega("b",1.67);//desaceleracion max
        p_idm->Params_agrega("s0",2);//gap de taco
        p_idm->Params_agrega("l",5);//longitud de vehiculo
        
    }
    
}

