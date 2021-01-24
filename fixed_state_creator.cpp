#include "point.h"
#include "trajectory.h"
#include "params.h"
#include "model.h"
#include "creator.h"
#include "fixed_state_creator.h"
#include <iostream>
#include <vector>
#include <math.h>


using namespace std;
using namespace Model;

namespace Creator{
fixed_state_creator::fixed_state_creator (model *_Model,double _spacing,double _initial_speed){
    spacing=_spacing;
    initial_speed=_initial_speed;
    Model=_Model;
    
};
point *fixed_state_creator::create(point *leader){
    point *new_point=new point(leader->T(),0.0,initial_speed,leader->A(),leader->LANE());
    double equil_spacing=Model->equil_spcg(leader,new_point,Model->params);
    double sm=max(equil_spacing,spacing);
    //cout<<"esto es el valor de sm "<< sm <<endl;
    double new_x=leader->X()-sm;
    if (new_x>=0){
        new_point->set_x(new_x);
        //double new_accel=Model->accel(leader,new_point,Model->params);//aca nose si estoy calculando lo que necesito
        //new_point->set_accel(new_accel);
        return new_point;
    }
    else{
        return NULL;
    }
    };
trajectory  fixed_state_creator::initial_state (point* leader){
    double leader_x=leader->X();
    //double equil_spacing=Model->equil_spcg(leader,new_point,Model->params);
    //spacing=min(equil_spacing,spacing);
    int  n=leader_x/spacing;
    trajectory initial_vector;
    initial_vector.push_back(leader);
    for (int i=1;i<n;++i){
        point *new_car;
	new_car=create(initial_vector[i-1]);
	if (new_car != NULL){
        	initial_vector.push_back(new_car);
	}
	else{
		return initial_vector;
	}
    }
    return initial_vector;
        
};
}
