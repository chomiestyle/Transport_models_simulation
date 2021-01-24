#ifndef GIPPS_H
#define GIPPS_H

#include "p_gipps.h"
#include "model.h"
#include "point.h"

namespace Model{

class gipps: public model{
    
    
    public :
    gipps ();
    double accel(point *lider,point *follower,Params *p) override;
    double equil_spcg(point *leader,point *follower, Params *p)override;
    double wave_speed(point leader,point follower,Params p)override;
    bool lch_left(point *leader, point *follower, point *new_leader, point *new_follower,Params *p)override;
    bool lch_right(point *leader, point *follower, point *new_leader, point *new_follower,Params* p)override;
    
};
}
#endif
