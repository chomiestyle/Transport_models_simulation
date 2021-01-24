#ifndef MODEL_H
#define MODEL_H

#include "point.h"
#include "params.h"
namespace Model{
    
    class model{
        
    public:
        Params *params=new Params;
        virtual double accel( point *leader,point *follower,Params *p)=0;
        virtual double equil_spcg(point *leader,point *follower, Params *p)=0;
        virtual double wave_speed(point leader,point follower,Params p)=0;
        virtual bool lch_left(point *leader, point *follower, point *new_leader, point *new_follower,Params *p)=0;
        virtual bool lch_right(point *leader, point *follower, point *new_leader, point *new_follower, Params *p)=0;
    };
}
#endif

