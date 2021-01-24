
#ifndef LINEAR_H
#define LINEAR_H

#include "p_linear.h"
#include "model.h"
#include "point.h"

namespace Model{
    
    class linear: public model{
        public :
        linear();
        double accel(point *leader,point *follower,Params *p) override;
        double equil_spcg(point *leader,point *follower, Params *p)override;
        double wave_speed(point leader,point follower,Params p)override;
        bool lch_left(point *leader, point *follower, point *new_leader, point *new_follower,Params *p)override;
        bool lch_right(point *leader, point *follower, point *new_leader, point *new_follower,Params *p)override;
        
    };
}
#endif
