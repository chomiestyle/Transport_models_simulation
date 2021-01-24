#include "point.h"
#include "trajectory.h"
#include "params.h"
#include "model.h"
#include "creator.h"
#include "fixed_demand_creator.h"
#include <math.h>
#include <vector>
#include <iostream>

using namespace Model;
using namespace std;

namespace Creator{

fixed_demand_creator::fixed_demand_creator (model *_Model,double _flow){
    t=pow(_flow,-1);
    flow=_flow;
    Model=_Model;
};
point *fixed_demand_creator::create ( point *leader){
    double new_x=leader->X()-leader->V()*t;
    if (new_x>0){
        double new_t=leader->T();
        double new_v=leader->V();
        double new_lane=leader->LANE();
        point *new_point=new point(new_t,new_x,new_v,0.0,new_lane);
        double new_accel=Model->accel(leader,new_point,Model->params);
        new_point->set_accel(new_accel);
        return new_point;
    }
    else {
        return NULL;
    }
};

trajectory fixed_demand_creator::initial_state (point* leader){
    double leader_t=leader->T();
    double leader_x=leader->X();
    int n=leader_t*flow;
    trajectory initial_demand;
    initial_demand.push_back(create(leader));
    for(int i=1;i<n-1;++i){
        point *nuevo=create(initial_demand[i-1]);
        if (nuevo!=NULL){
            initial_demand.push_back(create(initial_demand[i-1]));
        }
        else{
            return initial_demand;
        }
        
    }
    
    return initial_demand;
        
    }
}
