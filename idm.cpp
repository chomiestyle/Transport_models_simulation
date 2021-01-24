#include "idm.h"
#include "p_idm.h"
#include "model.h"
#include <math.h>
#include <algorithm>

using namespace std;

namespace Model{
    
    idm::idm(){
        P_idm nuevo_idm;
        params=nuevo_idm.p_idm;
    };
    double idm::accel(point *leader,point *follower,Params *p){
        double s0=p->Params_valor("s0");
        double T=p->Params_valor("T");
        double a=p->Params_valor("a");
        double b=p->Params_valor("b");
        double v0=p->Params_valor("v0");
        double dl=p->Params_valor("dl");
        double l=p->Params_valor("l");
        double si=s0+T*follower->V()+follower->V()*(follower->V()-leader->V())/(2*sqrt(a*b));
        return a*(1-pow(follower->V()/v0,dl)-pow(si/(leader->X()-follower->X()-l),2));
    };
    double idm::equil_spcg(point *leader,point *follower, Params *p){
        double s0=p->Params_valor("s0");
        double a=p->Params_valor("a");
        double b=p->Params_valor("b");
        double T=p->Params_valor("T");
        double v0=p->Params_valor("v0");
        double var=sqrt(a*b);
        double delta_v=leader->V()-follower->V();
        double equil_spcg=s0 + T*v0 + (v0*delta_v)/(2*var);
        return equil_spcg;
        
    };
    double idm::wave_speed(point leader,point follower,Params p){
        return 0.0;
        
    };
    bool idm::lch_left(point *leader, point *follower, point *new_leader, point *new_follower,Params *p){
        double s0=p->Params_valor("s0");
        double l=p->Params_valor("l");
        double spacing_row=s0+l;
        double T=p->Params_valor("T");
        if (0.9*T>follower->V()){
            if ((leader->X()+spacing_row<follower->X() && follower->X() - spacing_row >= new_follower->X() + equil_spcg(follower,new_follower,p) && new_leader->X() - spacing_row >= follower->X() + equil_spcg(new_leader,follower,p))){
                return true;
            }
        }
        return false;
        
    };
    bool idm::lch_right(point *leader, point *follower, point *new_leader, point *new_follower,Params *p){
        double s0=p->Params_valor("s0");
        double T=p->Params_valor("T");
        double l=p->Params_valor("l");
        double spacing_row=s0+l;
        
        if (0.95*T<follower->V()){
            if ((leader->X()+spacing_row<follower->X() && follower->X() - spacing_row >= new_follower->X() + equil_spcg(follower,new_follower,p) && new_leader->X() - spacing_row >=follower->X() + equil_spcg(new_leader,follower,p))){
                return true;
            }
        }

        return false;
        
    };
    
}
