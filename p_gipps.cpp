#include "params.h"
#include "p_gipps.h"

namespace Model{
    P_gipps::P_gipps(){
        p_gipps=new Params;
        p_gipps->Params_agrega("an",1.7 );//aceleracion max
        p_gipps->Params_agrega("bn",-3.4 );//desaceleracion max
        p_gipps->Params_agrega("sn",6.5);//espaciamiento de taco
        p_gipps->Params_agrega("vn",20);//velocidad de flujo libre
        p_gipps->Params_agrega("tau",0.8);//tiempo de reaccion
        p_gipps->Params_agrega("bg",-3.2);//desaceleracion max esperable del lider
        
    }
    
}
