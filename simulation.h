#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include "point.h"
#include "params.h"
#include "model.h"
#include "creator.h"
#include "geometry.h"
#include "trajectory.h"
#include <vector>

using namespace Model;
using namespace Creator;
using namespace std;
using namespace Geometry;

namespace Simulation{
    
    class simulation{
    private:
        model *Model;
        double T;
	double dt;
        geometry *GEO;
        creator *Creator;
        trajectory vector_initial;
        
        
    public:
        simulation (model *_Model,double tiempo,geometry *_geometry,creator *_Creator,trajectory,double dt);
        point *create_new_point(point *, point*);
	point *create_leader_trajectory(point *ld_car,int time);
        vector<trajectory>run();
	//vector<double>passes(double x);
        //vector <double>positions(double t);
        //vector<double>traffic_state(double x_min,double x_max,double t_min,double t_max);
    };
}
#endif
