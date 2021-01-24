#include "point.h"

namespace Model{

point::point(double _t,double _x,double _v,double _a,int _lane){
    t=_t;
    x=_x;
    a=_a;
    v=_v;
    lane=_lane;
};
double point::T(){
    return t;
};
double point::X(){
    return x;
    
};
double point::A(){
    return a;
    
};
void point::set_accel(double _a){
    a=_a;
        
    }
void point::set_x(double _x){
        x=_x;
        
    }
void point::set_lane(int _lane){
        lane=_lane;
        
    }
    
double  point::V(){
        return v;
        
    };
int  point::LANE(){
    return lane;
    
};
}


