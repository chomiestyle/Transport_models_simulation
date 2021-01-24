#include "point.h"
#include "params.h"
#include "model.h"
#include "creator.h"
#include <math.h>

using namespace Model;


namespace Creator{

creator::creator (model *_Model,double _flow){
    //Model=new model;
    t=pow(_flow,-1);
    Model=_Model;
};
point* creator::create ( point *leader){
    double new_x=leader.X()-leader.V()*t;
    double new_t=leader.T()+t;
    double new_v=leader.V();
    double new_lane=leader.LANE();
    point new_point=point(new_t,new_x,new_v,0.0,new_lane);
    double new_accel=Model->accel(leader,new_point,Model->params);
    new_point.set_accel(new_accel);//ver si asi realiza un metodo a un puntero
    return new_point;
    
    
};
}
