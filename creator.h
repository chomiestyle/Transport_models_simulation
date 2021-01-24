#ifndef CREATOR_H
#define CREATOR_H

#include "point.h"
#include "trajectory.h"
#include "params.h"
#include "model.h"
#include <iostream>
#include <vector>

using namespace Model;
using namespace std;

namespace Creator{
    
    class creator{
        public:
        virtual point* create ( point *leader)=0;
        virtual trajectory initial_state( point* leader)=0;
    };
}
#endif
