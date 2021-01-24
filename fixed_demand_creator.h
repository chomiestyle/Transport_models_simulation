#ifndef FIXED_DEMAND_CREATOR_H
#define FIXED_DEMAND_CREATOR_H

#include "point.h"
#include "params.h"
#include "model.h"
#include <iostream>
#include "creator.h"
#include "trajectory.h"

using namespace Model;
using namespace std;

namespace Creator{
class fixed_demand_creator:public creator{
    private:
        double t;
        double flow;
        model *Model;
        

    public:
        fixed_demand_creator (model *_Modelo,double _flow);
        point *create (point *leader)override;
        trajectory initial_state (point* leader)override;
    };
}
#endif

