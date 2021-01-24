#include "linear.h"
#include "p_linear.h"
#include "model.h"
#include <math.h>
#include <algorithm>
#include "iostream"
#include <random>
using namespace std;

namespace Model{
    linear::linear(){
        P_linear nuevo_linear;
        params=nuevo_linear.p_linear;
    }
    double linear::accel(point *leader,point *follower,Params *p){
        double V=p->Params_valor("V");
        double c1=p->Params_valor("c1");
        double c2=p->Params_valor("c2");
        double sr=p->Params_valor("sr");
        double tau=p->Params_valor("tau");
        double c3=p->Params_valor("c3");
        double pend=p->Params_valor("pend");
        double sigmatilde=p->Params_valor("sigmatilde");
        //double xdesde=400;
        //double xhasta=600;
        double fa=(V-follower->V())*c1;
        double fr=(leader->V()-follower->V())*c2+(leader->X()-follower->X()-sr-follower->V()*tau)*c3;
        if (fr>0){
            fr=0;
        }
        /*
            //las variables xdesde y xhasta dependen de geometry?
        if (xdesde<follower.X<xhasta){
            
                double sigma=sigmatilde*V*sqrt(c1);
                static default_random_engine rd;
                static normal_distribution <double> d(9.8*pend, sigma);
                double normal = d(rd);
                double fa = fa - normal;
        }
         */
        double acceleration=fa + fr;
        return acceleration;
    };
    double linear::equil_spcg(point *leader,point *follower, Params *p){
        double V=p->Params_valor("V");
        double c1=p->Params_valor("c1");
        double c2=p->Params_valor("c2");
        double sr=p->Params_valor("sr");
        double tau=p->Params_valor("tau");
        double c3=p->Params_valor("c3");
        double equil_spcg=sr-V*(c1/c3)*(tau+(c1/c3));
        return equil_spcg;
        
    };
    double linear::wave_speed(point leader,point follower,Params p){
        double V=p.Params_valor("V");
        double c1=p.Params_valor("c1");
        double c2=p.Params_valor("c2");
        double sr=p.Params_valor("sr");
        double tau=p.Params_valor("tau");
        double c3=p.Params_valor("c3");
        double w=(sr*c3-V*c1)/(c1 + c3*tau);
        return  w;
        
    };
    bool linear::lch_left(point *leader, point *follower, point *new_leader, point *new_follower,Params *p){
        double sr=p->Params_valor("sr");
        double V=p->Params_valor("V");
        double c1=p->Params_valor("c1");
        double c3=p->Params_valor("c3");
        double spacing_row=sr -V*(c1/c3);
        if (0.9*V>follower->V()){
            if ((leader->X()+spacing_row<follower->X() && follower->X() - spacing_row >= new_follower->X() + equil_spcg(follower,new_follower,p) && new_leader->X() - spacing_row >= follower->X() + equil_spcg(new_leader,follower,p))){
                return true;
            }
            
        }
        return false;
        
    };
    bool linear::lch_right(point *leader, point *follower, point *new_leader, point *new_follower,Params *p){
        double sr=p->Params_valor("sr");
        double V=p->Params_valor("V");
        double c1=p->Params_valor("c1");
        double c3=p->Params_valor("c3");
        double spacing_row=sr-V*(c1/c3);
        
        if (0.95*V<follower->V()){//que representa el V
            if ((leader->X()+spacing_row<follower->X() && follower->X() - spacing_row >= new_follower->X() + equil_spcg(follower,new_follower,p) && new_leader->X() - spacing_row >=follower->X() + equil_spcg(new_leader,follower,p))){
                return true;
            }
        }
        return false;
        
    };
    
}
