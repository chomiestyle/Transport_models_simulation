#ifndef FIXED_STATE_CREATOR_H
#define FIXED_STATE_CREATOR_H

#include "point.h"
#include "trajectory.h"
#include "params.h"
#include "model.h"
#include <iostream>
#include "creator.h"
#include <vector>

using namespace Model;
using namespace std;

namespace Creator{
    
class fixed_state_creator:public creator{
    private:
        double spacing;
        double initial_speed;
        model *Model;
        
    public:
        fixed_state_creator (model *_Modelo,double _spacing,double _initial_speed);
        point *create (point *leader)override;
        trajectory initial_state ( point* leader)override;
    };
}
#endif
